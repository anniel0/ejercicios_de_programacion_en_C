# Ejercicio 1. ¡Noche de Dardos y Amigos! (10 ptos)

¡La noche pintaba para ser legendaria! Tú, como el cerebro detrás de la operación, habías
arrastrado a tus dos mejores amigos, Maria y Luis, a ese bar nuevo del que tanto habías oído
hablar. El ambiente era perfecto: música a buen volumen, el murmullo de las conversaciones y, por
supuesto, la diana de dardos. La tentación fue demasiada; pronto estaban en medio de un
acalorado, aunque muy divertido, duelo de puntería.

Las rondas pasaron, las risas se multiplicaron, y con cada tiro, la puntuación se volvía más...
abstracta. Maria y Luis, fieles a su espíritu competitivo y a unas cuantas cervezas de más, llegaron
a un punto donde sumar dos más dos se sentía como resolver una ecuación cuántica. Los números
bailaban en sus ojos, las reglas se mezclaban, y el "ganador" era una noción cada vez más elusiva.

Tú, que observabas la escena con una mezcla de diversión y la habitual pereza por hacer
cálculos manuales, tuviste una epifanía. "¡Esto es ridículo!", pensaste. "¡Tenemos la tecnología!
¡Esto es un trabajo para un programa!". Y así, con el eco de las risas etílicas de tus amigos de
fondo y un desafío personal en mente, decidiste que esta noche no se resolvería a golpes de
calculadora mental, sino con la elegancia y la precisión del código.
La Diana y Puntuaciones

Imagina una diana de dardos ubicada en el plano cartesiano. El radio total de la diana es de 11
unidades desde su origen.

• Círculo Central (Radio 1): 10 puntos.

• Círculo Medio (Radio 5): 5 puntos (si está fuera del central).

• Círculo Grande (Radio 10): 1 punto (si está fuera del medio).

Zonas de Penalización (restan 1 punto): Franjas de 1 unidad de grosor entre cada círculo.
Fuera de la Diana (distancia > 11 unidades): 0 puntos.

## Archivos de entrada

•juego.txt:

o Coordenadas x e y del centro de la diana.

o Nombre del Jugador 1 (linea de texto sin espacios) y cantidad de tiros, separados por un
espacio.

o Nombre del Jugador 2 (linea de texto sin espacios) y cantidad de tiros, separados por un
espacio.

```
juego.txt:
---------
0 0
prodegi_ 2
ronirck 3
```
• tiros.txt:

o Coordenadas X e Y de un tiro, separadas por un espacio.

o El total de líneas es la suma de los tiros de ambos jugadores. Los primeros tiros corresponden
al Jugador 1, los siguientes al Jugador 2.

```
tiros.txt
---------
5 1
-1 3
-5 -5
4 2
0 -3
```

## Archivo de salida

• puntuacion.txt:

o Nombre del Jugador 1 y su puntuación total.

o Nombre del Jugador 2 y su puntuación total.

o Mensaje indicando el ganador o si hubo un empate.
```
puntuacion.txt
--------------
prodegi_ 5
ronirck 11
Felicidades ronirck, has ganado.
```
