#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo
{
    char dato;
    struct Nodo *izquierdo;
    struct Nodo *derecho;
} Nodo;

typedef Nodo *arbolBinario;

// funcion para liberar toda la memoria del arbol
void eliminarArbol(arbolBinario raiz)
{
    if (raiz == NULL)
    {
        return;
    }
    eliminarArbol(raiz->izquierdo);
    eliminarArbol(raiz->derecho);
    free(raiz);
}

// funcioon auxiliar
Nodo *crearNodo(char valor)
{
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    nuevo->dato = valor;
    nuevo->izquierdo = NULL;
    nuevo->derecho = NULL;
    return nuevo;
}

// funcion recursiva para reconstruir el arbol desde posorden
arbolBinario reconstruirPosorden(char *cadena, int *indice)
{
    if (*indice < 0)
    {
        return NULL;
    }

    char actual = cadena[*indice];
    (*indice)--;

    if (actual == '0')
    {
        return NULL;
    }

    Nodo *raiz = crearNodo(actual);

    raiz->derecho = reconstruirPosorden(cadena, indice);
    raiz->izquierdo = reconstruirPosorden(cadena, indice);

    return raiz;
}

// funcion para recorrer e imprimir en Inorden izquierda,raiz, derecha
void inorden(arbolBinario raiz)
{
    if (raiz != NULL)
    {
        inorden(raiz->izquierdo);
        printf("%c ", raiz->dato);
        inorden(raiz->derecho);
    }
}

int main()
{
    // cadena de prueba
    char cadena[] = "00B00CA";
    int indice = strlen(cadena) - 1;

    arbolBinario miArbol = reconstruirPosorden(cadena, &indice);

    // imprimir en inorden
    printf("recorrido inorden ");
    inorden(miArbol);
    printf("\n");

    eliminarArbol(miArbol);
    miArbol = NULL;

    return 0;
}