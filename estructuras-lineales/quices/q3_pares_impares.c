#include <stdio.h>
#include <stdlib.h>

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
        printf("error, no hay memoria disponible\n");
        exit(1);
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

// funcion para separar la lista original en dos listas, pares e impares
void separar_pares_impares(Node *head, Node **head_pares, Node **tail_pares, Node **head_impares, Node **tail_impares)
{
    Node *actual = head;

    while (actual != NULL)
    {
        if (actual->data % 2 == 0)
        {
            insertar_fifo(head_pares, tail_pares, actual->data);
        }
        else
        {
            insertar_fifo(head_impares, tail_impares, actual->data);
        }
        actual = actual->next;
    }
}

void imprimir_lista(Node *head)
{
    Node *temp = head;
    if (temp == NULL)
    {
        printf("(Vacia)");
    }
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void liberar_lista(Node *head)
{
    Node *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main()
{
    Node *head_original = NULL;
    Node *tail_original = NULL;

    Node *head_pares = NULL;
    Node *tail_pares = NULL;

    Node *head_impares = NULL;
    Node *tail_impares = NULL;

    int valor;

    printf("ingrese numeros enteros (el ingreso finaliza con el valor 0):\n");

    while (1)
    {
        if (scanf("%d", &valor) != 1)
        {
            printf("entrada no valida\n");
            break;
        }

        if (valor == 0)
        {
            break;
        }

        insertar_fifo(&head_original, &tail_original, valor);
    }

    separar_pares_impares(head_original, &head_pares, &tail_pares, &head_impares, &tail_impares);

    printf("lista original: ");
    imprimir_lista(head_original);

    printf("lista de pares: ");
    imprimir_lista(head_pares);

    printf("lista de impares: ");
    imprimir_lista(head_impares);

    liberar_lista(head_original);
    liberar_lista(head_pares);
    liberar_lista(head_impares);

    return 0;
}