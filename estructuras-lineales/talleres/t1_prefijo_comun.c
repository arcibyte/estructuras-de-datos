#include <stdio.h>
#include <string.h>

#define MAX_N 10
#define MAX_LEN 20

int main()
{
    int n;

    if (scanf("%d", &n) != 1 || n < 2 || n > MAX_N)
    {
        return 1;
    }

    char cadenas[MAX_N][MAX_LEN + 1];

    for (int i = 0; i < n; i++)
    {
        if (scanf("%20s", cadenas[i]) != 1)
        {
            return 1;
        }
    }

    int longitud_prefijo = 0;

    while (cadenas[0][longitud_prefijo] != '\0')
    {
        char caracter_actual = cadenas[0][longitud_prefijo];
        int coincide = 1;

        for (int i = 1; i < n; i++)
        {
            // si la cadena terminó o el carácter difiere, el prefijo termina
            if (cadenas[i][longitud_prefijo] != caracter_actual)
            {
                coincide = 0;
                break;
            }
        }

        if (!coincide)
        {
            break;
        }

        longitud_prefijo++;
    }

    if (longitud_prefijo == 0)
    {
        printf("-\n");
    }
    else
    {
        cadenas[0][longitud_prefijo] = '\0'; // rompe la primera cadena en el límite del prefijo
        printf("%s\n", cadenas[0]);
    }

    return 0;
}