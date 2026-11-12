#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

void insertar_fifo(Node **head, Node **tail, int valor)
{
    Node *nuevo = (Node *)malloc(sizeof(Node));
    if (nuevo == NULL)
    {
        fprintf(stderr, "error, no se pudo asignar memoria\n");
        exit(EXIT_FAILURE);
    }
    nuevo->data = valor;
    nuevo->next = NULL;

    if (*head == NULL)
    {
        *head = nuevo;
        *tail = nuevo;
    }
    else
    {
        (*tail)->next = nuevo;
        *tail = nuevo;
    }
}

void imprimir_lista(const Node *head)
{
    if (head == NULL)
    {
        printf("la lista esta vacia (no existen elementos con ocurrencia unica)\n");
        return;
    }

    const Node *actual = head;
    while (actual != NULL)
    {
        printf("%d ", actual->data);
        actual = actual->next;
    }
    printf("\n");
}

void liberar_lista(Node **head)
{
    Node *actual = *head;
    Node *siguiente = NULL;

    while (actual != NULL)
    {
        siguiente = actual->next;
        free(actual);
        actual = siguiente;
    }

    *head = NULL;
}

int main()
{
    int arreglo[MAX_SIZE];
    int n = 0;

    printf("ingrese la cantidad de elementos (maximo %d): ", MAX_SIZE);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_SIZE)
    {
        printf("cantidad de elementos invalida\n");
        return 1;
    }

    printf("ingrese los %d numeros enteros (positivos o negativos):\n", n);
    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &arreglo[i]) != 1)
        {
            printf("error, en la lectura del elemento en la posicion %d.\n", i);
            return 1;
        }
    }

    Node *head = NULL;
    Node *tail = NULL;

    for (int i = 0; i < n; i++)
    {
        int ocurrencias = 0;
        for (int j = 0; j < n; j++)
        {
            if (arreglo[i] == arreglo[j])
            {
                ocurrencias++;
            }
        }

        if (ocurrencias == 1)
        {
            insertar_fifo(&head, &tail, arreglo[i]);
        }
    }

    printf("\nnumeros con una sola ocurrencia (orden FIFO):\n");
    imprimir_lista(head);

    liberar_lista(&head);

    return 0;
}