#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    // Prompt for height until user provides a number between 1 and 8
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Outer loop handles the rows
    for (int row = 1; row <= height; row++)
    {
        // Inner loop 1: Print spaces
        // To right-align, we need (height - current row) spaces
        for (int spaces = 0; spaces < height - row; spaces++)
        {
            printf(" ");
        }

        // Inner loop 2: Print hashes
        // We need (current row) number of hashes
        for (int hashes = 0; hashes < row; hashes++)
        {
            printf("#");
        }

        // Move to the next line after finishing a row
        printf("\n");
    }

    return 0;
}
