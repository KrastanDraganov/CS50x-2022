#include <math.h>
#include <stdbool.h>

#include "helpers.h"

const int GRID_SIZE = 3;
const int COLOR_LIMIT = 255;

int gx_kernel[GRID_SIZE][GRID_SIZE] =
{
    {-1,  0,  1},
    {-2,  0,  2},
    {-1,  0,  1}
};

int gy_kernel[GRID_SIZE][GRID_SIZE] =
{
    {-1, -2, -1},
    { 0,  0,  0},
    { 1,  2,  1}
};

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            double average_color = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            BYTE new_color = round(average_color);
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = new_color;
        }
    }

    return;
}

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width / 2; ++j)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }

    return;
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy_image[height][width];
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            copy_image[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int counter = 0;

            double average_blue = 0.0;
            double average_green = 0.0;
            double average_red = 0.0;

            for (int new_i = i - 1; new_i <= i + 1; ++new_i)
            {
                for (int new_j = j - 1; new_j <= j + 1; ++new_j)
                {
                    bool in_boundary = (new_i >= 0 && new_i < height && new_j >= 0 && new_j < width);
                    if (in_boundary)
                    {
                        ++counter;

                        average_blue += 1.0 * copy_image[new_i][new_j].rgbtBlue;
                        average_green += 1.0 * copy_image[new_i][new_j].rgbtGreen;
                        average_red += 1.0 * copy_image[new_i][new_j].rgbtRed;
                    }
                }
            }

            average_blue /= (1.0 * counter);
            average_green /= (1.0 * counter);
            average_red /= (1.0 * counter);

            image[i][j].rgbtBlue = round(average_blue);
            image[i][j].rgbtGreen = round(average_green);
            image[i][j].rgbtRed = round(average_red);
        }
    }

    return;
}

void cap_color(int *color)
{
    if (*color > COLOR_LIMIT)
    {
        *color = COLOR_LIMIT;
    }
}

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy_image[height][width];
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            copy_image[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int gx_blue = 0;
            int gy_blue = 0;

            int gx_green = 0;
            int gy_green = 0;

            int gx_red = 0;
            int gy_red = 0;

            for (int new_i = i - 1; new_i <= i + 1; ++new_i)
            {
                for (int new_j = j - 1; new_j <= j + 1; ++new_j)
                {
                    bool in_boundary = (new_i >= 0 && new_i < height && new_j >= 0 && new_j < width);
                    if (in_boundary)
                    {
                        int current_gx = gx_kernel[new_i - i + 1][new_j - j + 1];
                        int current_gy = gy_kernel[new_i - i + 1][new_j - j + 1];

                        gx_blue += current_gx * copy_image[new_i][new_j].rgbtBlue;
                        gy_blue += current_gy * copy_image[new_i][new_j].rgbtBlue;

                        gx_green += current_gx * copy_image[new_i][new_j].rgbtGreen;
                        gy_green += current_gy * copy_image[new_i][new_j].rgbtGreen;

                        gx_red += current_gx * copy_image[new_i][new_j].rgbtRed;
                        gy_red += current_gy * copy_image[new_i][new_j].rgbtRed;
                    }
                }
            }

            int edge_blue = round(sqrt(gx_blue * gx_blue + gy_blue * gy_blue));
            int edge_green = round(sqrt(gx_green * gx_green + gy_green * gy_green));
            int edge_red = round(sqrt(gx_red * gx_red + gy_red * gy_red));

            cap_color(&edge_blue);
            cap_color(&edge_green);
            cap_color(&edge_red);

            image[i][j].rgbtBlue = edge_blue;
            image[i][j].rgbtGreen = edge_green;
            image[i][j].rgbtRed = edge_red;
        }
    }

    return;
}