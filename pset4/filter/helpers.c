#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Converts images to greyscale by taking average of every rbg triplets and setting the rgb values to this new value
            float new_rgb = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = new_rgb;
            image[i][j].rgbtGreen = new_rgb;
            image[i][j].rgbtBlue = new_rgb;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (int)(width / 2); j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the image array so as to not consider values that have already been updated
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Loop over all the rows
    for (int i = 0; i < height; i++)
    {
        // Looping over each pixel
        for (int j = 0; j < width; j++)
        {
            // Initialize variables to store the sum of the colour values
            int redSum = 0, greenSum = 0, blueSum = 0;
            double counter = 0;
            // Iterate over each neighbouring pixel
            for (int a = i - 1; a <= i + 1; a++)
            {
                for (int b = j - 1; b <= j + 1; b++)
                {
                    // Condition to check if the pixel exists
                    if (a >= 0 && a < height && b >= 0 && b < width)
                    {
                        redSum += temp[a][b].rgbtRed;
                        blueSum += temp[a][b].rgbtBlue;
                        greenSum += temp[a][b].rgbtGreen;
                        counter++;
                    }
                }
            }

            // Setting the new rgb values
            image[i][j].rgbtRed = round(redSum / counter);
            image[i][j].rgbtBlue = round(blueSum / counter);
            image[i][j].rgbtGreen = round(greenSum / counter);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the image array so as to not consider values that have already been updated
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Initialize the Sobel kernels
    int gx_matrix[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy_matrix[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Iterating over every row
    for (int i = 0; i < height; i++)
    {
        // Iterating over every pixel
        for (int j = 0; j < width; j++)
        {
            double gx_red = 0, gy_red = 0, gx_green = 0, gy_green = 0, gx_blue = 0, gy_blue = 0;

            // Iterating over neighbouring pixels
            for (int a = i - 1, row = 0; a <= i + 1; a++, row++)
            {
                for (int b = j - 1, column = 0; b <= j + 1; b++, column++)
                {
                    // If it is not a border pixel and it exists
                    if (a >= 0 && a < height && b >= 0 && b < width)
                    {
                        // Calculte gx and gy values
                        gx_red += gx_matrix[row][column] * temp[a][b].rgbtRed;
                        gy_red += gy_matrix[row][column] * temp[a][b].rgbtRed;
                        gx_green += gx_matrix[row][column] * temp[a][b].rgbtGreen;
                        gy_green += gy_matrix[row][column] * temp[a][b].rgbtGreen;
                        gx_blue += gx_matrix[row][column] * temp[a][b].rgbtBlue;
                        gy_blue += gy_matrix[row][column] * temp[a][b].rgbtBlue;
                    }
                }
            }

            // Combining the gx and gy values into a single one
            int new_red = round(sqrt(pow(gx_red, 2) + pow(gy_red, 2)));
            int new_green = round(sqrt(pow(gx_green, 2) + pow(gy_green, 2)));
            int new_blue = round(sqrt(pow(gx_blue, 2) + pow(gy_blue, 2)));

            // Capping to 255
            if (new_red > 255)
            {
                new_red = 255;
            }
            if (new_green > 255)
            {
                new_green = 255;
            }
            if (new_blue > 255)
            {
                new_blue = 255;
            }

            // Setting the new values
            image[i][j].rgbtRed = (new_red < 255) ? new_red : 255;
            image[i][j].rgbtGreen = (new_green < 255) ? new_green : 255;
            image[i][j].rgbtBlue = (new_blue < 255) ? new_blue : 255;
        }
    }
    return;
}