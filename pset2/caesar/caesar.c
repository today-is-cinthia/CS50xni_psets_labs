#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    int i, a;
//validacion argumentos
    if (argc != 2)
    {
        printf("usage: ./caesar key");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar  key\n");
            return 1;
        }
    }

//conversion a entero
    int key = atoi(argv[1]);
    if (key <= 0)
    {
        printf("ingrese un numero positivo");
        return 1;
    }
    string text = get_string("plaintext: ");
    printf("ciphertext: ");
    char n;

    //ciclo principal
    for (i = 0; i < strlen(text); i++)
    {
        // si es parte del alfabeto
        if (isalpha(text[i]))
        {
            //mayuscula
            if (isupper(text[i]))
            {
                printf("%c", n = (text[i] - 'A' + key) % 26 + 'A');
            }
            else
            {
                // minuscula
                if (islower(text[i]))
                {
                    printf("%c", n = (text[i] - 'a' + key) % 26 + 'a');
                }
            }
        }
        else
        {
            // si no es parte
            printf("%c", text[i]);
        }

    } // \n de salida
    printf("\n");
    return 0;
}