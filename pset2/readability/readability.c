#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    //conteo letras
    int count_letter = 0;
    //conteo palabras
    int count_word = 1;
    //conteo oraciones
    int count_sentence = 0;

    string text = get_string("Text: ");

    int text_length = strlen(text);
    for (int i = 0; i < text_length; i++)
    {
        if (isalpha(text[i]))
        {
            count_letter++;
        }
    }
    //printf("%i\n", count_letter)

    for (int i = 0; i < text_length; i++)
    {
        if (isspace(text[i]))
        {
            count_word++;
        }
    }
//  printf("%i\n", count_word);
    for (int i = 0; i < text_length; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            count_sentence++;
        }
    }

    //calculo
    float calculation = (0.0588 * count_letter / count_word * 100) - (0.296 * count_sentence / count_word * 100) - 15.8;

    //redondeo
    int index = round(calculation);

    //niveles de lectura
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}