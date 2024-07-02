#include "helpers.h"
#include <math.h>

int less_than(int n1, int n2);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average_r, average_g, average_b;
    int average_rgb;

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green and blue
            average_r = image[i][j].rgbtRed;
            average_g = image[i][j].rgbtGreen;
            average_b = image[i][j].rgbtBlue;
            average_rgb = (int) round((average_r + average_g + average_b) / 3.0);

            // Update pixel values
            image[i][j].rgbtRed = average_rgb;
            image[i][j].rgbtGreen = average_rgb;
            image[i][j].rgbtBlue = average_rgb;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    const int MAXIMUM_VALUE = 255;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Complete sepia values
            int sepiaRed = (int) (round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                                        .189 * image[i][j].rgbtBlue));
            int sepiaGreen =
                (int) (round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                             .168 * image[i][j].rgbtBlue));
            int sepiaBlue = (int) (round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                                         .131 * image[i][j].rgbtBlue));

            // Update pixel with sepia values
            sepiaRed = less_than(sepiaRed, MAXIMUM_VALUE);
            sepiaGreen = less_than(sepiaGreen, MAXIMUM_VALUE);
            sepiaBlue = less_than(sepiaBlue, MAXIMUM_VALUE);

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            // Swap pixels
            RGBTRIPLE temp = image[i][width - 1 - j];
            image[i][width - 1 - j] = image[i][j];
            image[i][j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Temp of average values

    int avgRed[height][width];
    int avgGreen[height][width];
    int avgBlue[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Corner cases
            // Top left
            if (i == 0 && j == 0)
            {
                avgRed[i][j] = (int) (round(copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                            copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                                      4.0);
                avgGreen[i][j] =
                    (int) (round(copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                 copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                           4.0);
                avgBlue[i][j] =
                    (int) (round(copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                 copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) /
                           4.0);
            }

            // Top right
            else if (i == 0 && j == width - 1)
            {
                avgRed[i][j] = (int) (round(copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed +
                                            copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed) /
                                      4.0);
                avgGreen[i][j] =
                    (int) (round(copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen +
                                 copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) /
                           4.0);
                avgBlue[i][j] =
                    (int) (round(copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue +
                                 copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) /
                           4.0);
            }

            // Bottom left
            else if (i == height - 1 && j == 0)
            {
                avgRed[i][j] = (int) (round(copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                            copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed) /
                                      4.0);
                avgGreen[i][j] =
                    (int) (round(copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                 copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) /
                           4.0);
                avgBlue[i][j] =
                    (int) (round(copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                 copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) /
                           4.0);
            }
            // Bottom right
            else if (i == height - 1 && j == width - 1)
            {
                avgRed[i][j] = (int) (round(copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed +
                                            copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed) /
                                      4.0);
                avgGreen[i][j] =
                    (int) (round(copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen +
                                 copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen) /
                           4.0);
                avgBlue[i][j] =
                    (int) (round(copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue +
                                 copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue) /
                           4.0);
            }

            // Edge cases
            // First row
            else if (i == 0 && j != 0 && j != width - 1)
            {
                avgRed[i][j] = (int) (round(copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed +
                                            copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed +
                                            copy[i][j + 1].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                                      6.0);
                avgGreen[i][j] =
                    (int) (round(copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen +
                                 copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen +
                                 copy[i][j + 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                           6.0);
                avgBlue[i][j] =
                    (int) (round(copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue +
                                 copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue +
                                 copy[i][j + 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) /
                           6.0);
            }

            // Last row
            else if (i == height - 1 && j != 0 && j != width - 1)
            {
                avgRed[i][j] = (int) (round(copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed +
                                            copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed +
                                            copy[i][j + 1].rgbtRed + copy[i - 1][j + 1].rgbtRed) /
                                      6.0);
                avgGreen[i][j] =
                    (int) (round(copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen +
                                 copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen +
                                 copy[i][j + 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) /
                           6.0);
                avgBlue[i][j] =
                    (int) (round(copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue +
                                 copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue +
                                 copy[i][j + 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) /
                           6.0);
            }

            // First column
            else if (i != 0 && i != height - 1 && j == 0)
            {
                avgRed[i][j] = (int) (round(copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                            copy[i - 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed +
                                            copy[i + 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed) /
                                      6.0);
                avgGreen[i][j] =
                    (int) (round(copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                 copy[i - 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen +
                                 copy[i + 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) /
                           6.0);
                avgBlue[i][j] = (int) (round(copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                             copy[i - 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue +
                                             copy[i][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) /
                                       6.0);
            }

            // Last column
            else if (i != 0 && i != height - 1 && j == width - 1)
            {
                avgRed[i][j] = (int) (round(copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed +
                                            copy[i - 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed +
                                            copy[i + 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed) /
                                      6.0);
                avgGreen[i][j] =
                    (int) (round(copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen +
                                 copy[i - 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen +
                                 copy[i + 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen) /
                           6.0);
                avgBlue[i][j] = (int) (round(copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue +
                                             copy[i - 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue +
                                             copy[i][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue) /
                                       6.0);
            }

            // General cases
            else
            {
                avgRed[i][j] = (int) (round(copy[i][j].rgbtRed + copy[i + 1][j + 1].rgbtRed +
                                            copy[i - 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed +
                                            copy[i][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed +
                                            copy[i - 1][j + 1].rgbtRed + copy[i][j - 1].rgbtRed +
                                            copy[i - 1][j].rgbtRed) /
                                      9.0);
                avgGreen[i][j] =
                    (int) (round(copy[i][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen +
                                 copy[i - 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen +
                                 copy[i][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen +
                                 copy[i - 1][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen +
                                 copy[i - 1][j].rgbtGreen) /
                           9.0);
                avgBlue[i][j] = (int) (round(copy[i][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue +
                                             copy[i - 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                                             copy[i][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue +
                                             copy[i - 1][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue +
                                             copy[i - 1][j].rgbtBlue) /
                                       9.0);
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = avgRed[i][j];
            image[i][j].rgbtGreen = avgGreen[i][j];
            image[i][j].rgbtBlue = avgBlue[i][j];
        }
    }

    return;
}

// Function that returns the lesser of two integers
int less_than(int n1, int n2)
{
    if (n1 < n2)
    {
        return n1;
    }
    else
        return n2;
}
