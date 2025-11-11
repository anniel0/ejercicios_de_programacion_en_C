/*
Existe un cierto tipo de insecto (llamado la plaga) que diezma los naranjos, y a su vez existe otro
tipo que ataca a la plaga, al cual llamaremos depredador. Comúnmente, donde habita la plaga
hay presencia de depredadores, sin embargo, éstos son torpes en el ataque, de modo que solo
lo hacen si hay plaga en un entorno bastante cercano.

La empresa de agroquímicos KLRS C.A. lo ha contratado para que haga la simulación del
comportamiento de ambos tipos de insectos durante lapsos variables en un terreno que tiene un
arreglo de árboles de naranja de fil x col.

El equipo de biólogos de la empresa ha estudiado el fenómeno durante un tiempo considerable
y ha llegado a la siguiente conclusión:

1) Los depredadores eliminan plaga (de uno en uno por ciclo de simulación) si están en
los árboles cercanos o en donde se encuentran en cierto ciclo. Por cercano se tiene a los
árboles vecinos en las ocho direcciones cardinales (Norte, Sur, etc.). Si no hay plaga en
esos vecinos, debe trasladarse hacia cualquier dirección de manera aleatoria en busca
de plaga.

2) La plaga abandona un árbol, solo si está sobre-poblado de plaga, y se dirige al árbol
vecino, según la dirección del viento. Por sobre-población se entiende a la existencia de
más de 10 ejemplares aproximadamente en un árbol, y la dirección del viento es hacia
alguna dirección cardinal.

3) El desplazamiento de un árbol a otro y la aniquilación de una plaga por un depredador
se hacen por cada ciclo de simulación, de uno en uno. La reproducción se hace por
cada tres ciclos de simulación entre las parejas de cada especie, de uno en uno. Por
ejemplo, si en un árbol hay 5 depredadores, implica la existencia de 2 parejas, lo que
conlleva al nacimiento de 2 depredadores adicionales en el siguiente ciclo. Si en el árbol
hay 1 depredador, significa que no hay parejas, por lo cual, el número de depredadores
permanece igual.

4) Un depredador muere, cuando es minoría respecto a la plaga en un árbol i (se reduce el
número de depredadores uno en uno por cada ciclo).

Por lo tanto, por cada árbol se tiene la siguiente información: el número de plaga y depredadores
así como la dirección del viento, la cual puede variar aleatoriamente en cada ciclo de simulación
hacia algunas de las direcciones cardinales.

Usted debe suministrarle esa información al programa de simulación que desarrolle, en un
archivo llamado sembradoin.txt, el cual tiene la siguiente estructura:

cs
nm
fi ci npi ndi dvi
fj cj npj ndj dvj
.
.
.
fk ck npk ndk dvk

Donde, cs ≥ 20 es el número de ciclos de simulación, n y m son los números de fila y columna
respectivamente del sembrado; fi ≤ n y ci ≤ m, son las coordenadas del árbol; npi y ndi, son la
cantidad de plaga y depredadores en el árbol i respectivamente, y dvi es la dirección inicial del
viento (durante la simulación, ésta varía aleatoriamente) según la siguiente lista:

    N = 0, S = 1, E = 2, O = 3, NE = 4, NO = 5, SE = 6, SO = 7.

El programa a desarrollar debe generar un archivo de salida llamado sembradoout.txt, que
contenga “pantallas” de la configuración del sembrado, de acuerdo al siguiente formato:
Debe aparecer una M, si en cierto árbol hay tanto plaga como depredadores, una P si hay plaga
solamente, y una D para depredadores solamente. Si en el árbol no hay ninguno de los dos tipos,
se deja vacío.

El número de pantallas a aparecer son cinco: La configuración inicial del sembrado justo después
de leer el archivo de entrada, la configuración cuando han transcurrido el 25%, 50%, 75%, 100%
de los ciclos respectivamente.
*/

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
