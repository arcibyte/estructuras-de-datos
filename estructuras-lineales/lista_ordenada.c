#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo
{
    int dato;
    struct Nodo *siguiente;
} Nodo;

// inserta un nuevo nodo manteniendo el orden de menor a mayor
void insertar_ordenado(Nodo **cabeza, int valor)
{
    Nodo *nuevo_nodo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevo_nodo == NULL)
    {
        exit(1);
    }
    nuevo_nodo->dato = valor;
    nuevo_nodo->siguiente = NULL;

    // caso 1
    if (*cabeza == NULL || (*cabeza)->dato >= valor)
    {
        nuevo_nodo->siguiente = *cabeza;
        *cabeza = nuevo_nodo;
    }
    else
    {
        // caso 2
        Nodo *actual = *cabeza;
        while (actual->siguiente != NULL && actual->siguiente->dato < valor)
        {
            actual = actual->siguiente;
        }
        nuevo_nodo->siguiente = actual->siguiente;
        actual->siguiente = nuevo_nodo;
    }
}

void imprimir_lista(Nodo *cabeza)
{
    Nodo *actual = cabeza;
    while (actual != NULL)
    {
        printf("%d ", actual->dato);
        actual = actual->siguiente;
    }
    printf("\n");
}

// liberar nodo
void liberar_lista(Nodo *cabeza)
{
    Nodo *temporal;
    while (cabeza != NULL)
    {
        temporal = cabeza;
        cabeza = cabeza->siguiente;
        free(temporal);
    }
}

int main()
{
    Nodo *lista = NULL;
    int numero;

    // bucle de lectura hasta encontrar la condicion de detenerse
    while (1)
    {
        scanf("%d", &numero);
        if (numero == 0)
        {
            break;
        }
        insertar_ordenado(&lista, numero);
    }

    imprimir_lista(lista);
    liberar_lista(lista);

    return 0;
}