#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000

// estructuras de datos
typedef struct {
    int depredadores, plagas, viento;
} sembrario;

typedef struct {
    int x, y;
} direccionViento;

// aleatorio(0, 10) -> Genera números aleatorios entre 0 y 10
int aleatorio(int minimo, int maximo);

int existePunto(int posX, int posY, int fil, int col);
// funcion encargada de la salida de datos
void salida_archivo(int k, int cantSimulacion, int fil, int col, char arboles[][MAX]);
// funcion encargada de transformar un matriz de caracteres
void transformar_arrays(int fil, int col, sembrario arboles[][MAX], char arr[][MAX]);

void cambiarVientoAleatorio(int fil, int col, sembrario arboles[][MAX]);

void desplazamientoPlagasYDepredadores(int k, int fil, int col, sembrario arboles[][MAX]);

void simulacion(int cantSimulacion, int fil, int col, sembrario arboles[][MAX]);
// funcion encargada de recopilar datos
void lectura_archivo(sembrario arboles[][MAX], int *cantSimulaciones, int *fil, int *col);

sembrario res[MAX][MAX];
char aux[MAX][MAX];
direccionViento dv[8] = {{-1,-1}, {0,-1}, {1,-1}, {-1,0}, {1,0}, {-1,1}, {0,1}, {1,1}};

int main() {
    
    int cantSimulaciones, fil, col;
    
    lectura_archivo(res, &cantSimulaciones, &fil, &col);
    simulacion(cantSimulaciones, fil, col,res);
    
    return 0;
}

void lectura_archivo(sembrario arboles[][MAX], int *cantSimulaciones, int *fil, int *col) {
    FILE *datos = fopen("sembradoin.txt", "r");

    if (datos == NULL) {
        printf("Error en lectura de archivos\n");
        return;
    }

    int posX, posY;
    fscanf(datos, "%d\n%d %d", cantSimulaciones, fil, col);

    // Inicializar matriz
    for (int i = 0; i <= *fil; i++) {
        for (int j = 0; j <= *col; j++) {
            arboles[i][j].plagas = 0;
            arboles[i][j].depredadores = 0;
            arboles[i][j].viento = 0;
        }
    }

    while (!feof(datos)) {
        fscanf(datos, "%d %d", &posX, &posY);
        if (existePunto(posX, posY, *fil, *col)) {
            fscanf(datos, "%d %d %d",
                &arboles[posX][posY].plagas,
                &arboles[posX][posY].depredadores,
                &arboles[posX][posY].viento
            );
        }
    }

    fclose(datos);
}

void transformar_arrays(int fil, int col, sembrario arboles[][MAX], char arr[][MAX]) {
    for (int i = 0; i <= fil; i++) {
        for (int j = 0; j <= col; j++) {
            if (arboles[i][j].depredadores > 0 && arboles[i][j].plagas > 0) {
                arr[i][j] = 'M';  // Mixto
            } else if (arboles[i][j].depredadores > 0) {
                arr[i][j] = 'D';  // Depredadores
            } else if (arboles[i][j].plagas > 0) {
                arr[i][j] = 'P';  // Plagas
            } else {
                arr[i][j] = ' ';  // Vacío
            }
        }   
    }
}

void salida_archivo(int k, int cantSimulacion, int fil, int col, char arboles[][MAX]) {
    FILE *salida = fopen("sembradoout.txt", k == 1 ? "w" : "a");  

    if (salida == NULL) {
        printf("Error al abrir archivo de salida\n");
        return;
    }

    fprintf(salida, "Simulacion %d:\n", k);
    for (int i = 0; i <= fil; i++) {
        for (int j = 0; j <= col; j++) {
            fprintf(salida, "%c ", arboles[i][j]);   
        }
        fprintf(salida, "\n");
    }
    fprintf(salida, "\n");

    fclose(salida);
}

// aleatorio(0, 10) -> Genera números aleatorios entre 0 y 10
int aleatorio(int minimo, int maximo) {
    static int inicializado = 0;
    if (!inicializado) {
        srand(time(NULL));
        inicializado = 1;
    }
    return minimo + rand() % (maximo - minimo + 1);
}

void simulacion(int cantSimulacion, int fil, int col, sembrario arboles[][MAX]) {
    for (int k = 1; k <= cantSimulacion; k++) {
        transformar_arrays(fil, col, arboles, aux);
        salida_archivo(k, cantSimulacion, fil, col, aux);
        cambiarVientoAleatorio(fil, col, arboles);
        desplazamientoPlagasYDepredadores(k, fil, col, arboles);
    }
}

void cambiarVientoAleatorio(int fil, int col, sembrario arboles[][MAX]) {
    for (int i = 0; i <= fil; i++) {
        for (int j = 0; j <= col; j++) {
            int elem = aleatorio(0, 7);  // 8 direcciones posibles
            arboles[i][j].viento = elem;   
        }
    }
}
// inicilizamos de forma global 
sembrario nuevo[MAX][MAX] = {0};

void desplazamientoPlagasYDepredadores(int k, int fil, int col, sembrario arboles[][MAX]) {
    // Copiar estado actual
    for (int i = 0; i <= fil; i++) {
        for (int j = 0; j <= col; j++) {
            nuevo[i][j] = arboles[i][j];
        }
    }

    for (int i = 0; i <= fil; i++) {
        for (int j = 0; j <= col; j++) {
            int dir = arboles[i][j].viento;
            int nuevaX = i + dv[dir].x;
            int nuevaY = j + dv[dir].y;

            // Verificar movimiento válido
            if (existePunto(nuevaX, nuevaY, fil, col)) {
                // Interaccion depredadores-plagas
                if (arboles[i][j].depredadores > 0 && arboles[nuevaX][nuevaY].plagas > 0) {
                    if (nuevo[nuevaX][nuevaY].plagas > 0) {
                        nuevo[nuevaX][nuevaY].plagas--;
                    }
                }

                // Propagacion de plagas
                if (arboles[i][j].plagas > 10) {
                    nuevo[nuevaX][nuevaY].plagas++;
                }
            }

            // Reproduccion de depredadores cada 3 iteraciones
            if (arboles[i][j].depredadores > 4 && (k % 3) == 0) {
                nuevo[i][j].depredadores += 2;
            }
        }
    }
    
    // Actualizar estado
    for (int i = 0; i <= fil; i++) {
        for (int j = 0; j <= col; j++) {
            arboles[i][j] = nuevo[i][j];
        }
    }
}

int existePunto(int posX, int posY, int fil, int col) {
    return (posX >= 0 && posX <= fil && posY >= 0 && posY <= col);
}