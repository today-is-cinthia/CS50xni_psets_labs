#include <cs50.h>
#include <stdio.h>

int main(void)
{
     int altura = 0;
    // validacion de 1 a 8
    do
    {
        altura = get_int("Ingresa el tamaño porfis: \n");
    }
    while (altura < 1 || altura > 8);

    //impresion de la piramide
    for (int i = 0; i < altura; i++)
    {
        //impresion de espacios
        for (int espacios = i + 1; espacios < altura; espacios++)
        {
            printf(" ");
        }
        //impresion de hash
        for (int hash = altura + i + 1; hash > altura; hash--)
        {
            printf("#");
        }
        //salto de linea
        printf("\n");
    }
    return 0;
}