#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BASE 10000
#define DIGITOS_BLOQUE 4

typedef struct Nodo
{
    short bloque;
    struct Nodo *siguiente;
} Nodo;

Nodo *crearNodo(short valor)
{
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevo == NULL)
    {
        fprintf(stderr, "Error crítico: Memoria insuficiente.\n");
        exit(EXIT_FAILURE);
    }
    nuevo->bloque = valor;
    nuevo->siguiente = NULL;
    return nuevo;
}

Nodo *leerNumeroEmpaquetado(void)
{
    Nodo *pilaDigitos = NULL;
    int c;

    while ((c = getchar()) != EOF && isspace(c))
        ;

    // apila digitos en orden inverso para agrupar de 4 en 4 desde las unidades sin usar arreglos
    while (c != EOF && isdigit(c))
    {
        short d = (short)(c - '0');
        if (!(pilaDigitos == NULL && d == 0))
        {
            Nodo *temp = crearNodo(d);
            temp->siguiente = pilaDigitos;
            pilaDigitos = temp;
        }
        c = getchar();
    }

    if (pilaDigitos == NULL)
    {
        return crearNodo(0);
    }

    Nodo *cabezaBloques = NULL;
    Nodo *colaBloques = NULL;

    while (pilaDigitos != NULL)
    {
        short valorBloque = 0;
        short multiplicador = 1;

        for (int i = 0; i < DIGITOS_BLOQUE && pilaDigitos != NULL; i++)
        {
            valorBloque += pilaDigitos->bloque * multiplicador;
            multiplicador *= 10;

            Nodo *basura = pilaDigitos;
            pilaDigitos = pilaDigitos->siguiente;
            free(basura);
        }

        Nodo *nuevoBloque = crearNodo(valorBloque);
        if (cabezaBloques == NULL)
        {
            cabezaBloques = nuevoBloque;
            colaBloques = nuevoBloque;
        }
        else
        {
            colaBloques->siguiente = nuevoBloque;
            colaBloques = nuevoBloque;
        }
    }

    return cabezaBloques;
}

Nodo *sumarNumeros(Nodo *num1, Nodo *num2)
{
    Nodo *resCabeza = NULL;
    Nodo *resCola = NULL;
    short acarreo = 0;

    while (num1 != NULL || num2 != NULL || acarreo > 0)
    {
        short b1 = (num1 != NULL) ? num1->bloque : 0;
        short b2 = (num2 != NULL) ? num2->bloque : 0;

        short suma = b1 + b2 + acarreo;
        short bloqueResultante = suma % BASE;
        acarreo = suma / BASE;

        Nodo *nuevo = crearNodo(bloqueResultante);
        if (resCabeza == NULL)
        {
            resCabeza = nuevo;
            resCola = nuevo;
        }
        else
        {
            resCola->siguiente = nuevo;
            resCola = nuevo;
        }

        if (num1 != NULL)
            num1 = num1->siguiente;
        if (num2 != NULL)
            num2 = num2->siguiente;
    }

    return resCabeza;
}

// inversion inplace O(1) para imprimir sin arreglos ni desbordamiento de pila por recursion
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
    if (*cabeza == NULL)
        return;

    *cabeza = invertirLista(*cabeza);

    Nodo *actual = *cabeza;
    printf("%hd", actual->bloque);
    actual = actual->siguiente;

    // rellena con ceros a 4 dígitos para preservar ceros intermedios entre bloques
    while (actual != NULL)
    {
        printf("%04hd", actual->bloque);
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
    Nodo *numero1 = leerNumeroEmpaquetado();

    printf("Ingrese el segundo entero positivo:\n");
    Nodo *numero2 = leerNumeroEmpaquetado();

    Nodo *resultado = sumarNumeros(numero1, numero2);

    printf("Resultado de la suma:\n");
    imprimirNumero(&resultado);

    liberarLista(numero1);
    liberarLista(numero2);
    liberarLista(resultado);

    return 0;
}