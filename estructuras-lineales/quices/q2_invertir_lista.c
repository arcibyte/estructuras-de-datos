#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    float data;
    struct Node *next;
} Node;

void insertar_fifo(Node **head, Node **tail, float valor)
{
    Node *nuevo = (Node *)malloc(sizeof(Node));
    if (nuevo == NULL)
    {
        printf("error: no hay memoria disponible\n");
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

// invertir la lista enlazada (punteros)
Node *invertir_lista(Node *head)
{
    Node *prev = NULL;
    Node *current = head;
    Node *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}

void imprimir_lista(Node *head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        printf("%.2f ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// liberar memoria
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
    Node *head = NULL;
    Node *tail = NULL;
    float valor;
    int contador_menos_uno = 0;

    printf("ingrese numeros en punto flotante (el ingreso finaliza con la 3ra aparicion de -1):\n");

    while (1)
    {
        if (scanf("%f", &valor) != 1)
        {
            printf("entrada no valida\n");
            break;
        }

        // verificar si es el valor centinela -1
        if (valor == -1.0f)
        {
            contador_menos_uno++;
            if (contador_menos_uno == 3)
            {
                break;
            }

            continue;
        }

        insertar_fifo(&head, &tail, valor);
    }

    head = invertir_lista(head);

    printf("\nLista original en orden inverso:\n");
    imprimir_lista(head);

    liberar_lista(head);

    return 0;
}