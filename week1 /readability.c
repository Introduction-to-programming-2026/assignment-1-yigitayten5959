#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Function prototypes
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count letters, words, and sentences
    int letters   = count_letters(text);
    int words     = count_words(text);
    int sentences = count_sentences(text);

    // Compute L and S (averages per 100 words)
    // We use (float) to ensure the division doesn't truncate decimals
    float L = (float) letters / words * 100;
    float S = (float) sentences / words * 100;

    // Apply the Coleman-Liau formula
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(index);

    // Print the grade level output
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

// Count alphabetical characters only
int count_letters(string text)
{
    int count = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}

// Count words based on the number of spaces
int count_words(string text)
{
    int count = 1; // Assume at least one word exists
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }
    return count;
}

// Count sentences based on punctuation (., !, ?)
int count_sentences(string text)
{
    int count = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}
