#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo
{
    int valor;
    struct Nodo *izquierdo;
    struct Nodo *derecho;
} Nodo;

typedef Nodo *BST;

// funcion auxiliar para el nodo nuevo
Nodo *crearNodo(int valor)
{
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    nuevo->valor = valor;
    nuevo->izquierdo = NULL;
    nuevo->derecho = NULL;
    return nuevo;
}

BST insertar(BST raiz, int valor)
{
    if (raiz == NULL)
    {
        return crearNodo(valor);
    }

    if (valor < raiz->valor)
    {
        raiz->izquierdo = insertar(raiz->izquierdo, valor);
    }
    else
    {
        raiz->derecho = insertar(raiz->derecho, valor);
    }

    return raiz;
}

// funcion para imprimir en inorden izquierda, raiz, derecha
void inorden(BST raiz)
{
    if (raiz != NULL)
    {
        inorden(raiz->izquierdo);
        printf("%d ", raiz->valor);
        inorden(raiz->derecho);
    }
}

void eliminarArbol(BST raiz)
{
    if (raiz == NULL)
        return;
    eliminarArbol(raiz->izquierdo);
    eliminarArbol(raiz->derecho);
    free(raiz);
}

int main()
{
    BST miArbol = NULL;
    int numero;
    char separador;

    printf("ingrese los numeros separados por espacio ");

    while (scanf("%d", &numero) == 1)
    {
        miArbol = insertar(miArbol, numero);

        separador = getchar();
        if (separador == '\n' || separador == EOF)
        {
            break;
        }
    }

    printf("salida ordenada (inorden) ");
    inorden(miArbol);
    printf("\n");

    eliminarArbol(miArbol);
    miArbol = NULL;

    return 0;
}