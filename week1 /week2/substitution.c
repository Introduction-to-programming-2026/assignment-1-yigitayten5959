#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Function prototypes
bool is_valid_key(string key);

int main(int argc, string argv[])
{
    // STEP 1: Validate command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (!is_valid_key(argv[1]))
    {
        // Specific error messages are often helpful for debugging, 
        // but check50 usually looks for a return 1.
        printf("Key must contain 26 unique alphabetic characters.\n");
        return 1;
    }

    string key = argv[1];

    // STEP 2: Get the plaintext from the user
    string plaintext = get_string("plaintext:  ");

    // STEP 3: Encrypt and print ciphertext
    printf("ciphertext: ");

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isupper(plaintext[i]))
        {
            // Find alphabet position (0-25)
            int index = plaintext[i] - 'A';
            // Output key character in uppercase
            printf("%c", toupper(key[index]));
        }
        else if (islower(plaintext[i]))
        {
            // Find alphabet position (0-25)
            int index = plaintext[i] - 'a';
            // Output key character in lowercase
            printf("%c", tolower(key[index]));
        }
        else
        {
            // Non-alphabetic characters remain unchanged
            printf("%c", plaintext[i]);
        }
    }

    printf("\n");
    return 0;
}

// Validate the encryption key
bool is_valid_key(string key)
{
    // Check length
    if (strlen(key) != 26)
    {
        return false;
    }

    bool seen[26] = {false};

    for (int i = 0; i < 26; i++)
    {
        // Check if characters are alphabetic
        if (!isalpha(key[i]))
        {
            return false;
        }

        // Check for duplicates (case-insensitive)
        int index = tolower(key[i]) - 'a';
        if (seen[index])
        {
            return false;
        }
        seen[index] = true;
    }

    return true;
}
