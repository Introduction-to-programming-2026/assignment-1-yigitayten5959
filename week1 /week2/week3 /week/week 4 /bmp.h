// CS50x Week 4 — BMP type definitions (distribution code)
// DO NOT MODIFY THIS FILE

#include <stdint.h>

/**
 * Common data types used in BMP file structures.
 * These aliases make the code more readable and match 
 * the Microsoft BMP documentation.
 */
typedef uint8_t  BYTE;
typedef uint32_t DWORD;
typedef int32_t  LONG;
typedef uint16_t WORD;

/**
 * BITMAPFILEHEADER
 * * The first 14 bytes of the file. 
 * Contains general information about the file type and size.
 */
typedef struct
{
    WORD  bfType;      // "BM" (0x4D42) identifies the file as a BMP
    DWORD bfSize;      // Total size of the file in bytes
    WORD  bfReserved1; // Reserved; must be zero
    WORD  bfReserved2; // Reserved; must be zero
    DWORD bfOffBits;   // The offset (starting address) where the pixel data begins
} __attribute__((__packed__))
BITMAPFILEHEADER;

/**
 * BITMAPINFOHEADER
 * * The next 40 bytes. 
 * Contains detailed information about the image (dimensions, color depth, etc).
 */
typedef struct
{
    DWORD biSize;          // Size of this header (40 bytes)
    LONG  biWidth;         // Width of the image in pixels
    LONG  biHeight;        // Height of the image in pixels
    WORD  biPlanes;        // Number of color planes (must be 1)
    WORD  biBitCount;      // Bits per pixel (usually 24 for RGB)
    DWORD biCompression;   // Compression type (0 for none)
    DWORD biSizeImage;     // Size of the raw bitmap data (including padding)
    LONG  biXPelsPerMeter; // Horizontal resolution
    LONG  biYPelsPerMeter; // Vertical resolution
    DWORD biClrUsed;       // Number of colors in the color palette
    DWORD biClrImportant;  // Number of important colors
} __attribute__((__packed__))
BITMAPINFOHEADER;

/**
 * RGBTRIPLE
 * * Represents a single pixel in a 24-bit color image.
 * BMP files store colors in BGR order (Blue, Green, Red).
 */
typedef struct
{
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
} __attribute__((__packed__))
RGBTRIPLE;
