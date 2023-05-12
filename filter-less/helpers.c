#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            average = (int)round(average);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaBlue = (int)round(.131 * image[i][j].rgbtBlue + .534 * image[i][j].rgbtGreen + .272 * image[i][j].rgbtRed);
            sepiaGreen = (int)round(.168 * image[i][j].rgbtBlue + .686 * image[i][j].rgbtGreen + .349 * image[i][j].rgbtRed);
            sepiaRed = (int)round(.189 * image[i][j].rgbtBlue + .769 * image[i][j].rgbtGreen + .393 * image[i][j].rgbtRed);

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    int mid = width / 2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < mid; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy of the image array so the already blurred pixels dont affect the others
    RGBTRIPLE copy[height][width];
    float average_blue;
    float average_green;
    float average_red;
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            average_blue = 0;
            average_green = 0;
            average_red = 0;
            // Top left corner
            if (row == 0 && column == 0)
            {
                for (int i = row; i < row + 2; i++)
                {
                    for (int j = column; j < column + 2; j++)
                    {
                        // Sum of each color
                        average_blue += image[i][j].rgbtBlue;
                        average_green += image[i][j].rgbtGreen;
                        average_red += image[i][j].rgbtRed;
                    }
                }
                // Average rgb value
                average_blue = (int)round(average_blue / 4);
                average_green = (int)round(average_green / 4);
                average_red = (int)round(average_red / 4);
                // Copy the rgb values to the aux array
                copy[row][column].rgbtBlue = average_blue;
                copy[row][column].rgbtGreen = average_green;
                copy[row][column].rgbtRed = average_red;
            }
            // Top row
            else if (row == 0 && column != 0 && column != width - 1)
            {
                for (int i = row; i < row + 2; i++)
                {
                    for (int j = column - 1; j < column + 2; j++)
                    {
                        // Sum of each color
                        average_blue += image[i][j].rgbtBlue;
                        average_green += image[i][j].rgbtGreen;
                        average_red += image[i][j].rgbtRed;
                    }
                }
                // Average rgb value
                average_blue = (int)round(average_blue / 6);
                average_green = (int)round(average_green / 6);
                average_red = (int)round(average_red / 6);
                // Copy the rgb values to the aux array
                copy[row][column].rgbtBlue = average_blue;
                copy[row][column].rgbtGreen = average_green;
                copy[row][column].rgbtRed = average_red;
            }
            // Top right corner
            else if (row == 0 && column == width - 1)
            {
                for (int i = row; i < row + 2; i++)
                {
                    for (int j = column - 1; j < column + 1; j++)
                    {
                        // Sum of each color
                        average_blue += image[i][j].rgbtBlue;
                        average_green += image[i][j].rgbtGreen;
                        average_red += image[i][j].rgbtRed;
                    }
                }
                // Average rgb value
                average_blue = (int)round(average_blue / 4);
                average_green = (int)round(average_green / 4);
                average_red = (int)round(average_red / 4);
                // Copy the rgb values to the aux array
                copy[row][column].rgbtBlue = average_blue;
                copy[row][column].rgbtGreen = average_green;
                copy[row][column].rgbtRed = average_red;
            }
            // Left column
            else if (column == 0 && row != 0 && row != height - 1)
            {
                for (int i = row - 1; i < row + 2; i++)
                {
                    for (int j = column; j < column + 2; j++)
                    {
                        // Sum of each color
                        average_blue += image[i][j].rgbtBlue;
                        average_green += image[i][j].rgbtGreen;
                        average_red += image[i][j].rgbtRed;
                    }
                }
                // Average rgb value
                average_blue = (int)round(average_blue / 6);
                average_green = (int)round(average_green / 6);
                average_red = (int)round(average_red / 6);
                // Copy the rgb values to the aux array
                copy[row][column].rgbtBlue = average_blue;
                copy[row][column].rgbtGreen = average_green;
                copy[row][column].rgbtRed = average_red;
            }
            // Right column
            else if (column == width - 1 && row != 0 && row != height - 1)
            {
                for (int i = row - 1; i < row + 2; i++)
                {
                    for (int j = column - 1; j < column + 1; j++)
                    {
                        // Sum of each color
                        average_blue += image[i][j].rgbtBlue;
                        average_green += image[i][j].rgbtGreen;
                        average_red += image[i][j].rgbtRed;
                    }
                }
                // Average rgb value
                average_blue = (int)round(average_blue / 6);
                average_green = (int)round(average_green / 6);
                average_red = (int)round(average_red / 6);
                // Copy the rgb values to the aux array
                copy[row][column].rgbtBlue = average_blue;
                copy[row][column].rgbtGreen = average_green;
                copy[row][column].rgbtRed = average_red;
            }
            // Bottom left corner
            else if (row == height - 1 && column == 0)
            {
                for (int i = row - 1; i < row + 1; i++)
                {
                    for (int j = column; j < column + 2; j++)
                    {
                        // Sum of each color
                        average_blue += image[i][j].rgbtBlue;
                        average_green += image[i][j].rgbtGreen;
                        average_red += image[i][j].rgbtRed;
                    }
                }
                // Average rgb value
                average_blue = (int)round(average_blue / 4);
                average_green = (int)round(average_green / 4);
                average_red = (int)round(average_red / 4);
                // Copy the rgb values to the aux array
                copy[row][column].rgbtBlue = average_blue;
                copy[row][column].rgbtGreen = average_green;
                copy[row][column].rgbtRed = average_red;
            }
            // Bottom row
            else if (row == height - 1 && column != 0 && column != width - 1)
            {
                for (int i = row - 1; i < row + 1; i++)
                {
                    for (int j = column - 1; j < column + 2; j++)
                    {
                        // Sum of each color
                        average_blue += image[i][j].rgbtBlue;
                        average_green += image[i][j].rgbtGreen;
                        average_red += image[i][j].rgbtRed;
                    }
                }
                // Average rgb value
                average_blue = (int)round(average_blue / 6);
                average_green = (int)round(average_green / 6);
                average_red = (int)round(average_red / 6);
                // Copy the rgb values to the aux array
                copy[row][column].rgbtBlue = average_blue;
                copy[row][column].rgbtGreen = average_green;
                copy[row][column].rgbtRed = average_red;
            }
            // Bottom right corner
            else if (row == height - 1 && column == width - 1)
            {
                for (int i = row - 1; i < row + 1; i++)
                {
                    for (int j = column - 1; j < column + 1; j++)
                    {
                        // Sum of each color
                        average_blue += image[i][j].rgbtBlue;
                        average_green += image[i][j].rgbtGreen;
                        average_red += image[i][j].rgbtRed;
                    }
                }
                // Average rgb value
                average_blue = (int)round(average_blue / 4);
                average_green = (int)round(average_green / 4);
                average_red = (int)round(average_red / 4);
                // Copy the rgb values to the aux array
                copy[row][column].rgbtBlue = average_blue;
                copy[row][column].rgbtGreen = average_green;
                copy[row][column].rgbtRed = average_red;
            }
            else if (row != 0 && row != height - 1 && column != 0 && column != width - 1)
            {
                for (int i = row - 1; i < row + 2; i++)
                {
                    for (int j = column - 1; j < column + 2; j++)
                    {
                        // Sum of each color
                        average_blue += image[i][j].rgbtBlue;
                        average_green += image[i][j].rgbtGreen;
                        average_red += image[i][j].rgbtRed;
                    }
                }
                // Average rgb value
                average_blue = (int)round(average_blue / 9);
                average_green = (int)round(average_green / 9);
                average_red = (int)round(average_red / 9);
                // Copy the rgb values to the aux array
                copy[row][column].rgbtBlue = average_blue;
                copy[row][column].rgbtGreen = average_green;
                copy[row][column].rgbtRed = average_red;
            }
        }
    }
    // Copy the blurred oixels to the original array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
        }
    }
    return;
}
