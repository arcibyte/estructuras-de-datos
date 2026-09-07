#include <stdio.h>

int main()
{
    int arreglo[20];

    printf("ingrese 20 numeros enteros:\n");
    for (int i = 0; i < 20; i++)
    {
        scanf("%d", &arreglo[i]);
    }

    printf("elementos que solo tienen una ocurrencia:\n");
    for (int i = 0; i < 20; i++)
    {
        int ocurrencias = 0;
        for (int j = 0; j < 20; j++)
        {
            if (arreglo[i] == arreglo[j])
            {
                ocurrencias++;
            }
        }
        if (ocurrencias == 1)
        {
            printf("%d ", arreglo[i]);
        }
    }
    printf("\n");

    return 0;
}