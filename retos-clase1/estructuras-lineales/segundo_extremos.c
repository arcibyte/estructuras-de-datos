#include <stdio.h>

int main()
{
    float numeros[10];

    printf("Ingrese 10 numeros:\n");
    for (int i = 0; i < 10; i++)
    {
        scanf("%f", &numeros[i]);
    }

    // intento para ordenar el arreglo de menor a mayor
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (numeros[j] > numeros[j + 1])
            {
                float aux = numeros[j];
                numeros[j] = numeros[j + 1];
                numeros[j + 1] = aux;
            }
        }
    }

    // TODO: me falta imprimir el segundo menor y el segundo mayor
    // creo que el segundo menor esta en el indice 1 y el segundo mayor en el 8

    return 0;
}