#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average of Blue, Green, Red values
            float rgbAvg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;

            // Set RGB values to average for all three to create grayscale
            image[i][j].rgbtBlue = round(rgbAvg);
            image[i][j].rgbtGreen = round(rgbAvg);
            image[i][j].rgbtRed = round(rgbAvg);
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate RGB values for sepia colors
            int sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            int sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            int sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Set pixels to sepia colors
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, half_width = width / 2; j < half_width; j++)
        {
            int last_pixel = width - 1 - j;

            // Temp storage for first pixel
            RGBTRIPLE firstPixel;
            firstPixel.rgbtBlue = image[i][j].rgbtBlue;
            firstPixel.rgbtGreen = image[i][j].rgbtGreen;
            firstPixel.rgbtRed = image[i][j].rgbtRed;

            // Temp storage for last pixel
            RGBTRIPLE lastPixel;
            lastPixel.rgbtBlue = image[i][last_pixel].rgbtBlue;
            lastPixel.rgbtGreen = image[i][last_pixel].rgbtGreen;
            lastPixel.rgbtRed = image[i][last_pixel].rgbtRed;

            // Set first pixel with values from last pixel
            image[i][j].rgbtBlue = lastPixel.rgbtBlue;
            image[i][j].rgbtGreen = lastPixel.rgbtGreen;
            image[i][j].rgbtRed = lastPixel.rgbtRed;

            // Set last pixel with values from first pixel
            image[i][last_pixel].rgbtBlue = firstPixel.rgbtBlue;
            image[i][last_pixel].rgbtGreen = firstPixel.rgbtGreen;
            image[i][last_pixel].rgbtRed = firstPixel.rgbtRed;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create temporary RGBTRIPLE to store new values
    RGBTRIPLE blurImage[height][width];

    // Loop through every pixel of image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Create variables needed to keep track of totals and create averages
            int blueAvg = 0;
            int blueSum = 0;
            int greenAvg = 0;
            int greenSum = 0;
            int redAvg = 0;
            int redSum = 0;
            int totalNeighbors = 0;

            // Add values for the pixel itself
            blueSum += image[i][j].rgbtBlue;
            greenSum += image[i][j].rgbtGreen;
            redSum += image[i][j].rgbtRed;
            totalNeighbors++;

            // If pixel is NOT on a bottom edge
            if (!(i - 1 < 0))
            {
                blueSum += image[i - 1][j].rgbtBlue;
                greenSum += image[i - 1][j].rgbtGreen;
                redSum += image[i - 1][j].rgbtRed;
                totalNeighbors++;

                // If pixel is not on a right edge
                if (!(j + 1 > width))
                {
                    blueSum += image[i - 1][j + 1].rgbtBlue;
                    greenSum += image[i - 1][j + 1].rgbtGreen;
                    redSum += image[i - 1][j + 1].rgbtRed;
                    totalNeighbors++;

                    blueSum += image[i][j + 1].rgbtBlue;
                    greenSum += image[i][j + 1].rgbtGreen;
                    redSum += image[i][j + 1].rgbtRed;
                    totalNeighbors++;
                }

                // If pixel is not on a left edge
                if (!(j - 1 < 0))
                {
                    blueSum += image[i - 1][j - 1].rgbtBlue;
                    greenSum += image[i - 1][j - 1].rgbtGreen;
                    redSum += image[i - 1][j - 1].rgbtRed;
                    totalNeighbors++;

                    blueSum += image[i][j - 1].rgbtBlue;
                    greenSum += image[i][j - 1].rgbtGreen;
                    redSum += image[i][j - 1].rgbtRed;
                    totalNeighbors++;
                }
            }

            // If pixel is not on a top edge
            if (!(i + 1 > height))
            {
                blueSum += image[i + 1][j].rgbtBlue;
                greenSum += image[i + 1][j].rgbtGreen;
                redSum += image[i + 1][j].rgbtRed;
                totalNeighbors++;

                // If the pixel is not on a right edge
                if (!(j + 1 > width))
                {
                    blueSum += image[i + 1][j + 1].rgbtBlue;
                    greenSum += image[i + 1][j + 1].rgbtGreen;
                    redSum += image[i + 1][j + 1].rgbtRed;
                    totalNeighbors++;
                }

                // If the pixel is not on a left edge
                if (!(j - 1 < 0))
                {
                    blueSum += image[i + 1][j - 1].rgbtBlue;
                    greenSum += image[i + 1][j - 1].rgbtGreen;
                    redSum += image[i + 1][j - 1].rgbtRed;
                    totalNeighbors++;
                }
            }
        
            // Calculate average 
            blueAvg = blueSum / totalNeighbors;
            greenAvg = greenSum / totalNeighbors;
            redAvg = redSum / totalNeighbors;

            // Set temporary RGBTRIPLE struct with blurred values
            blurImage[i][j].rgbtBlue = blueAvg;
            blurImage[i][j].rgbtGreen = greenAvg;
            blurImage[i][j].rgbtRed = redAvg;
        }
    }

    // Loop through image again to replace RGB values for each pixel with blurred values.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = blurImage[i][j].rgbtBlue;
            image[i][j].rgbtGreen = blurImage[i][j].rgbtGreen;
            image[i][j].rgbtRed = blurImage[i][j].rgbtRed;
        }
    }

    return;
}