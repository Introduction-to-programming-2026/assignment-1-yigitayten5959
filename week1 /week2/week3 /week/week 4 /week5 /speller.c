// CS50x Week 5 — Speller: speller.c
// ⚠️  DO NOT MODIFY THIS FILE
// Distribution code provided by CS50.
// This file handles timing, text processing, and calls your dictionary functions.

#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>

#include "dictionary.h"

// Undefine any macros that might interfere with timing
#undef calculate
#undef getrusage

// Default dictionary path if none is provided via command line
#define DICTIONARY "dictionaries/large"

// Prototype for the timing calculation function
double calculate(const struct rusage *b, const struct rusage *a);

int main(int argc, char *argv[])
{
    // Ensure correct command-line usage
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./speller [DICTIONARY] text\n");
        return 1;
    }

    // Structures to store resource usage (for timing)
    struct rusage before, after;

    // Benchmarking variables
    double time_load = 0.0, time_check = 0.0, time_size = 0.0, time_unload = 0.0;

    // Determine which dictionary to use
    char *dictionary = (argc == 3) ? argv[1] : DICTIONARY;

    // Load the dictionary and record time taken
    getrusage(RUSAGE_SELF, &before);
    bool loaded = load(dictionary);
    getrusage(RUSAGE_SELF, &after);

    // Abort if dictionary failed to load
    if (!loaded)
    {
        printf("Could not load %s.\n", dictionary);
        return 1;
    }

    // Calculate time spent in load()
    time_load = calculate(&before, &after);

    // Identify the text file to spell-check
    char *text = (argc == 3) ? argv[2] : argv[1];
    FILE *file = fopen(text, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", text);
        unload();
        return 1;
    }

    // Start spell-checking process
    printf("\nMISSPELLED WORDS\n\n");

    int index = 0, misspellings = 0, words = 0;
    char word[LENGTH + 1];
    char c;

    // Read every character in the text file
    while (fread(&c, sizeof(char), 1, file))
    {
        // Only allow alphabetical characters and apostrophes (standard for English)
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            word[index] = c;
            index++;

            // Ignore words that are longer than the dictionary's max length
            if (index > LENGTH)
            {
                while (fread(&c, sizeof(char), 1, file) && isalpha(c));
                index = 0;
            }
        }
        // If we reach a number or punctuation, we've found a complete word
        else if (index > 0)
        {
            // Terminate the current word
            word[index] = '\0';
            words++;

            // Check the word's spelling and time the operation
            getrusage(RUSAGE_SELF, &before);
            bool misspelled = !check(word);
            getrusage(RUSAGE_SELF, &after);

            // Accumulate total time spent checking words
            time_check += calculate(&before, &after);

            // Print the word if it is not in the dictionary
            if (misspelled)
            {
                printf("%s\n", word);
                misspellings++;
            }

            // Reset index for the next word
            index = 0;
        }
    }

    // Close the text file
    fclose(file);

    // Determine the dictionary size and record time
    getrusage(RUSAGE_SELF, &before);
    unsigned int n = size();
    getrusage(RUSAGE_SELF, &after);
    time_size = calculate(&before, &after);

    // Unload the dictionary from memory and record time
    getrusage(RUSAGE_SELF, &before);
    bool unloaded = unload();
    getrusage(RUSAGE_SELF, &after);
    time_unload = calculate(&before, &after);

    // Error if unloading failed
    if (!unloaded)
    {
        printf("Could not unload %s.\n", dictionary);
        return 1;
    }

    // Output final benchmarking report
    printf("\nWORDS MISSPELLED:     %d\n", misspellings);
    printf("WORDS IN DICTIONARY:  %d\n", n);
    printf("WORDS IN TEXT:        %d\n", words);
    printf("TIME IN load:          %.2f\n", time_load);
    printf("TIME IN check:         %.2f\n", time_check);
    printf("TIME IN size:          %.2f\n", time_size);
    printf("TIME IN unload:        %.2f\n", time_unload);
    printf("TIME IN TOTAL:         %.2f\n",
           time_load + time_check + time_size + time_unload);
    printf("\n");

    return 0;
}

/**
 * calculate
 * ---------
 * Returns the number of seconds elapsed between two rusage structures.
 */
double calculate(const struct rusage *b, const struct rusage *a)
{
    if (b == NULL || a == NULL)
    {
        return 0.0;
    }
    else
    {
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                  (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                 ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                  (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec))) /
                1000000.0);
    }
}
