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
int rewrite; // 0 = FIFO, 1 = LRU
int cache[8][5];

// Configuración inicial de la memoria caché
void setup() {


    cout << "Introduce el tamaño de palabra en bytes (4/8): ";
    cin >> wordSize;
    while (wordSize!=4 && wordSize!=8) {
        cout << "Error: El valor introducido es incorrecto.\n";
        cout << "Introduce el tamaño de palabra en bytes (4/8): ";
        cin >> wordSize;
    }

    cout << "\nIntroduce el tamaño de bloque en bytes (32/64): ";
    cin >> blockSize;
    while (blockSize!=32 && blockSize!=64) {
        cout << "Error: El valor introducido es incorrecto.\n";
        cout << "Introduce el tamaño de bloque en bytes (32/64): ";
        cin >> blockSize;
    }

    cout << "\nIntroduce el tamaño de conjunto en bloques (1/2/4/8). Recuerda que '1' es equivalente a correspondencia directa, y '8' a totalmente asociativa: ";
    cin >> setSize;
    while (setSize!=1 && setSize!=2 && setSize!=4 && setSize!=8) {
        cout << "Error: El valor introducido es incorrecto.\n";
        cout << "Introduce el tamaño de conjunto (1/2/4/8): ";
        cin >> setSize;
    }

    cout << "\nIntroduce la política de reemplazo deseada, introduciendo el número correspondiente (0=FIFO, 1=LRU): ";
    cin >> rewrite;
    while (rewrite!=0 && rewrite!=1) {
        cout << "Error: El valor introducido es incorrecto.\n";
      cout << "Introduce la política de reemplazo deseada, introduciendo el número correspondiente (0=FIFO, 1=LRU): ";
      cin >> rewrite;
    }

    cout << "CONFIGURACIÓN SELECCIONADA: \n";
    cout << "- Palabra de " << wordSize << " bytes.\n";
    cout << "- Bloque de " << blockSize << " palabras.\n";
    cout << "- Conjunto de " << setSize << " bloques.\n";
    cout << "- Política de reemplazo: " << (rewrite==0 ? "FIFO" : "LRU") << '\n';


}
int main() {
    setup();
}