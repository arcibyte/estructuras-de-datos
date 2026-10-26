// correcion enunciado E1-P
// Jhon Arciniegas -2243561

#include <stdio.h>
#include <stdlib.h>

struct Nodo
{
    int valor;
    struct Nodo *sig;
};

// TAD cola para la ventana deslizante
typedef struct
{
    struct Nodo *frente;
    struct Nodo *final;
    int tamano;
} Cola;

// TAD pila auxiliar
typedef struct
{
    struct Nodo *tope;
} Pila;

Pila crearPila()
{
    Pila p;
    p.tope = NULL;
    return p;
}

int isEmptyPila(Pila p)
{
    return p.tope == NULL;
}

void push(Pila *p, int valor)
{
    struct Nodo *nuevo = (struct Nodo *)malloc(sizeof(struct Nodo));
    nuevo->valor = valor;
    nuevo->sig = p->tope;
    p->tope = nuevo;
}

int pop(Pila *p)
{
    if (isEmptyPila(*p))
        return -1;
    struct Nodo *temp = p->tope;
    int val = temp->valor;

    p->tope = p->tope->sig;
    free(temp);
    return val;
}

Cola crearCola()
{
    Cola c;
    c.frente = NULL;
    c.final = NULL;
    c.tamano = 0;
    return c;
}

int isEmptyCola(Cola c)
{
    return c.tamano == 0;
}

void enqueue(Cola *c, int valor)
{
    struct Nodo *nuevo = (struct Nodo *)malloc(sizeof(struct Nodo));
    nuevo->valor = valor;
    nuevo->sig = NULL;

    if (isEmptyCola(*c))
    {
        c->frente = nuevo;
        c->final = nuevo;
    }
    else
    {
        c->final->sig = nuevo;
        c->final = nuevo;
    }
    c->tamano++;
}

int dequeue(Cola *c)
{
    if (isEmptyCola(*c))
        return -1;
    struct Nodo *temp = c->frente;
    int val = temp->valor;

    c->frente = c->frente->sig;
    if (c->frente == NULL)
    {
        c->final = NULL;
    }
    free(temp);
    c->tamano--;
    return val;
}

void imprimirVentanaInvertida(Cola *c)
{
    Pila p = crearPila();
    int iteraciones = c->tamano;

    // pasar de Cola a Pila
    for (int i = 0; i < iteraciones; i++)
    {
        push(&p, dequeue(c));
    }

    // imprimir LIFO y reencolar
    printf("ventana invertida ");
    while (!isEmptyPila(p))
    {
        int val = pop(&p);
        printf("%d ", val);
        enqueue(c, val);
    }
    printf("\n");

    // regresar a la cola a su orden original
    for (int i = 0; i < iteraciones; i++)
    {
        push(&p, dequeue(c));
    }
    while (!isEmptyPila(p))
    {
        enqueue(c, pop(&p));
    }
}

int main()
{
    int k, numero;

    if (scanf("%d", &k) != 1)
        return 1;

    Cola ventana = crearCola();

    while (1)
    {
        scanf("%d", &numero);
        if (numero == -1)
            break;

        printf("ingresa %d - ", numero);

        // deslizar ventana si está llena
        if (ventana.tamano == k)
        {
            dequeue(&ventana);
        }
        enqueue(&ventana, numero);

        imprimirVentanaInvertida(&ventana);
    }

    // liberar memoria final
    while (!isEmptyCola(ventana))
    {
        dequeue(&ventana);
    }

    return 0;
}