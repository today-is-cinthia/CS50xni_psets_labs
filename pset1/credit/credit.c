#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long n = get_long("Introducí tu numero de tarjeta porfis: ");

    int i = 0;
    long cc = n;

    //cuento de la longitud
    while (cc > 0)
    {
        cc = cc / 10;
        i++;
    }
    //longitud de la tarjeta
    if (i != 13 && i != 15 && i != 16)
    {
        printf("INVALID\n");
        return 0;
    }
    int sum1 = 0, sum2 = 0, mod1, mod2, d1, d2, total = 0;
    long x = n;

    do
    {
        //quitar el ultimo digito y añadirlo a sum1
        mod1 = x % 10;
        x = x / 10;
        sum1 = sum1 + mod1;

        // quitar el penultimo digito
        mod2 = x % 10;
        x = x / 10;

        //duplicar el penultimo digito añadirlo a sum2
        mod2 = mod2 * 2;
        d1 = mod2 % 10;
        d2 = mod2 / 10;
        sum2 = sum2 + d1 + d2;

    }
    while (x > 0);

    total = sum1 + sum2;

    //chequear si pasa el algoritmo Luhn
    if (total % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }
    long start = n;
    //identificar los digitos de inicio
    do
    {
        start =  start / 10;
    }
    while (start > 100);

    //identificar mastercard
    if ((start / 10 == 5) && (0 < start % 10 && start % 10 < 6))
    {
        printf("MASTERCARD\n");
    }
    else if ((start / 10 == 3) && (start % 10 == 4 || start % 10 == 7))
    {
        printf("AMEX\n");
    }
    else if (start / 10 == 4)
    {
        printf("VISA\n");
    }
    // si no es ninguna
    else
    {
        printf("INVALID\n");
    }
    return 0;
}