#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Defining useful variables
    double avg;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of blue, green, red
            avg = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            avg = round(avg);
            // Update the pixel values

            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    double Red, Green, Blue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Assigns the new RGB values to floats
            Red = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                  .189 * image[i][j].rgbtBlue;
            Green = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                    .168 * image[i][j].rgbtBlue;
            Blue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                   .131 * image[i][j].rgbtBlue;

            // Treats the case were one or more values are >255
            if (Red > 255)
            {
                Red = 255;
            }
            if (Green > 255)
            {
                Green = 255;
            }
            if (Blue > 255)
            {
                Blue = 255;
            }

            // Rounds all the values
            Red = round(Red);
            Green = round(Green);
            Blue = round(Blue);

            // Uses the function round to round all the RGB values to the nearest interger
            image[i][j].rgbtRed = Red;
            image[i][j].rgbtGreen = Green;
            image[i][j].rgbtBlue = Blue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Creates an RGBTRIPLE variable
    RGBTRIPLE cpy;

    // Bidimensional loop
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Switches the pixels
            cpy = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = cpy;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Defining useful variables
    int avg;
    double red, green, blue;
    //---------------------------

    // Copying the image
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // ---------------------------------------------------------------

    // Blurs the first line
    for (int i = 0; i < width; i++)
    {
        // Adds the values that are included in all the additions
        red = copy[0][i].rgbtRed + copy[1][i].rgbtRed;
        green = copy[0][i].rgbtGreen + copy[1][i].rgbtGreen;
        blue = copy[0][i].rgbtBlue + copy[1][i].rgbtBlue;

        if (i != 0)
        {
            // Adds to all values except for the first pixel
            red += copy[0][i - 1].rgbtRed + copy[1][i - 1].rgbtRed;
            green += copy[0][i - 1].rgbtGreen + copy[1][i - 1].rgbtGreen;
            blue += copy[0][i - 1].rgbtBlue + copy[1][i - 1].rgbtBlue;
        }
        if (i != width - 1)
        {
            // Adds to all values except for the last pixel
            red += copy[0][i + 1].rgbtRed + copy[1][i + 1].rgbtRed;
            green += copy[0][i + 1].rgbtGreen + copy[1][i + 1].rgbtGreen;
            blue += copy[0][i + 1].rgbtBlue + copy[1][i + 1].rgbtBlue;
        }

        if (i == 0 || i == width - 1)
        {
            // Divides the corner pixels
            red /= 4.0;
            green /= 4.0;
            blue /= 4.0;
        }
        else
        {
            // Divides the other pixels
            red /= 6.0;
            green /= 6.0;
            blue /= 6.0;
        }

        // Rounds everything and send the values
        red = round(red);
        image[0][i].rgbtRed = red;

        green = round(green);
        image[0][i].rgbtGreen = green;

        blue = round(blue);
        image[0][i].rgbtBlue = blue;
    }
    // --------------------------------------------------------------------------

    // Blurs all the middle lines, starting with a bidimensional loop
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Adds the values common for all the pixels
            red = copy[i + 1][j].rgbtRed + copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed;
            green = copy[i + 1][j].rgbtGreen + copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen;
            blue = copy[i + 1][j].rgbtBlue + copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue;

            if (j != 0)
            {
                // Adds to all values except for the first pixel
                red += copy[i + 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed +
                       copy[i - 1][j - 1].rgbtRed;
                green += copy[i + 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen +
                         copy[i - 1][j - 1].rgbtGreen;
                blue += copy[i + 1][j - 1].rgbtBlue + copy[i][j - 1].rgbtBlue +
                        copy[i - 1][j - 1].rgbtBlue;
            }
            if (j != width - 1)
            {
                // Adds to all values except for the last pixel
                red += copy[i + 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed +
                       copy[i - 1][j + 1].rgbtRed;
                green += copy[i + 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen +
                         copy[i - 1][j + 1].rgbtGreen;
                blue += copy[i + 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue +
                        copy[i - 1][j + 1].rgbtBlue;
            }

            if (j == 0 || j == width - 1)
            {
                // Divides last and first pixel
                red /= 6.0;
                green /= 6.0;
                blue /= 6.0;
            }
            else
            {
                // Divides the other pixels
                red /= 9.0;
                green /= 9.0;
                blue /= 9.0;
            }

            // Rounds everything and sends the values
            red = round(red);
            image[i][j].rgbtRed = red;

            green = round(green);
            image[i][j].rgbtGreen = green;

            blue = round(blue);
            image[i][j].rgbtBlue = blue;
        }
    }
    // --------------------------------------------------------------------------------------------------------------------

    // Blurs the last line
    for (int i = 0; i < width; i++)
    {
        // Adds the values common to all pixels
        red = copy[height - 1][i].rgbtRed + copy[height - 2][i].rgbtRed;
        green = copy[height - 1][i].rgbtGreen + copy[height - 2][i].rgbtGreen;
        blue = copy[height - 1][i].rgbtBlue + copy[height - 2][i].rgbtBlue;

        if (i != 0)
        {
            // Adds to all but the first
            red += copy[height - 1][i - 1].rgbtRed + copy[height - 2][i - 1].rgbtRed;
            green += copy[height - 1][i - 1].rgbtGreen + copy[height - 2][i - 1].rgbtGreen;
            blue += copy[height - 1][i - 1].rgbtBlue + copy[height - 2][i - 1].rgbtBlue;
        }
        if (i != width - 1)
        {
            // Adds to all but the last
            red += copy[height - 1][i + 1].rgbtRed + copy[height - 2][i + 1].rgbtRed;
            green += copy[height - 1][i + 1].rgbtGreen + copy[height - 2][i + 1].rgbtGreen;
            blue += copy[height - 1][i + 1].rgbtBlue + copy[height - 2][i + 1].rgbtBlue;
        }
        if (i == 0 || i == width - 1)
        {
            // Divides the last and first pixels
            red /= 4.0;
            green /= 4.0;
            blue /= 4.0;
        }
        else
        {
            // Divides all the other pixels
            red /= 6.0;
            green /= 6.0;
            blue /= 6.0;
        }

        // Rounds everything and sends it
        red = round(red);
        image[height - 1][i].rgbtRed = red;

        green = round(green);
        image[height - 1][i].rgbtGreen = green;

        blue = round(blue);
        image[height - 1][i].rgbtBlue = blue;
    }
    // --------------------------------------------------------------------------
}
