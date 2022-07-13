#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //itera sobre las dimensiones de la imagen
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //promedio del valor del pixel
            int rgbt = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            //establece pixeles
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = rgbt;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int o_red, o_green, o_blue, sepia_red, sepia_green, sepia_blue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            o_red = image[i][j].rgbtRed;
            o_green = image[i][j].rgbtGreen;
            o_blue = image[i][j].rgbtBlue;

            //formula para el sepia
            //si los colores son mayores a 255 en valor cambiarlo, y si no se deja en su valor
            sepia_red = round(0.393 * o_red + 0.769 * o_green + 0.189 * o_blue);
            if (sepia_red > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepia_red;
            }

            //formula para el sepia
            sepia_green = round(0.349 * o_red + 0.686 * o_green + 0.168 * o_blue);
            if (sepia_green > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepia_green;
            }
            //sepia formula
            sepia_blue = round(0.272 * o_red + 0.534 * o_green + 0.131 * o_blue);
            if (sepia_blue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepia_blue;
            }
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
            // Refleja los pixeles
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //crea una imagen temporaria
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red_total, blue_total, green_total;
            red_total = blue_total = green_total = 0;

            float contador = 0.00;

            //recorre los pixeles vecinos
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int currentx = i + x;
                    int currenty = j + y;

                    //verifica si son válidos
                    if (currentx < 0 || currentx > (height - 1) || currenty < 0 || currenty > (width - 1))
                    {
                        continue;
                    }

                    //almacenar el valor de la imagen
                    red_total += image[currentx][currenty].rgbtRed;
                    green_total += image[currentx][currenty].rgbtGreen;
                    blue_total += image[currentx][currenty].rgbtBlue;

                    contador++;
                }

                //promedio de los pixeles vecinos
                temp[i][j].rgbtRed = round(red_total / contador);
                temp[i][j].rgbtGreen = round(green_total / contador);
                temp[i][j].rgbtBlue = round(blue_total / contador);
            }
        }
    }

    //copia la imagen con blur en la original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}
