#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    // Prompt user for height between 1 and 8 inclusive
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Loop through each row
    for (int row = 1; row <= height; row++)
    {
        // 1. Print leading spaces for the left pyramid
        for (int spaces = 0; spaces < height - row; spaces++)
        {
            printf(" ");
        }

        // 2. Print hashes for the left pyramid
        for (int hashes = 0; hashes < row; hashes++)
        {
            printf("#");
        }

        // 3. Print the constant two-space gap
        printf("  ");

        // 4. Print hashes for the right pyramid
        for (int hashes = 0; hashes < row; hashes++)
        {
            printf("#");
        }

        // Move to the next row
        printf("\n");
    }

    return 0;
}
