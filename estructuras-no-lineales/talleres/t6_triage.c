// Jhon Arciniegas 2243561
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char cedula[32];
    int categoria;
    long long ordenLlegada;
} Paciente;

typedef struct
{
    Paciente *datos;
    int tamano;
    int capacidad;
} MinHeap;

MinHeap crearHeap(int capacidadInicial)
{
    MinHeap h;
    h.capacidad = capacidadInicial > 0 ? capacidadInicial : 64;
    h.datos = (Paciente *)malloc((size_t)h.capacidad * sizeof(Paciente));
    if (h.datos == NULL)
    {
        exit(EXIT_FAILURE);
    }
    h.tamano = 0;
    return h;
}

void liberarHeap(MinHeap *h)
{
    free(h->datos);
    h->datos = NULL;
    h->tamano = 0;
    h->capacidad = 0;
}

int tieneMayorPrioridad(Paciente a, Paciente b)
{
    if (a.categoria != b.categoria)
    {
        return a.categoria < b.categoria;
    }
    return a.ordenLlegada < b.ordenLlegada;
}

void intercambiar(Paciente *a, Paciente *b)
{
    Paciente temp = *a;
    *a = *b;
    *b = temp;
}

void flotar(MinHeap *h, int i)
{
    while (i > 0)
    {
        int padre = (i - 1) / 2;
        if (tieneMayorPrioridad(h->datos[i], h->datos[padre]))
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

void hundir(MinHeap *h, int i)
{
    while (1)
    {
        int mejor = i;
        int izq = 2 * i + 1;
        int der = 2 * i + 2;

        if (izq < h->tamano && tieneMayorPrioridad(h->datos[izq], h->datos[mejor]))
        {
            mejor = izq;
        }
        if (der < h->tamano && tieneMayorPrioridad(h->datos[der], h->datos[mejor]))
        {
            mejor = der;
        }

        if (mejor != i)
        {
            intercambiar(&h->datos[i], &h->datos[mejor]);
            i = mejor;
        }
        else
        {
            break;
        }
    }
}

void insertarHeap(MinHeap *h, Paciente p)
{
    if (h->tamano >= h->capacidad)
    {
        h->capacidad *= 2;
        Paciente *temp = (Paciente *)realloc(h->datos, (size_t)h->capacidad * sizeof(Paciente));
        if (temp == NULL)
        {
            free(h->datos);
            exit(EXIT_FAILURE);
        }
        h->datos = temp;
    }

    h->datos[h->tamano] = p;
    flotar(h, h->tamano);
    h->tamano++;
}

int extraerMin(MinHeap *h, Paciente *atendido)
{
    if (h->tamano == 0)
    {
        return 0;
    }

    *atendido = h->datos[0];
    h->tamano--;

    if (h->tamano > 0)
    {
        h->datos[0] = h->datos[h->tamano];
        hundir(h, 0);
    }

    return 1;
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
        entrada = fopen("triage_data.txt", "r");
        if (entrada != NULL)
        {
            cerrarArchivo = 1;
        }
        else
        {
            entrada = stdin;
        }
    }

    MinHeap urgencias = crearHeap(128);
    char token[32];
    int categoria;
    long long contadorLlegada = 0;

    while (fscanf(entrada, "%31s", token) == 1)
    {
        if (strcmp(token, "000000") == 0)
        {
            Paciente atendido;
            if (extraerMin(&urgencias, &atendido))
            {
                printf("%s\n", atendido.cedula);
            }
        }
        else
        {
            if (fscanf(entrada, "%d", &categoria) != 1)
            {
                break;
            }

            // categoria 4 (Consulta externa) no ingresa al servicio de urgencias
            if (categoria >= 1 && categoria <= 3)
            {
                Paciente nuevo;
                strncpy(nuevo.cedula, token, sizeof(nuevo.cedula) - 1);
                nuevo.cedula[sizeof(nuevo.cedula) - 1] = '\0';
                nuevo.categoria = categoria;
                nuevo.ordenLlegada = contadorLlegada++;

                insertarHeap(&urgencias, nuevo);
            }
        }
    }

    if (cerrarArchivo)
    {
        fclose(entrada);
    }

    liberarHeap(&urgencias);
    return 0;
}