/*
Sea un tablero de Ajedrez reducido de 6 x 6 casillas, en el cual solo hay una pieza a la vez,
puede ser un una Torre (T) o un Caballo (C). Tal situación se representa en un archivo de
entrada llamado 02-tableroin.txt de la siguiente manera:

Entrada: 02-tableroin.txt
******
******
******
***C**
******
******

Un asterisco representa una celda vacía, y una letra (T, C) una celda ocupada por una Torre o
un Caballo. Solo debe ir las celdas, la numeración de las filas y columnas es para referencia.

Codifique un algoritmo que lea ese archivo y determine la celda donde se encuentra la pieza
(fila y columna) e imprima por pantalla esa información; luego imprima también una lista de los
posibles movimientos (pares de filas y columnas) que puede realizar la pieza de acuerdo a la
ubicación encontrada, es decir aquellas que estén dentro del tablero, de modo que el usuario
puede elegir uno de esos posibles movimientos.

Una vez elegida la nueva posición de la pieza, se debe imprimir el tablero con esa modificación
en un archivo llamado 02-tablerout.txt.

Cada pieza tiene un tipo de movimiento asociado, los cuales se muestran en las siguientes
imágenes:
*/
#include <stdio.h>

// encuentra la posicion del pieza como el tipo de pieza
void posicion_pieza(int* fil,int* col,char* pieza);

// mostrar los posibles movimientos de la pieza
void mostrar_posibles_movimientos(int fil,int col,char pieza);

// modificar el tablero de salida
void modificacion_tablero(int fil,int col,char pieza);

// mostrar las opciones de movimiento en terminal
void opciones_en_pantalla();

int main(){
    opciones_en_pantalla();
    return 0;
}

void opciones_en_pantalla(){
    int fil,col;
    char pieza;

    // la posicion la pieza como el tipo de pieza
    posicion_pieza(&fil,&col,&pieza);

    // verificar el tipo de pieza
    if( pieza == 'C' ){
        printf("Caballo encontrado en la posición (%d,%d).\n",fil,col);
    }else if( pieza == 'T'){
        printf("Torre encontrada en la posición (%d,%d).\n",fil,col);
    }
    
    printf("Los posibles movimientos son:\n");
    // los posibles movimiento de cada pieza
    mostrar_posibles_movimientos(fil,col,pieza);
    printf("Seleccione uno de ellos (fil, col):\n");
    scanf("%d%d",&fil,&col);

    // modificar el tablero de salida
    modificacion_tablero(fil,col,pieza);
}

// mostrar las posibles movimientos que tiene la pieza
void mostrar_posibles_movimientos(int fil,int col,char pieza){
    int primero = 1; // Para controlar la puntuacion
    
    if( pieza == 'T' ){
        // Movimientos verticales
        for(int i=-2; i <= 2; i++){
            if( fil + i >= 1 && fil + i <= 6){
                if(!primero) {
                    printf(";");
                }
                printf("(%d,%d)",fil+i,col);
                primero = 0;
            }
        }
        
        // Movimientos horizontales
        for(int i=-2; i <= 2; i++){
            if( col + i >= 1 && col + i <= 6){
                if(!primero) printf(";");
                printf("(%d,%d)",fil,col+i);
                primero = 0;
            }
        }
        printf(".\n");
        
    }else{

            // Movimientos del caballo 
            for(int dx = -2; dx <= 2; dx++){
                for(int dy = -2; dy <= 2; dy++){
                    // El caballo se mueve en L: |dx| + |dy| = 3 y dx != 0 y dy != 0
                    int abs_dx = (dx < 0) ? -dx : dx;
                    int abs_dy = (dy < 0) ? -dy : dy;
                    
                    if(abs_dx + abs_dy == 3 && dx != 0 && dy != 0){
                        int nueva_fil = fil + dx;
                        int nueva_col = col + dy;
                        
                        if(nueva_fil >= 1 && nueva_fil <= 6 && nueva_col >= 1 && nueva_col <= 6){
                            if(!primero) printf(";");
                            printf("(%d,%d)",nueva_fil,nueva_col);
                            primero = 0;
                        }
                    }
                }
            }
            printf(".\n");
        
    }
}

// lectura del tablero de entrada y posicion y tipo de pieza
void posicion_pieza(int* fil,int* col,char* pieza){
    FILE *tablero = fopen("02-tableroin.txt","r");

    if( tablero == NULL ){
        printf("Error de archivo.\n");
        return;
    }

    for(int i=1; i <= 6; i++){
        for(int j=1; j <= 6; j++){
            char letra;
            // Leer ignorando espacios y saltos de linea
            do {
                fscanf(tablero,"%c",&letra);
            } while(letra == ' ' || letra == '\n' || letra == '\r');
            
            if( letra == 'T' || letra == 'C'){
                *pieza = letra;
                *fil = i;
                *col = j;
                fclose(tablero);
                return; // Encontro la pieza, salir
            }
        }
    }

    fclose(tablero);
}

// crea el archivo de salida para el tablero de salida
void modificacion_tablero(int fil,int col,char pieza){
    FILE *tablero = fopen("02-tablerout.txt","w");

    if(tablero == NULL){
        printf("Error al crear el archivo.\n");
        return;
    }

    for(int i=1; i <= 6; i++){
        for(int j=1; j <= 6; j++){
            if( fil == i && col == j ){
                fprintf(tablero,"%c",pieza);
            }else{
                fprintf(tablero,"*");
            }
        }
        fprintf(tablero,"\n");
    }

    fclose(tablero);
    printf("Tablero actualizado correctamente.\n");
}
