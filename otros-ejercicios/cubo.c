#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRODUCTOS 197
#define ANIOS 6
#define MESES 12
#define TOTAL_MESES (ANIOS * MESES)

int cubo[PRODUCTOS][ANIOS][MESES];

void cargar_datos(char *ruta)
{
    FILE *archivo = fopen(ruta, "r");
    if (archivo == NULL)
    {
        printf("error: no se pudo abrir el archivo %s\n", ruta);
        exit(1);
    }
    char linea[4096];
    int p = 0;
    while (fgets(linea, sizeof(linea), archivo) != NULL && p < PRODUCTOS)
    {
        char *texto = linea;

        // si es la primera fila, omite los 3 caracteres invisibles del dataset
        if (p == 0 && (unsigned char)linea[0] == 239)
        {
            texto = linea + 3;
        }

        char *token = strtok(texto, ";\r\n");
        int mes_absoluto = 0;

        while (token != NULL && mes_absoluto < TOTAL_MESES)
        { // calcular años y meses
            int a = mes_absoluto / MESES;
            int m = mes_absoluto % MESES;

            cubo[p][a][m] = atoi(token);

            token = strtok(NULL, ";\r\n");
            mes_absoluto++;
        }
        p++;
    }
    fclose(archivo);
}

// suma las ventas de un producto en un rango de meses (0 a 71)
long sumar_ventas(int producto, int mes_ini, int mes_fin)
{
    long suma = 0;
    for (int k = mes_ini; k <= mes_fin; k++)
    {
        int a = k / MESES;
        int m = k % MESES;
        suma += cubo[producto][a][m];
    }
    return suma;
}

int pedir_numero(char *mensaje)
{
    int valor;
    printf("%s: ", mensaje);
    scanf("%d", &valor);
    return valor;
}

// encuentra el producto mas vendido en un rango de meses
void mas_vendido_rango(int ini, int fin)
{
    int mejor_producto = 0;
    long max_ventas = -1;

    for (int p = 0; p < PRODUCTOS; p++)
    {
        long ventas = sumar_ventas(p, ini, fin);
        if (ventas > max_ventas)
        {
            max_ventas = ventas;
            mejor_producto = p;
        }
    }
    printf("producto %d con %ld unidades\n", mejor_producto + 1, max_ventas);
}

void q1_anio()
{
    int a = pedir_numero("anio (1-6)") - 1;
    mas_vendido_rango(a * MESES, a * MESES + MESES - 1);
}

// funciones para encontrar producto mas vendido en cada categoria
void q1_mes()
{
    int a = pedir_numero("anio (1-6)") - 1;
    int m = pedir_numero("mes (1-12)") - 1;
    mas_vendido_rango(a * MESES + m, a * MESES + m);
}

void q1_periodo()
{
    int i = pedir_numero("mes inicial absoluto (1-72)") - 1;
    int f = pedir_numero("mes final absoluto (1-72)") - 1;
    mas_vendido_rango(i, f);
}

void promedio_max_rango(int ini, int fin)
{
    int mejor_producto = 0;
    double max_promedio = -1;
    int cantidad_meses = fin - ini + 1;

    for (int p = 0; p < PRODUCTOS; p++)
    {
        double promedio = (double)sumar_ventas(p, ini, fin) / cantidad_meses;
        if (promedio > max_promedio)
        {
            max_promedio = promedio;
            mejor_producto = p;
        }
    }
    printf("producto %d con promedio %.2f unidades/mes\n", mejor_producto + 1, max_promedio);
}

// funciones para encontrar el mayor promedio de ventas
void q2_cada_anio()
{
    for (int a = 0; a < ANIOS; a++)
    {
        printf("anio %d:\n", a + 1);
        promedio_max_rango(a * MESES, a * MESES + MESES - 1);
    }
}

void q2_periodo()
{
    int i = pedir_numero("mes inicial absoluto (1-72)") - 1;
    int f = pedir_numero("mes final absoluto (1-72)") - 1;
    promedio_max_rango(i, f);
}

void q3()
{
    int mejor_anio = 0;
    long max_ventas = -1;

    for (int a = 0; a < ANIOS; a++)
    {
        long suma_anio = 0;

        for (int p = 0; p < PRODUCTOS; p++)
        {
            for (int m = 0; m < MESES; m++)
            {
                suma_anio += cubo[p][a][m];
            }
        }
        printf("  anio %d: %ld unidades\n", a + 1, suma_anio);
        if (suma_anio > max_ventas)
        {
            max_ventas = suma_anio;
            mejor_anio = a;
        }
    }
    printf("el mejor anio fue el %d con %ld unidades\n", mejor_anio + 1, max_ventas);
}

void q4()
{
    int p = pedir_numero("producto (1-197)") - 1;
    int m = pedir_numero("mes (1-12)") - 1;
    int mejor_anio = 0;

    for (int a = 1; a < ANIOS; a++)
    {
        if (cubo[p][a][m] > cubo[p][mejor_anio][m])
        {
            mejor_anio = a;
        }
    }
    printf("anio %d (%d unidades del producto %d en el mes %d)\n",
           mejor_anio + 1, cubo[p][mejor_anio][m], p + 1, m + 1);
}

int main()
{
    cargar_datos("ventas.csv");
    printf("datos cargados correctamente\n");

    int opcion = -1;
    while (opcion != 0)
    {
        printf("1 producto mas vendido por anio\n");
        printf("2 producto mas vendido por mes\n");
        printf("3 producto mas vendido por periodo\n");
        printf("4 mayor promedio de ventas en cada anio\n");
        printf("5 mayor promedio de ventas por periodo\n");
        printf("6 anio con mayor cantidad de unidades vendidas\n");
        printf("7 anio en que mas se vendio el producto N en el mes M\n");
        printf("0 salir\n");

        opcion = pedir_numero("elige una opcion");
        switch (opcion)
        {
        case 1:
            q1_anio();
            break;
        case 2:
            q1_mes();
            break;
        case 3:
            q1_periodo();
            break;
        case 4:
            q2_cada_anio();
            break;
        case 5:
            q2_periodo();
            break;
        case 6:
            q3();
            break;
        case 7:
            q4();
            break;
        case 0:
            printf("saliendo\n");
            break;
        default:
            printf("elija una opcion correcta\n");
            break;
        }
    }
    return 0;
}