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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int GxGreen, GxRed, GxBlue, GyGreen, GyRed, GyBlue;
    int Green, Blue, Red;
    // Copy of the image array so the already blurred pixels dont affect the others
    RGBTRIPLE copy[height][width];
    // Gx and Gy kernels from top left to bottom right
    int Gx[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int Gy[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    // Position in the kernel / around the pixel
    int pos;
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            // Reset all the variables
            GxGreen = 0;
            GxRed = 0;
            GxBlue = 0;
            GyGreen = 0;
            GyRed = 0;
            GyBlue = 0;
            pos = 0;
            for (int i = row - 1; i < row + 2; i++)
            {
                for (int j = column - 1; j < column + 2; j++)
                {
                    // Black border
                    if (i < 0 || i > height - 1 || j < 0 || j > width - 1)
                    {
                        pos++;
                    }
                    else
                    {
                        GxGreen += image[i][j].rgbtGreen * Gx[pos];
                        GxRed += image[i][j].rgbtRed * Gx[pos];
                        GxBlue += image[i][j].rgbtBlue * Gx[pos];
                        GyGreen += image[i][j].rgbtGreen * Gy[pos];
                        GyRed += image[i][j].rgbtRed * Gy[pos];
                        GyBlue += image[i][j].rgbtBlue * Gy[pos];
                        pos++;
                    }

                }
            }
            // Sobel filter algorithm
            Green = (int)round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
            Red = (int)round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
            Blue = (int)round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
            if (Green > 255)
            {
                Green = 255;
            }
            if (Red > 255)
            {
                Red = 255;
            }
            if (Blue > 255)
            {
                Blue = 255;
            }
            copy[row][column].rgbtGreen = Green;
            copy[row][column].rgbtRed = Red;
            copy[row][column].rgbtBlue = Blue;
        }
    }

    // Copy the blurred pixels to the original array
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
