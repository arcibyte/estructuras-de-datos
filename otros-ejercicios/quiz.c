#include <stdio.h>
#include <string.h>

// Jhon Arciniegas 2243561

int main()
{
    char token[200];
    // se agrega el arreglo para guardar todos los tokens en memoria
    char tokens[100][50];
    int totalTokens = 0;

    char pilaOperadores[100]; // arreglo para guardar los operadores temporalmente
    int tope = -1;            // empieza en -1 porque la pila esta vacia

    // otro arreglo para guardar la salida en orden posfijo (la cola/salida)
    char salida[100][50];
    int totalSalida = 0;

    int contadorNumeros = 0;
    int contadorOperadores = 0;

    printf("ingrese la expresion ej: 5 + 3 * 2, (maximo 200 caracteres):\n");
    printf("(no olvide dejar espacios entre cada elemento)\n\n");

    while (scanf("%s", token) == 1)
    {
        // guardamos una copia del token actual en el arreglo de memoria
        strcpy(tokens[totalTokens], token);
        totalTokens++;

        if (token[0] >= '0' && token[0] <= '9')
        {
            printf("  [operando]  -> %s\n", token);
            contadorNumeros++;
        }
        else if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/' || token[0] == '^')
        {
            printf("  [operador]  -> %s\n", token);
            contadorOperadores++;

            // cuando es un operador, lo subimos (push) a la pila de operadores
            // tope++;
            // pilaOperadores[tope] = token[0];
            // ------------------------------------------
        }
        else if (token[0] == '(')
        {
            printf("  [parentesis] -> abre (\n");
        }
        else if (token[0] == ')')
        {
            printf("  [parentesis] -> cierra )\n");
        }
    }

    printf("\ntotal de numeros encontrados: %d\n", contadorNumeros);
    printf("total de operadores encontrados: %d\n", contadorOperadores);
    printf("total de tokens almacenados en el arreglo: %d\n", totalTokens);

    return 0;
}