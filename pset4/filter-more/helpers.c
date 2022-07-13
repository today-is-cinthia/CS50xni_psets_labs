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

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            //guarda la imagen original temporariamente
            int temPred = image[i][j].rgbtRed;
            int temPgreen = image[i][j].rgbtGreen;
            int temPblue = image[i][j].rgbtBlue;

            //guardar la imagen de la izquierda en la
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            //guardar la variable temporal en la derecha de la imagen
            image[i][width - j - 1].rgbtRed = temPred;
            image[i][width - j - 1].rgbtGreen = temPgreen;
            image[i][width - j - 1].rgbtBlue = temPblue;
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //arreglo temporal para la imagen
    RGBTRIPLE temp[height][width];

    //incializar los arreglos de Sobel
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};


    //iterar sobre columnas  y filas
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gxBlue = 0;
            int gyBlue = 0;
            int gxGreen = 0;
            int gyGreen = 0;
            int gxRed = 0;
            int gyRed = 0;

            //para cada pixel iterar vertical y horizontalmente
            for (int r = -1; r < 2; r++)
            {
                for (int c = -1; c < 2; c++)
                {
                    //si el pixel esta fuera de las filas
                    if (i + r < 0 || i + r > height - 1)
                    {
                        continue;
                    }
                    //si esta fuera de las columnas
                    if (j + c < 0 || j + c > width - 1)
                    {
                        continue;
                    }

                    //si no es así se le añade a las sumas
                    gxBlue += image[i + r][j + c].rgbtBlue * gx[r + 1][c + 1];
                    gyBlue += image[i + r][j + c].rgbtBlue * gy[r + 1][c + 1];
                    gxGreen += image[i + r][j + c].rgbtGreen * gx[r + 1][c + 1];
                    gyGreen += image[i + r][j + c].rgbtGreen * gy[r + 1][c + 1];
                    gxRed += image[i + r][j + c].rgbtRed * gx[r + 1][c + 1];
                    gyRed += image[i + r][j + c].rgbtRed * gy[r + 1][c + 1];
                }
            }

            //calcular el agoritmo sobel
            int blue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));
            int green = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int red = round(sqrt(gxRed * gxRed + gyRed * gyRed));

            //asignar los valores a los pixeles
            temp[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
            temp[i][j].rgbtGreen = (green > 255) ? 255 : green;
            temp[i][j].rgbtRed = (red > 255) ? 255 : red;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }

    return;
}
