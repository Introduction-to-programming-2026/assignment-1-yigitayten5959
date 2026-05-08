// CS50x Week 5 — Speller: dictionary.h
// ⚠️  DO NOT MODIFY THIS FILE
// Declares the dictionary's constants and the function prototypes for dictionary.c

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

/**
 * LENGTH
 * ------
 * The maximum length for a word in the dictionary.
 * The longest word in the English language is commonly cited as 45 characters.
 * Any word read from the dictionary or text will be at most this long.
 */
#define LENGTH 45

/**
 * Prototypes for the five functions implemented in dictionary.c.
 * These allow speller.c to call your functions correctly.
 */

// Returns true if word is in dictionary, else false
bool check(const char *word);

// Hashes a word to a number (bucket index)
unsigned int hash(const char *word);

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary);

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void);

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void);

#endif // DICTIONARY_H
