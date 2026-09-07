#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int arreglo[30];
    int frecuencias[6] = {0};

    srand(time(NULL));
    printf("arreglo generado:\n");
    for (int i = 0; i < 30; i++)
    {
        arreglo[i] = (rand() % 5) + 1;
        printf("%d ", arreglo[i]);
        frecuencias[arreglo[i]]++;
    }

    printf("\n\nfrecuencias:\n");
    for (int i = 1; i <= 5; i++)
    {
        printf("numero %d: %d vez/veces\n", i, frecuencias[i]);
    }

    return 0;
}