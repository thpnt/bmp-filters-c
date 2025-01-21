#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    int mean;
    uint8_t grayscale_value;

    // Loop through pixels
    for (int h = 0; h<height; h++) // Loop through rows
    {
        for (int w = 0; w<width; w++) // Loop through columns
        {
            // Compute mean RGB value
            mean = (image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3;
            grayscale_value = (uint8_t)mean;

            // Reassign new values
            image[h][w].rgbtBlue = grayscale_value;
            image[h][w].rgbtGreen = grayscale_value;
            image[h][w].rgbtRed = grayscale_value;

        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through rows
    for (int h=0; h<height; h++)
    {
        // allocate memory for new row
        RGBTRIPLE *new_row = calloc(width, sizeof(RGBTRIPLE));

        // Memory allocation error
        if (new_row == NULL) {
            return;
        }

        // Loop through columns
        for (int w=0; w<width; w++)
        {
            // Flip the array using new_row
            new_row[w].rgbtBlue = image[h][width-(w+1)].rgbtBlue;
            new_row[w].rgbtGreen = image[h][width-(w+1)].rgbtGreen;
            new_row[w].rgbtRed = image[h][width-(w+1)].rgbtRed;
        }

        // Swap original image row with new_row
        for (int w = 0; w < width; w++)
        {
            image[h][w] = new_row[w];
        }


    free(new_row);
    }
    return;
}



// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Allocate memory for temporary image
    RGBTRIPLE (*temp_img)[width] = calloc(height, sizeof(RGBTRIPLE) * width);

    // Memory allocation error check
    if (temp_img == NULL)
    {
        return;
    }

    // Loop through each pixel in the image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Initialize sums for RGB values and a neighbor count
            int blue_sum = 0;
            int green_sum = 0;
            int red_sum = 0;
            int neighbor_count = 0;

            // Loop through the 3x3 grid of neighbors
            for (int nh = -1; nh <= 1; nh++)
            {
                for (int nw = -1; nw <= 1; nw++)
                {
                    int neighbor_h = h + nh;
                    int neighbor_w = w + nw;

                    // Check if the neighbor is within bounds
                    if (neighbor_h >= 0 && neighbor_h < height && neighbor_w >= 0 && neighbor_w < width)
                    {
                        // Add neighbor's RGB values to the sums
                        blue_sum += image[neighbor_h][neighbor_w].rgbtBlue;
                        green_sum += image[neighbor_h][neighbor_w].rgbtGreen;
                        red_sum += image[neighbor_h][neighbor_w].rgbtRed;

                        // Increment the neighbor count
                        neighbor_count++;
                    }
                }
            }

            // Compute the average RGB values and store them in the temporary image
            temp_img[h][w].rgbtBlue = (uint8_t)(blue_sum / neighbor_count);
            temp_img[h][w].rgbtGreen = (uint8_t)(green_sum / neighbor_count);
            temp_img[h][w].rgbtRed = (uint8_t)(red_sum / neighbor_count);
        }
    }

    // Copy the blurred values from temp_img back into the original image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = temp_img[h][w];
        }
    }

    // Free the allocated memory for temp_img
    free(temp_img);

    return;
}




// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
