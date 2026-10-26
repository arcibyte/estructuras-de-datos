// ejercicio 4

#include <stdio.h>

int main()
{
    char arr[10];
    int freq[256] = {0};

    printf("ingrese 10 caracteres:\n");
    for (int i = 0; i < 10; i++)
    {
        scanf(" %c", &arr[i]);
        freq[(unsigned char)arr[i]]++;
    }
    printf("los tres caracteres con mayor frecuencia\n");

    printf("los tres caracteres con mayor frecuencia\n");
    for (int k = 0; k < 3; k++)
    {
        int max_freq = -1;
        int max_char = -1;

        for (int i = 0; i < 256; i++)
        {
            if (freq[i] > max_freq)
            {
                max_freq = freq[i];
                max_char = i;
            }
        }

        if (max_freq > 0)
        {
            printf("%c (frecuencia: %d)\n", (char)max_char, max_freq);
            freq[max_char] = 0; // hace que no se seleccione demas
        }
    }

    return 0;
}