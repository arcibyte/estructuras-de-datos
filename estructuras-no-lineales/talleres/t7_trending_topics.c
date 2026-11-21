#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nombre[64];
    int frecuencia;
    int orden;
} Hashtag;

typedef struct
{
    Hashtag *datos;
    int tamano;
    int capacidad;
} MaxHeap;

MaxHeap crearHeap(int capacidadInicial)
{
    MaxHeap h;
    h.capacidad = capacidadInicial > 0 ? capacidadInicial : 64;
    h.datos = (Hashtag *)malloc((size_t)h.capacidad * sizeof(Hashtag));
    if (h.datos == NULL)
    {
        exit(EXIT_FAILURE);
    }
    h.tamano = 0;
    return h;
}

void liberarHeap(MaxHeap *h)
{
    free(h->datos);
    h->datos = NULL;
    h->tamano = 0;
    h->capacidad = 0;
}

// en este codigo eetorna 1 si a es mayor prioridad que b en el max-heap
int esMayor(Hashtag a, Hashtag b)
{
    if (a.frecuencia != b.frecuencia)
    {
        return a.frecuencia > b.frecuencia;
    }
    return a.orden < b.orden;
}

void intercambiar(Hashtag *a, Hashtag *b)
{
    Hashtag temp = *a;
    *a = *b;
    *b = temp;
}

void flotar(MaxHeap *h, int i)
{
    while (i > 0)
    {
        int padre = (i - 1) / 2;
        if (esMayor(h->datos[i], h->datos[padre]))
        {
            intercambiar(&h->datos[i], &h->datos[padre]);
            i = padre;
        }
        else
        {
            break;
        }
    }
}

void hundir(MaxHeap *h, int i)
{
    while (1)
    {
        int mayor = i;
        int izq = 2 * i + 1;
        int der = 2 * i + 2;

        if (izq < h->tamano && esMayor(h->datos[izq], h->datos[mayor]))
        {
            mayor = izq;
        }
        if (der < h->tamano && esMayor(h->datos[der], h->datos[mayor]))
        {
            mayor = der;
        }

        if (mayor != i)
        {
            intercambiar(&h->datos[i], &h->datos[mayor]);
            i = mayor;
        }
        else
        {
            break;
        }
    }
}

void insertarDirecto(MaxHeap *h, Hashtag item)
{
    if (h->tamano >= h->capacidad)
    {
        h->capacidad *= 2;
        Hashtag *temp = (Hashtag *)realloc(h->datos, (size_t)h->capacidad * sizeof(Hashtag));
        if (temp == NULL)
        {
            free(h->datos);
            exit(EXIT_FAILURE);
        }
        h->datos = temp;
    }

    h->datos[h->tamano] = item;
    flotar(h, h->tamano);
    h->tamano++;
}

// incrementa la frecuencia si el hashtag ya existe en el heap, o lo inserta con frecuencia 1
void registrarHashtag(MaxHeap *h, const char *texto, int *contadorOrden)
{
    for (int i = 0; i < h->tamano; i++)
    {
        if (strcmp(h->datos[i].nombre, texto) == 0)
        {
            h->datos[i].frecuencia++;
            flotar(h, i);
            return;
        }
    }

    Hashtag nuevo;
    strncpy(nuevo.nombre, texto, sizeof(nuevo.nombre) - 1);
    nuevo.nombre[sizeof(nuevo.nombre) - 1] = '\0';
    nuevo.frecuencia = 1;
    nuevo.orden = (*contadorOrden)++;

    insertarDirecto(h, nuevo);
}

int extraerMax(MaxHeap *h, Hashtag *extraido)
{
    if (h->tamano == 0)
    {
        return 0;
    }

    *extraido = h->datos[0];
    h->tamano--;

    if (h->tamano > 0)
    {
        h->datos[0] = h->datos[h->tamano];
        hundir(h, 0);
    }

    return 1;
}

void mostrarTop5(MaxHeap *h)
{
    Hashtag extraidos[5];
    int cantidad = 0;

    while (cantidad < 5 && extraerMax(h, &extraidos[cantidad]))
    {
        if (cantidad > 0)
        {
            printf(" ");
        }
        printf("%s", extraidos[cantidad].nombre);
        cantidad++;
    }
    printf("\n");

    // reinsertar los hashtags extraidos para conservar el acumulado
    for (int i = 0; i < cantidad; i++)
    {
        insertarDirecto(h, extraidos[i]);
    }
}

int main(int argc, char *argv[])
{
    FILE *entrada = NULL;
    int cerrarArchivo = 0;

    if (argc > 1)
    {
        entrada = fopen(argv[1], "r");
        if (entrada != NULL)
        {
            cerrarArchivo = 1;
        }
    }

    if (entrada == NULL)
    {
        entrada = stdin;
    }

    MaxHeap heap = crearHeap(64);
    char token[64];
    int contadorOrden = 0;

    while (fscanf(entrada, "%63s", token) == 1)
    {
        if (strcmp(token, "TT") == 0)
        {
            mostrarTop5(&heap);
        }
        else
        {
            registrarHashtag(&heap, token, &contadorOrden);
        }
    }

    if (cerrarArchivo)
    {
        fclose(entrada);
    }

    liberarHeap(&heap);
    return 0;
}