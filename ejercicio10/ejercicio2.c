#include <stdio.h>

// lectura de los archivos de entrada y salida
void lectura_archivo();

// determinar el numero en base a simbolo morse
char letra_resultante(int numero);

int main()
{
    lectura_archivo();
    return 0;
}

// lectura de los archivos de entrada y salida
void lectura_archivo()
{
    FILE *entrada = fopen("morse.txt", "r"),
         *salida = fopen("mensaje.txt", "w");

    if (entrada == NULL)
    {
        return;
    }
    char letra;
    int suma = 0;
    while (fscanf(entrada, "%c", &letra) != EOF)
    {
        if (letra == ' ')
        {
            fprintf(salida, "%c", letra_resultante(suma));
            suma = 0;
        }
        else if (letra == '.')
        {
            suma = suma * 10 + 1;
        }
        else if (letra == '-')
        {
            suma = suma * 10 + 2;
        }
        else if (letra == '\n')
        {
            fprintf(salida, "\n");
            suma = 0;
        }
    }
    fprintf(salida, "%c", letra_resultante(suma));
    fprintf(salida, "\n");

    fclose(entrada);
    fclose(salida);
}

// determinar el numero en base a simbolo morse
char letra_resultante(int numero)
{
    char letra;
    switch (numero)
    {
    case 12:
        letra = 'A';
        break;
    case 2111:
        letra = 'B';
        break;
    case 2121:
        letra = 'C';
        break;
    case 211:
        letra = 'D';
        break;
    case 1:
        letra = 'E';
        break;
    case 1121:
        letra = 'F';
        break;
    case 221:
        letra = 'G';
        break;
    case 1111:
        letra = 'H';
        break;
    case 11:
        letra = 'I';
        break;
    case 1222:
        letra = 'J';
        break;
    case 212:
        letra = 'K';
        break;
    case 1211:
        letra = 'L';
        break;
    case 22:
        letra = 'M';
        break;
    case 21:
        letra = 'N';
        break;
    case 222:
        letra = 'O';
        break;
    case 1221:
        letra = 'P';
        break;
    case 2212:
        letra = 'Q';
        break;
    case 121:
        letra = 'R';
        break;
    case 111:
        letra = 'S';
        break;
    case 2:
        letra = 'T';
        break;
    case 112:
        letra = 'U';
        break;
    case 1112:
        letra = 'V';
        break;
    case 122:
        letra = 'W';
        break;
    case 2112:
        letra = 'X';
        break;
    case 2122:
        letra = 'Y';
        break;
    case 2211:
        letra = 'Z';
        break;
    case 21121:
        letra = ' ';
        break;
    case 121212:
        letra = '.';
        break;
    case 22222:
        letra = '0';
        break;
    case 12222:
        letra = '1';
        break;
    case 11222:
        letra = '2';
        break;
    case 11122:
        letra = '3';
        break;
    case 11112:
        letra = '4';
        break;
    case 11111:
        letra = '5';
        break;
    case 21111:
        letra = '6';
        break;
    case 22111:
        letra = '7';
        break;
    case 22211:
        letra = '8';
        break;
    case 22221:
        letra = '9';
        break;
    default:
        break;
    }
    return letra;
}
