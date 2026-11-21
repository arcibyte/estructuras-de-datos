#include <stdio.h>
#include <stdlib.h>

void intercambiar(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void flotar(int arreglo[], int i)
{
    while (i > 0)
    {
        int padre = (i - 1) / 2;
        if (arreglo[i] > arreglo[padre])
        {
            intercambiar(&arreglo[i], &arreglo[padre]);
            i = padre;
        }
        else
        {
            break;
        }
    }
}

void insertarMaxHeap(int arreglo[], int *n, int valor)
{
    arreglo[*n] = valor;
    flotar(arreglo, *n);
    (*n)++;
}

void imprimirArreglo(const int arreglo[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        if (i > 0)
        {
            printf(" ");
        }
        printf("%d", arreglo[i]);
    }
    printf("\n");
}

int main(void)
{
    int capacidad = 100;
    int *arreglo = (int *)malloc((size_t)capacidad * sizeof(int));
    if (arreglo == NULL)
    {
        return 1;
    }

    int n = 0;
    int numero;

    while (scanf("%d", &numero) == 1)
    {
        if (n >= capacidad)
        {
            capacidad *= 2;
            int *temp = (int *)realloc(arreglo, (size_t)capacidad * sizeof(int));
            if (temp == NULL)
            {
                free(arreglo);
                return 1;
            }
            arreglo = temp;
        }
        insertarMaxHeap(arreglo, &n, numero);
    }

    imprimirArreglo(arreglo, n);

    free(arreglo);
    arreglo = NULL;

    return 0;
}
