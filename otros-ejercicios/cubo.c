#define ANIOS 5
#define PRODUCTOS 3
#define MESES 12

int cubo[ANIOS][PRODUCTOS][MESES];

// 1 producto mas vendido por año
int masVendidoAnio(int a)
{
    int best = 0, maxT = -1;
    for (int p = 0; p < PRODUCTOS; p++)
    {
        int t = 0;
        for (int m = 0; m < MESES; m++)
            t += cubo[a][p][m];
        if (t > maxT)
        {
            maxT = t;
            best = p;
        }
    }
    return best;
}

// 3) anio con mas unidades vendidas
int anioMayorVenta()
{
    int best = 0;
    long maxT = -1;
    for (int a = 0; a < ANIOS; a++)
    {
        long t = 0;
        for (int p = 0; p < PRODUCTOS; p++)
            for (int m = 0; m < MESES; m++)
                t += cubo[a][p][m];
        if (t > maxT)
        {
            maxT = t;
            best = a;
        }
    }
    return best;
}

// 4) anio en que mas se vendio el producto n en el mes m
int anioMaxProductoMes(int n, int m)
{
    int best = 0;
    for (int a = 1; a < ANIOS; a++)
        if (cubo[a][n][m] > cubo[best][n][m])
            best = a;
    return best;
}