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

// Calcula la dirección de MC en la que tenemos que leer o escribir.
int findDirection() {
    int palabra_mp = direccion / wordSize;
    int bloque_mp = direccion / blockSize;
    int dir_salida = -1; // Dirección a devolver

    cout << "- Dirección: " << direccion << endl;
    cout << "- Palabra: " << palabra_mp << ". Bloque: " << bloque_mp << '\n';

    // CASO 1: Correspondencia directa. Tenemos que calcular el bloque correspondiente al bloque de la dirección.
    if (setSize==1) {
        cout << "Haii :3";
        dir_salida = bloque_mp % (8/setSize);
    }

    // Caso 2: Totalmente asociativa. Tenemos que buscar si existe el elemento en el conjunto, si no el primer sitio libre y, de no haberlo, devolver el que corresponda según la política FIFO o LRU.
    else if (setSize==8) {
        // Primera pasada: Buscar el elemento.
        for (int i = 0; i <=7; i+=blockSize/wordSize) {
            if (cache[i][2]==direccion) {
                dir_salida = i;
                break;
            }
        }

        if (dir_salida==-1) {
            // Segunda pasada: Buscar un sitio libre.
            for (int i = 0; i <=7; i+=blockSize/wordSize) {
                if (cache[i][0]==0) {
                    dir_salida = i;
                    break;
                }
            }
        }

        // Tercera pasada: Ejecutar el protocolo de reemplazo. Basta con buscar el número de reemplazo más alto, pues en FIFO representa la vejez y en LRU el desuso.
        if (dir_salida == -1) {
            int element = 0;
            int element_age = -1;
            for (int i = 0; i <=7; i++) {
                if (cache[i][3] > element_age) {
                    element = i;
                    element_age = cache[i][3];
                }
            }
            dir_salida = element;
        }
    }

    // Caso 3: Asociativa por conjuntos. Entramos al conjunto que nos corresponde, y repetimos los pasos de la totalmente asociativa.
    else {
        // Primero calculamos el conjunto en el que nos corresponde estar
        int cj_cache = bloque_mp % (8/setSize);

        // Buscamos el elemento en el conjunto
        cout << "Conjunto " << cj_cache << '\n';
        for (int j = cj_cache * setSize; j<cj_cache*setSize+setSize; j++) {
            cout << j << endl;
            if (cache[j][2]==direccion) {
                dir_salida = j;
                break;
            }
        }
        if (dir_salida==-1){
            // Buscamos un hueco libre en el conjunto
            for (int j = cj_cache * setSize; j<cj_cache*setSize+setSize; j++) {
                cout << j << endl;
                if (cache[j][0]==0) {
                    dir_salida = j;
                    break;
                }
            }
      }

        // Ejecutamos el protocolo de reemplazo
        if (dir_salida==-1) {
            int element = 0;
            int element_age = -1;
            for (int j = cj_cache*setSize; j <cj_cache*setSize+setSize; j++) {
                if (cache[j][3] > element_age) {
                    element = j;
                    element_age = cache[j][3];
                }
            }
            dir_salida = element;
        }
    }
    return dir_salida;


}

void performRead() {
    int tag = getTag();

    cout << "El tag de " << direccion << " es " << tag << '\n';

    int dirObjetivo = findDirection();
    cout << "Va en la " << dirObjetivo << '\n';
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