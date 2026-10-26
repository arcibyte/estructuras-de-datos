#include <stdio.h>
#include <string.h>

int main()
{
    int n;
    printf("ingrese un numero n (2 <= n <= 10): ");
    if (scanf("%d", &n) != 1 || n < 2 || n > 10)
    {
        printf("numero invalido\n");
        return 1;
    }

    char cadenas[10][100];
    printf("ingrese las %d cadenas\n", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", cadenas[i]);
    }

    char prefijo[100];
    strcpy(prefijo, cadenas[0]);

    for (int i = 1; i < n; i++)
    {
        int j = 0;
        while (prefijo[j] != '\0' && cadenas[i][j] != '\0' && prefijo[j] == cadenas[i][j])
        {
            j++;
        }
        prefijo[j] = '\0'; // se detiene hasta encoontrar una coincidencia
    }

    if (strlen(prefijo) > 0)
    {
        printf("output: %s\n", prefijo);
    }
    else
    {
        printf("output: -\n");
    }

    return 0;
}