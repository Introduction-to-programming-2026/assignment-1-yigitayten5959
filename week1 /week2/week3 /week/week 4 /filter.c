// CS50x Week 4 — Filter (Less): filter.c
// ⚠️  DO NOT MODIFY THIS FILE
// Distribution code provided by CS50.

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"
#include "helpers.h"

int main(int argc, char *argv[])
{
    // Define the valid filter flags: (b)lur, (g)rayscale, (r)eflect, (s)epia
    char *filters = "bgrs";

    // Parse command-line flag using getopt
    char filter = getopt(argc, argv, filters);
    if (filter == '?')
    {
        fprintf(stderr, "Invalid filter flag.\n");
        return 1;
    }

    // Ensure the user didn't try to use more than one filter at once
    if (getopt(argc, argv, filters) != -1)
    {
        fprintf(stderr, "Only one filter can be applied at a time.\n");
        return 2;
    }

    // Ensure the user provided both an input and output filename
    if (argc != optind + 2)
    {
        fprintf(stderr, "Usage: ./filter [flag] infile outfile\n");
        return 3;
    }

    // Assign filenames to pointers
    char *infile = argv[optind];
    char *outfile = argv[optind + 1];

    // Open the input BMP file for reading
    FILE *inptr = fopen(infile, "rb");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open file: %s\n", infile);
        return 4;
    }

    // Open the output BMP file for writing
    FILE *outptr = fopen(outfile, "wb");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create file: %s\n", outfile);
        return 5;
    }

    // Read the File Header from the input file
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Read the Info Header from the input file
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Verify the file is a standard 24-bit uncompressed BMP
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format. Only 24-bit BMPs are supported.\n");
        return 6;
    }

    // Store image dimensions
    int height = abs(bi.biHeight);
    int width = bi.biWidth;

    // Allocate memory to store the entire image in a 2D array of pixels (RGBTRIPLEs)
    RGBTRIPLE(*image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (image == NULL)
    {
        fprintf(stderr, "Not enough memory to load the image.\n");
        fclose(outptr);
        fclose(inptr);
        return 7;
    }

    // Calculate padding for scanlines (BMP rows must be multiples of 4 bytes)
    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

    // Read pixels from the input file row by row
    for (int i = 0; i < height; i++)
    {
        // Read the row of pixels
        fread(image[i], sizeof(RGBTRIPLE), width, inptr);
        // Skip over the padding bytes in the input file
        fseek(inptr, padding, SEEK_CUR);
    }

    // Call the appropriate filter function based on the user's flag
    switch (filter)
    {
        case 'b':
            blur(height, width, image);
            break;
        case 'g':
            grayscale(height, width, image);
            break;
        case 'r':
            reflect(height, width, image);
            break;
        case 's':
            sepia(height, width, image);
            break;
    }

    // Write the File Header to the output file
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Write the Info Header to the output file
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Write the modified pixels to the output file row by row
    for (int i = 0; i < height; i++)
    {
        // Write the row of filtered pixels
        fwrite(image[i], sizeof(RGBTRIPLE), width, outptr);
        // Add BMP padding back to the end of each row
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // Clean up: free allocated memory and close all file pointers
    free(image);
    fclose(inptr);
    fclose(outptr);
    return 0;
}
