#include <stdio.h>

int main()
{
    float numeros[10];

    printf("Ingrese 10 numeros:\n");
    for (int i = 0; i < 10; i++)
    {
        scanf("%f", &numeros[i]);
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (numeros[j] > numeros[j + 1])
            {
                float aux = numeros[j];
                numeros[j] = numeros[j + 1];
                numeros[j + 1] = aux;
            }
        }
    }

    float segundo_menor = -1;
    for (int i = 1; i < 10; i++)
    {
        if (numeros[i] > numeros[0])
        {
            segundo_menor = numeros[i];
            break;
        }
    }

    float segundo_mayor = -1;
    for (int i = 8; i >= 0; i--)
    {
        if (numeros[i] < numeros[9])
        {
            segundo_mayor = numeros[i];
            break;
        }
    }

    if (segundo_menor == -1 && segundo_mayor == -1)
    {
        printf("Todos los números ingresados son iguales.\n");
    }
    else
    {
        if (segundo_menor != -1)
            printf("segundo menor: %.2f\n", segundo_menor);
        else
            printf("no hay segundo menor, todos los menores son iguales.\n");

        if (segundo_mayor != -1)
            printf("segundo mayor: %.2f\n", segundo_mayor);
        else
            printf("no hay segundo mayor, todos los mayores son iguales.\n");
    }

    return 0;
}