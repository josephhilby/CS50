// File provided by CS50 staff for use in programming assignments
#include "bmp.h"

// Convert image to grayscale
// ./filter -g images/<infile>.bmp <outfile>.bmp
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

// Reflect image horizontally
// ./filter -r images/<infile>.bmp <outfile>.bmp
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// Detect edges
// ./filter -e images/<infile>.bmp <outfile>.bmp
void edges(int height, int width, RGBTRIPLE image[height][width]);

// Blur image
// ./filter -b images/<infile>.bmp <outfile>.bmp
void blur(int height, int width, RGBTRIPLE image[height][width]);

