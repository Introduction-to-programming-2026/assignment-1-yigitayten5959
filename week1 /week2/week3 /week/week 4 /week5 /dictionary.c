// CS50x Week 5 — Speller: dictionary.c
// Implementation of a dictionary spell-checker using a hash table.

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // for strcasecmp

#include "dictionary.h"

/**
 * NODE 
 * Represents one entry in the hash table's linked list.
 */
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

/**
 * HASH TABLE CONFIGURATION
 * N is the number of buckets. For the large dictionary,
 * a larger prime number helps reduce collisions.
 */
const unsigned int N = 10007;

// Global hash table
node *table[N];

// Global word counter
unsigned int word_count = 0;

/**
 * hash
 * ----
 * Hashes a word to a number in the range [0, N-1].
 * This implementation uses the djb2 algorithm for better distribution.
 */
unsigned int hash(const char *word)
{
    unsigned long hash_val = 5381;
    int c;
    while ((c = tolower(*word++)))
    {
        hash_val = ((hash_val << 5) + hash_val) + c; // hash * 33 + c
    }
    return hash_val % N;
}

/**
 * load
 * ----
 * Loads the dictionary file into the hash table.
 * Returns true if successful, else false.
 */
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Buffer for reading words
    char word[LENGTH + 1];

    // Read words one by one until EOF
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate memory for a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            return false;
        }

        // Copy the word into the node
        strcpy(n->word, word);

        // Get the hash index
        unsigned int index = hash(word);

        // Prepend the node to the linked list (O(1) operation)
        n->next = table[index];
        table[index] = n;

        // Increment total word count
        word_count++;
    }

    // Close the file
    fclose(file);
    return true;
}

/**
 * check
 * -----
 * Returns true if the word is in the dictionary, else false.
 * This is case-insensitive.
 */
bool check(const char *word)
{
    // Find the hash bucket index
    unsigned int index = hash(word);

    // Walk the linked list in that bucket
    node *cursor = table[index];
    while (cursor != NULL)
    {
        // Compare words ignoring case
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

/**
 * size
 * ----
 * Returns the number of words currently in the dictionary.
 */
unsigned int size(void)
{
    return word_count;
}

/**
 * unload
 * ------
 * Frees all memory allocated for the hash table.
 * Returns true if successful, else false.
 */
bool unload(void)
{
    // Iterate over each bucket in the hash table
    for (int i = 0; i < N; i++)
    {
