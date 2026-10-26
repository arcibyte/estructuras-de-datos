#include <stdlib.h>

typedef struct Nodo
{
    int valor;
    struct Nodo *izquierdo;
    struct Nodo *derecho;
} Nodo;

typedef Nodo *arbolBinario;

void eliminarArbol(arbolBinario raiz)
{
    if (raiz == NULL)
    {
        return;
    }

    // liberacion recursiva
    eliminarArbol(raiz->izquierdo);

    eliminarArbol(raiz->derecho);

    free(raiz);
}