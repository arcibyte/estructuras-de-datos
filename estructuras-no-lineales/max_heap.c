#include <stdio.h>
#include <stdlib.h>

void intercambiar(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// matniene la propiedad de max-heap en el subarbol con raíz en i
void maxHeapify(int arreglo[], int n, int i)
{
    int mayor = i;
    int izquierdo = 2 * i + 1;
    int derecho = 2 * i + 2;

    if (izquierdo < n && arreglo[izquierdo] > arreglo[mayor])
    {
        mayor = izquierdo;
    }

    if (derecho < n && arreglo[derecho] > arreglo[mayor])
    {
        mayor = derecho;
    }

    if (mayor != i)
    {
        intercambiar(&arreglo[i], &arreglo[mayor]);
        maxHeapify(arreglo, n, mayor);
    }
}

// construye un max-heap a partir de un arreglo desordenado
void construirMaxHeap(int arreglo[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        maxHeapify(arreglo, n, i);
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

    printf("ingrese los numeros separados por espacio: ");

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

    printf("\narreglo original ingresado ");
    imprimirArreglo(arreglo, n);

    construirMaxHeap(arreglo, n);

    printf("representacion en max-heap ");
    imprimirArreglo(arreglo, n);

    free(arreglo);
    arreglo = NULL;

    return 0;
}