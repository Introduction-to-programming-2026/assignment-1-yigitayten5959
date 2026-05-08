#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    // STEP 1: Validate command-line arguments
    // Check if user provided exactly one argument and if it's numeric
    if (argc != 2 || !only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // STEP 2: Convert the key from string to int
    int key = atoi(argv[1]);

    // STEP 3: Get the plaintext from the user
    string plaintext = get_string("plaintext:  ");

    // STEP 4: Encrypt and print the ciphertext
    printf("ciphertext: ");

    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        // Rotate each character and print it
        printf("%c", rotate(plaintext[i], key));
    }

    // Print a newline at the very end
    printf("\n");
    return 0;
}

// Check if the string consists only of digits
bool only_digits(string s)
{
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

// Rotate character c by n positions
char rotate(char c, int n)
{
    if (isupper(c))
    {
        // Shift 'A' to 0, add key, wrap with % 26, shift back to ASCII 'A'
        return (c - 'A' + n) % 26 + 'A';
    }
    else if (islower(c))
    {
        // Shift 'a' to 0, add key, wrap with % 26, shift back to ASCII 'a'
        return (c - 'a' + n) % 26 + 'a';
    }
    
    // If not a letter, return unchanged
    return c;
}
