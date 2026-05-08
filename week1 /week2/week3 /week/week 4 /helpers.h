// CS50x Week 4 — Filter (Less): helpers.h
// DO NOT MODIFY THIS FILE

#include "bmp.h"

/**
 * grayscale
 * ---------
 * Converts the provided image to grayscale by averaging RGB values.
 */
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

/**
 * sepia
 * -----
 * Applies a sepia filter by calculating new RGB values based on 
 * weighted sums of the original colors.
 */
void sepia(int height, int width, RGBTRIPLE image[height][width]);

/**
 * reflect
 * -------
 * Flips the image horizontally, effectively creating a mirror image.
 */
void reflect(int height, int width, RGBTRIPLE image[height][width]);

/**
 * blur
 * ----
 * Applies a box blur by averaging the color values of a 3x3 grid 
 * of neighboring pixels.
 */
void blur(int height, int width, RGBTRIPLE image[height][width]);
