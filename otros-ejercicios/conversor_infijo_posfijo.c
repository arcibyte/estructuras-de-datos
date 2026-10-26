// Jhon Arciniegas 2243561
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // para atof() (convertir texto a flotante)
#include <math.h>

int prioridad(char operador)
{
    if (operador == '^')
        return 3;
    if (operador == '*' || operador == '/')
        return 2;
    if (operador == '+' || operador == '-')
        return 1;
    return 0;
}
int main()
{
    char linea[300];
    char tokens[100][50];
    int totalTokens = 0;
    char pilaOperadores[100];
    int tope = -1;
    // cola/salida para la expresion en formato posfijo
    char salida[100][50];
    int totalSalida = 0;

    if (fgets(linea, sizeof(linea), stdin) != NULL)
    {
        char *token = strtok(linea, " \n");
        while (token != NULL)
        {
            strcpy(tokens[totalTokens], token);
            totalTokens++;
            token = strtok(NULL, " \n");
        }
    }
    for (int i = 0; i < totalTokens; i++)
    {
        char *t = tokens[i];
        // regla a, si es un numero, va directo a la salida
        if (t[0] >= '0' && t[0] <= '9')
        {
            strcpy(salida[totalSalida], t);
            totalSalida++;
        }
        // regla b, si es un parentesis que abre '(', va a la pila
        else if (t[0] == '(')
        {
            tope++;
            pilaOperadores[tope] = t[0];
        }
        // regla c, si es un parentesis que cierra ')', vacia la pila a la salida hasta encontrar el '('
        else if (t[0] == ')')
        {
            while (tope >= 0 && pilaOperadores[tope] != '(')
            {
                salida[totalSalida][0] = pilaOperadores[tope];
                salida[totalSalida][1] = '\0';
                totalSalida++;
                tope--;
            }
            tope--;
        }
        // regla d, para ver si es un operador (+, -, *, /, ^)
        else
        {
            while (tope >= 0 && pilaOperadores[tope] != '(')
            {
                int prioTope = prioridad(pilaOperadores[tope]);
                int prioToken = prioridad(t[0]);
                // ^ es asociativo por la derecha (>), los demas por la izquierda (>=)
                if ((t[0] == '^' && prioTope > prioToken) ||
                    (t[0] != '^' && prioTope >= prioToken))
                {
                    salida[totalSalida][0] = pilaOperadores[tope];
                    salida[totalSalida][1] = '\0';
                    totalSalida++;
                    tope--;
                }
                else
                {
                    break; // rompe el ciclo si no cumple
                }
            }
            tope++;
            pilaOperadores[tope] = t[0];
        }
    }
    // vaciar cualquier operador que haya sobrado en la pila
    while (tope >= 0)
    {
        salida[totalSalida][0] = pilaOperadores[tope];
        salida[totalSalida][1] = '\0';
        totalSalida++;
        tope--;
    }
    // imprimir la expresion posfija
    for (int i = 0; i < totalSalida; i++)
    {
        printf("%s", salida[i]);
    }
    printf("\n");

    float pilaEvaluacion[100];
    int topeEval = -1;

    for (int i = 0; i < totalSalida; i++)
    {
        char *t = salida[i];

        if (t[0] >= '0' && t[0] <= '9')
        {
            topeEval++;
            pilaEvaluacion[topeEval] = atof(t);
        }
        else
        {
            float b = pilaEvaluacion[topeEval];
            topeEval--;
            float a = pilaEvaluacion[topeEval];
            topeEval--;
            float resultado = 0;
            if (t[0] == '+')
                resultado = a + b;
            else if (t[0] == '-')
                resultado = a - b;
            else if (t[0] == '*')
                resultado = a * b;
            else if (t[0] == '/')
                resultado = a / b;
            else if (t[0] == '^')
                resultado = pow(a, b);
            topeEval++;
            pilaEvaluacion[topeEval] = resultado;
        }
    }
    printf("%g\n", pilaEvaluacion[topeEval]);
    return 0;
}