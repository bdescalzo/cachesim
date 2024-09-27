/*
CACHESIM
Autor: Beñat Descalzo Alcuaz
Descripción: El siguiente código implementa un simulador sencillo de memoria caché, con soporte para diferentes protocolos de lectura/escritura y tamaños para los datos. Proyecto creado para la asignatura "Arquitectura de Computadores en la UPV/EHU.
*/

#include <bits/stdc++.h>

using namespace std;

// VARIABLES GLOBALES
int wordSize; // Tamaño de palabra
int blockSize; // Tamaño de bloque
int setSize; // Tamaño de conjunto
bool rewrite; // 0 = FIFO, 1 = LRU
int cache[8][5];

int main() {
    
}