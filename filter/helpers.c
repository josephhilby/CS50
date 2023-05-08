#include "helpers.h"
#include<math.h>

// Average the RGB value in pixle
BYTE avgGray(RGBTRIPLE pixle)
{
    float blue = pixle.rgbtBlue;
    float green = pixle.rgbtGreen;
    float red = pixle.rgbtRed;
    float avg = (blue + green + red) / 3;
    BYTE result = round(avg);
    return result;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h <= height; h++)
    {
        for (int w = 0; w <= width; w++)
        {
            BYTE newValue = avgGray(image[h][w]);
            image[h][w].rgbtBlue = newValue;
            image[h][w].rgbtGreen = newValue;
            image[h][w].rgbtRed = newValue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h <= height; h++)
    {
        for (int w = 0; w < width/2; w++)
        {
            RGBTRIPLE temp = image[h][w];
            image[h][w] = image[h][width - (w + 1)];
            image[h][width - (w + 1)] = temp;
        }
    }
}

// Average a given value by number of pixles
BYTE avg(float value, int count)
{
    float avg = value / count;
    BYTE result = round(avg);
    return result;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCopy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageCopy[i][j] = image[i][j];
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float sumRed = 0.0;
            float sumGreen = 0.0;
            float sumBlue = 0.0;
            int counter = 0;

            // Check the pixles above and below select pixle
            for (int ph = -1; ph < 2; ph++)
            {
                // Check the pixles left and right of select pixle
                for (int pw = -1; pw < 2; pw++)
                {
                    if (h + ph >= 0 && h + ph < height)
                    {
                        if (w + pw >= 0 && w + pw < width)
                        {
                            sumRed += imageCopy[h + ph][w + pw].rgbtRed;
                            sumGreen += imageCopy[h + ph][w + pw].rgbtGreen;
                            sumBlue += imageCopy[h + ph][w + pw].rgbtBlue;
                            counter++;
                        }
                    }
                }
            }
            image[h][w].rgbtRed = avg(sumRed, counter);
            image[h][w].rgbtGreen = avg(sumGreen, counter);
            image[h][w].rgbtBlue = avg(sumBlue, counter);
        }
    }
}

// Multiplys the RGB value against the given value in the Sobel matrix
// [[-1, 0, 1],
//  [-2, 0, 2],
//  [-1, 0, 1]]
// Line 169 creates a matrix of simular size around the select pixle with X axis orientation
// [[-1, 0, 1],
//  [-1, 0, 1],
//  [-1, 0, 1]]
int sobelValueX(int pixle, int height, int width)
{
    int multiplyer = width;
    if (height == 0)
    {
        multiplyer += width;
    }
    return pixle * multiplyer;
}

// Multiplys the RGB value against the given value in the Sobel matrix
// [[-1, -2, -1],
//  [ 0,  0,  0],
//  [ 1,  2,  1]]
// Line 166 creates a matrix of simular size around the select pixle with Y axis orientation
// [[-1, -1, -1]
//  [ 0,  0,  0],
//  [ 1,  1,  1]]
int sobelValueY(int pixle, int height, int width)
{
    int multiplyer = height;
    if (width == 0)
    {
        multiplyer += height;
    }
    return pixle * multiplyer;
}

int check255(int value)
{
    if (value > 255)
    {
        return 255;
    }
    else
    {
        return value;
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCopy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageCopy[i][j] = image[i][j];
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Store Sobel values by [RGB][X/Y Axis]
            float sobelValuesRGB[3][2]= {{0, 0}, {0, 0}, {0, 0}};

            // Check the pixles above and below select pixle
            for (int ph = -1; ph < 2; ph++)
            {
                // Check the pixles left and right of select pixle
                for (int pw = -1; pw < 2; pw++)
                {
                    if (h + ph >= 0 && h + ph < height)
                    {
                        if (w + pw >= 0 && w + pw < width)
                        {
                            // Sobel edge detection x-axis
                            sobelValuesRGB[0][0] += sobelValueX(imageCopy[h + ph][w + pw].rgbtRed, ph, pw);
                            sobelValuesRGB[1][0] += sobelValueX(imageCopy[h + ph][w + pw].rgbtGreen, ph, pw);
                            sobelValuesRGB[2][0] += sobelValueX(imageCopy[h + ph][w + pw].rgbtBlue, ph, pw);

                            // Sobel edge detection y-axis
                            sobelValuesRGB[0][1] += sobelValueY(imageCopy[h + ph][w + pw].rgbtRed, ph, pw);
                            sobelValuesRGB[1][1] += sobelValueY(imageCopy[h + ph][w + pw].rgbtGreen, ph, pw);
                            sobelValuesRGB[2][1] += sobelValueY(imageCopy[h + ph][w + pw].rgbtBlue, ph, pw);
                        }
                    }
                }
            }

            int redSobel = round(sqrt((sobelValuesRGB[0][0] * sobelValuesRGB[0][0]) + (sobelValuesRGB[0][1] * sobelValuesRGB[0][1])));
            int greenSobel = round(sqrt((sobelValuesRGB[1][0] * sobelValuesRGB[1][0]) + (sobelValuesRGB[1][1] * sobelValuesRGB[1][1])));
            int blueSobel = round(sqrt((sobelValuesRGB[2][0] * sobelValuesRGB[2][0]) + (sobelValuesRGB[2][1] * sobelValuesRGB[2][1])));


            image[h][w].rgbtRed = check255(redSobel);
            image[h][w].rgbtGreen = check255(greenSobel);
            image[h][w].rgbtBlue = check255(blueSobel);
        }
    }
}
