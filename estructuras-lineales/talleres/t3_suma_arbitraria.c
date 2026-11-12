#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Nodo
{
    short digito;
    struct Nodo *siguiente;
} Nodo;

Nodo *crearNodo(short digito)
{
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevo == NULL)
    {
        fprintf(stderr, "Error crítico: Memoria insuficiente.\n");
        exit(EXIT_FAILURE);
    }
    nuevo->digito = digito;
    nuevo->siguiente = NULL;
    return nuevo;
}

// inserta al inicio (head), dejando las unidades en la cabeza de la lista
Nodo *leerNumero(void)
{
    Nodo *cabeza = NULL;
    int c;

    while ((c = getchar()) != EOF && isspace(c))
        ;

    while (c != EOF && isdigit(c))
    {
        short valor = (short)(c - '0');

        if (!(cabeza == NULL && valor == 0))
        {
            Nodo *nuevo = crearNodo(valor);
            nuevo->siguiente = cabeza;
            cabeza = nuevo;
        }
        c = getchar();
    }

    if (cabeza == NULL)
    {
        cabeza = crearNodo(0);
    }

    return cabeza;
}

Nodo *sumarNumeros(Nodo *num1, Nodo *num2)
{
    Nodo *resultadoCabeza = NULL;
    Nodo *resultadoCola = NULL;
    short acarreo = 0;

    while (num1 != NULL || num2 != NULL || acarreo > 0)
    {
        short d1 = (num1 != NULL) ? num1->digito : 0;
        short d2 = (num2 != NULL) ? num2->digito : 0;

        short suma = d1 + d2 + acarreo;
        short digitoResultante = suma % 10;
        acarreo = suma / 10;

        // insertar al final para mantener las unidades en la cabeza
        Nodo *nuevo = crearNodo(digitoResultante);
        if (resultadoCabeza == NULL)
        {
            resultadoCabeza = nuevo;
            resultadoCola = nuevo;
        }
        else
        {
            resultadoCola->siguiente = nuevo;
            resultadoCola = nuevo;
        }

        if (num1 != NULL)
            num1 = num1->siguiente;
        if (num2 != NULL)
            num2 = num2->siguiente;
    }

    return resultadoCabeza;
}

Nodo *invertirLista(Nodo *cabeza)
{
    Nodo *anterior = NULL;
    Nodo *actual = cabeza;
    Nodo *siguiente = NULL;

    while (actual != NULL)
    {
        siguiente = actual->siguiente;
        actual->siguiente = anterior;
        anterior = actual;
        actual = siguiente;
    }
    return anterior;
}

void imprimirNumero(Nodo **cabeza)
{
    *cabeza = invertirLista(*cabeza);

    Nodo *actual = *cabeza;
    while (actual != NULL)
    {
        printf("%hd", actual->digito);
        actual = actual->siguiente;
    }
    printf("\n");

    *cabeza = invertirLista(*cabeza);
}

void liberarLista(Nodo *cabeza)
{
    Nodo *temp;
    while (cabeza != NULL)
    {
        temp = cabeza;
        cabeza = cabeza->siguiente;
        free(temp);
    }
}

int main(void)
{
    printf("Ingrese el primer entero positivo:\n");
    Nodo *numero1 = leerNumero();

    printf("Ingrese el segundo entero positivo:\n");
    Nodo *numero2 = leerNumero();

    Nodo *resultado = sumarNumeros(numero1, numero2);

    printf("Resultado de la suma:\n");
    imprimirNumero(&resultado);

    liberarLista(numero1);
    liberarLista(numero2);
    liberarLista(resultado);

    return 0;
}