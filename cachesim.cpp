/*
CACHESIM
Autor: Beñat Descalzo Alcuaz
Descripción: El siguiente código implementa un simulador sencillo de memoria caché, con soporte para diferentes protocolos de lectura/escritura y tamaños para los datos. Proyecto creado para la asignatura "Arquitectura de Computadores" en la UPV/EHU.
*/

#include <bits/stdc++.h>

using namespace std;

// VARIABLES GLOBALES
int wordSize; // Tamaño de palabra
int blockSize; // Tamaño de bloque
int setSize; // Tamaño de conjunto
int rewrite; // 0 = FIFO, 1 = LRU

// OCUPADO (0/1) - DIRTY (0/1) - TAG - REEMP - BLOQUE
int cache[8][5];

int direccion;
char op; // w=write, r=read

// Resetea la matriz de la cache, ajustando todos sus valores a 0
void setCacheMatrix() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 5; j++) {
            cache[i][j] = 0;
        }
    }
}
// Función auxiliar para la configuración inicial de la memoria caché
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
    cout << "- Bloque de " << blockSize << " bytes.\n";
    cout << "- Conjunto de " << setSize << " bloques.\n";
    cout << "- Política de reemplazo: " << (rewrite==0 ? "FIFO" : "LRU") << "\n\n";
}

// Función auxiliar para la selección de operación del usuario
void chooseOp() {
    cout << "Introduce una dirección de memoria (al byte) en formato decimal: ";
    cin >> direccion;

    cout << "Elige entre [w]rite o [r]ead: ";
    cin >> op;
    while (op!='w' && op!='r') {
        cout << "Opción incorrecta.\n";
        cout << "Elige entre [w]rite o [r]ead: ";
        cin >> op;
    }
}

// 
// Comprueba si en la dirección actual se encuentra el dato en uso.
bool checkTag(int word) {
    int palabra_mp = word / wordSize;
    int bloque_mp = palabra_mp / (blockSize/wordSize);

    // CASO 1: Correspondencia directa. Tenemos que calcular el tag correspondiente al bloque de la dirección.
    if (setSize==1) {
        int tag = bloque_mp / (8/blockSize);
        return cache[word][tag];
    }

}

// Calcula el tag de la dirección, en función del tamaño de conjunto
int getTag() {
    int bloque_mp = direccion / (blockSize);
    cout << "bloque " << bloque_mp << '\n';
    // Directa
    if (setSize==1) {
        return bloque_mp % 8;
    }

    // Totalmente asociativa
    else if (setSize==8) {
        return bloque_mp;
    }

    else {
        return bloque_mp / (8/setSize);
    }
}

void performRead() {
    int tag = getTag();

    cout << "El tag de " << direccion << " es " << tag << '\n';
}

int main() {
    // Ajustamos los valores iniciales del programa
    setCacheMatrix();
    setup();

    // Elección de operación
    while (true) {
        chooseOp();
        if (op=='r') {
            performRead();
        }
    }
}