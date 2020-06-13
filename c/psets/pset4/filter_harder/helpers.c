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
            float rgbAvg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00;

            // Set RGB values to average for all three to create grayscale
            image[i][j].rgbtBlue = roundf(rgbAvg);
            image[i][j].rgbtGreen = roundf(rgbAvg);
            image[i][j].rgbtRed = roundf(rgbAvg);
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
            float sepiaRed = roundf(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            float sepiaGreen = roundf(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            float sepiaBlue = roundf(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
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
            float blueAvg = 0;
            float blueSum = 0;
            float greenAvg = 0;
            float greenSum = 0;
            float redAvg = 0;
            float redSum = 0;
            float totalNeighbors = 0;

            // Loop through surrounding pixels
            for (int k = -1; k < 2; k++)
            {
                if (i + k < 0 || i + k >= height)
                {
                    continue;
                }

                for (int m = -1; m < 2; m++)
                {
                    if (j + m < 0 || j + m >= width)
                    {
                        continue;
                    }

                    blueSum += image[i + k][j + m].rgbtBlue;
                    greenSum += image[i + k][j + m].rgbtGreen;
                    redSum += image[i + k][j + m].rgbtRed;

                    totalNeighbors++;                    
                }
            }

            // Calculate average 
            blueAvg = roundf(blueSum / totalNeighbors);
            greenAvg = roundf(greenSum / totalNeighbors);
            redAvg = roundf(redSum / totalNeighbors);

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create temporary RGBTRIPLE to store new values
    RGBTRIPLE edgedImage[height][width];

    // Initialize variables for Sobel calculations
    float xMult = 0.00;
    float yMult = 0.00;
    float blueGx = 0.00;
    float blueGy = 0.00;
    float greenGx = 0.00;
    float greenGy = 0.00;
    float redGx = 0.00;
    float redGy = 0.00;
    float blueSobelValue = 0.00;
    float greenSobelValue = 0.00;
    float redSobelValue = 0.00;

    // Loop through every pixel of image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Reset counters used for Sobel calculation
            blueGx = 0.00;
            blueGy = 0.00;
            greenGx = 0.00;
            greenGy = 0.00;
            redGx = 0.00;
            redGy = 0.00;

            // Loop through surrounding pixels
            for (int k = -1; k < 2; k++)
            {
                if (i + k < 0 || i + k >= height)
                {
                    continue;
                }

                for (int m = -1; m < 2; m++)
                {
                    if (j + m < 0 || j + m >= width)
                    {
                        continue;
                    }

                    // Set multipliers based on coordinates
                    if (k == -1 && m == -1)
                    {
                        xMult = -1.00;
                        yMult = 1.00;
                    } 

                    if (k == -1 && m == 0)
                    {
                        xMult = -2.00;
                        yMult = 0.00;                       
                    }

                    if (k == -1 && m == 1)
                    {
                        xMult = -1.00;
                        yMult = -1.00;                        
                    }     

                    if (k == 0 && m == -1)
                    {
                        xMult = 0.00;
                        yMult = 2.00;
                    } 

                    if (k == 0 && m == 0)
                    {
                        xMult = 0.00;
                        yMult = 0.00;                        
                    }

                    if (k == 0 && m == 1)
                    {
                        xMult = 0.00;
                        yMult = -2.00;                        
                    }         

                    if (k == 1 && m == -1)
                    {
                        xMult = 1.00;
                        yMult = 1.00;
                    } 

                    if (k == 1 && m == 0)
                    {
                        xMult = 2.00;
                        yMult = 0.00;                        
                    }

                    if (k == 1 && m == 1)
                    {
                        xMult = 1.00;
                        yMult = -1.00;                        
                    }

                    // Add to running Gx sum for each color by using the determined x multiplier
                    blueGx += (image[i + k][j + m].rgbtBlue) * xMult;
                    greenGx += (image[i + k][j + m].rgbtGreen) * xMult;
                    redGx += (image[i + k][j + m].rgbtRed) * xMult;

                    // Add to running Gy sum for each color by using the determined y multiplier
                    blueGy += (image[i + k][j + m].rgbtBlue) * yMult;
                    greenGy += (image[i + k][j + m].rgbtGreen) * yMult;
                    redGy += (image[i + k][j + m].rgbtRed) * yMult;      
                }
            }

        // Calculate Sobel value for each color
        blueSobelValue = roundf(sqrt((blueGx * blueGx) + (blueGy * blueGy)));
        greenSobelValue = roundf(sqrt((greenGx * greenGx) + (greenGy * greenGy)));
        redSobelValue = roundf(sqrt((redGx * redGx) + (redGy * redGy)));

        // Ensure no Sobel values are above 255 or below 0
        if (blueSobelValue > 255)
        {
            blueSobelValue = 255;
        }
        else if (blueSobelValue < 0)
        {
             blueSobelValue = 0;
        }

        if (greenSobelValue > 255)
        {
            greenSobelValue = 255;
        }
        else if (greenSobelValue < 0)
        {
             greenSobelValue = 0;
        }

        if (redSobelValue > 255)
        {
            redSobelValue = 255;
        }
        else if (redSobelValue < 0)
        {
             redSobelValue = 0;
        }
        
        // Set temporary image Struct with Sobel values for each color for this pixel
        edgedImage[i][j].rgbtBlue = blueSobelValue;
        edgedImage[i][j].rgbtGreen = greenSobelValue;
        edgedImage[i][j].rgbtRed = redSobelValue;

        }
    }

    // Loop through image again to replace RGB values for each pixel with edged values.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = edgedImage[i][j].rgbtBlue;
            image[i][j].rgbtGreen = edgedImage[i][j].rgbtGreen;
            image[i][j].rgbtRed = edgedImage[i][j].rgbtRed;
        }
    }

    return;
}
