#include <stdio.h>
#include <stdlib.h>

void intercambiar(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(int arreglo[], int n, int i)
{
    int menor = i;
    int izquierdo = 2 * i + 1;
    int derecho = 2 * i + 2;

    // verifica si el hijo izquierdo es menor que la raiz
    if (izquierdo < n && arreglo[izquierdo] < arreglo[menor])
    {
        menor = izquierdo;
    }

    // verifica si el hijo derecho es menor que el menor actual
    if (derecho < n && arreglo[derecho] < arreglo[menor])
    {
        menor = derecho;
    }

    if (menor != i)
    {
        intercambiar(&arreglo[i], &arreglo[menor]);
        minHeapify(arreglo, n, menor);
    }
}

// hace un min-heap a partir de un arreglo desordenado
void construirMinHeap(int arreglo[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        minHeapify(arreglo, n, i);
    }
}

void imprimirArreglo(int arreglo[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", arreglo[i]);
    }
    printf("\n");
}

int main()
{
    int capacidad = 100;
    int *arreglo = (int *)malloc(capacidad * sizeof(int));
    int n = 0;
    int numero;
    char separador;

    printf("ingrese los numeros separados por espacio ");

    while (scanf("%d", &numero) == 1)
    {
        if (n >= capacidad)
        {
            capacidad *= 2;
            arreglo = (int *)realloc(arreglo, capacidad * sizeof(int));
        }

        arreglo[n++] = numero;

        separador = getchar();
        if (separador == '\n' || separador == EOF)
        {
            break;
        }
    }

    printf("\narreglo original ingresado: ");
    imprimirArreglo(arreglo, n);

    construirMinHeap(arreglo, n);

    printf("representacion en min-heap ");
    imprimirArreglo(arreglo, n);

    free(arreglo);
    arreglo = NULL;

    return 0;
}