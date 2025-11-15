No se evaluará su entrega si emplea arreglos o estructuras (temas que no han sido
cubiertos en clase todavía).

Procure revisar el documento en su totalidad. 

# Ejercicio 2. Ajedrez 6x6

Sea un tablero de Ajedrez reducido de 6 x 6 casillas, en el cual solo hay una pieza a la vez, puede ser una Torre (T) o un Caballo (C). Tal situación se representa en un archivo de entrada llamado `02-tableroin.txt`.

|   | 1 | 2 | 3 | 4 | 5 | 6 |
|---|---|---|---|---|---|---|
| 1 | * | * | * | * | * | * |
| 2 | * | * | * | * | * | * |
| 3 | * | * | * | * | * | * |
| 4 | * | * | * | C | * | * |
| 5 | * | * | * | * | * | * |
| 6 | * | * | * | * | * | * |

Un asterisco representa una celda vacía, y una letra (T, C) una celda ocupada por una Torre o un Caballo. 
Solo debe ir las celdas, la numeración de las filas y columnas es para referencia.

Codifique un algoritmo que lea ese archivo y determine la celda donde se encuentra la pieza (fila y columna) e imprima por pantalla esa información; 
luego imprima también una lista de los posibles movimientos (pares de filas y columnas) que puede realizar la pieza de acuerdo a la ubicación encontrada, 
es decir aquellas que estén dentro del tablero, de modo que el usuario puede elegir uno de esos posibles movimientos.

Una vez elegida la nueva posición de la pieza, se debe imprimir el tablero con esa modificación en un aSin embargo, para la Torre el movimiento queda limitado a un máximo de dos cuadros en
cada dirección.

Para el archivo de ejemplo, la interacción por pantalla debería ser:rchivo llamado 02-tablerout.txt.

Caballo encontrado en la posición (4, 4).
Los posibles movimientos son:
(2, 3); (2, 5); (6, 3); (6, 5); (3, 2); (5, 2); (3, 6); (5, 6).
Seleccione uno de ellos (fil, col): 6 3

Para esta elección el archivo de salida debería ser:

|   | 1 | 2 | 3 | 4 | 5 | 6 |
|---|---|---|---|---|---|---|
| 1 | * | * | * | * | * | * |
| 2 | * | * | * | * | * | * |
| 3 | * | * | * | * | * | * |
| 4 | * | * | * | * | * | * |
| 5 | * | * | * | * | * | * |
| 6 | * | * | C | * | * | * |

Utilice funciones o procedimientos para hallar la posición de la pieza en el tablero inicial, así
como para calcular los posibles movimientos y el tablero actualizado.
