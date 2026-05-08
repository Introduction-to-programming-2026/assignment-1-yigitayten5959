#include "helpers.h"
#include <math.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average of Red, Green, and Blue
            // We divide by 3.0 to ensure floating-point division
            float average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            int rounded_avg = round(average);

            // Set all color channels to the same average value
            image[i][j].rgbtRed = rounded_avg;
            image[i][j].rgbtGreen = rounded_avg;
            image[i][j].rgbtBlue = rounded_avg;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Store original values
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // Compute sepia values using the formula
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            // Cap values at 255 if they exceed the maximum byte limit
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // Only loop through half the width to swap left and right
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels using a temporary variable
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the image to read original pixel values
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float totalRed = 0, totalGreen = 0, totalBlue = 0;
            float counter = 0.00;

            // Iterate over the 3x3 grid surrounding the pixel
            for (int r = -1; r <= 1; r++)
            {
                for (int c = -1; c <= 1; c++)
                {
                    int neighborRow = i + r;
                    int neighborCol = j + c;

                    // Check if the neighbor pixel is within image bounds
                    if (neighborRow >= 0 && neighborRow < height && neighborCol >= 0 && neighborCol < width)
                    {
                        totalRed += copy[neighborRow][neighborCol].rgbtRed;
                        totalGreen += copy[neighborRow][neighborCol].rgbtGreen;
                        totalBlue += copy[neighborRow][neighborCol].rgbtBlue;
                        counter++;
                    }
                }
            }

            // Calculate the average and update the original image
            image[i][j].rgbtRed = round(totalRed / counter);
            image[i][j].rgbtGreen = round(totalGreen / counter);
            image[i][j].rgbtBlue = round(totalBlue / counter);
        }
    }
}
