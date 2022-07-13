#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //validación de entrada de argumentos
    if (argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }

    //apertura del archivo tipo file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("el archivo no existe\n");
    }

    int jpg = 0;
    int cont = 0;

    unsigned char buffer[512];
    FILE *imagen = NULL;
    char archivo[8];

    //condicion del buffer
    while (fread(buffer, 512, 1, file) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (jpg == 1)
            {
                fclose(imagen);
            }
            else
            {
                jpg = 1;
            }
            //imprimir en el arreglo archivo
            sprintf(archivo, "%03i.jpg", cont);
            imagen = fopen(archivo, "w");
            cont++;
        }
        //si se encontro un jpg escribir en la imagen
        if (jpg == 1)
        {
            fwrite(&buffer, 512, 1, imagen);
        }
    }
    fclose(file);
    fclose(imagen);

    return 0;
}