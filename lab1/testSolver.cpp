#include <iostream>
#include "Tablero.h"
#include "Solver.h"

using namespace std;

int main() {
    Tablero miTablero;
    
    cout << "=== COLOR BLOCK JAM - SOLVER A* ===" << endl;
    
    // Cambia el nombre del archivo si quieres probar facil2 o medios
    if (!miTablero.cargarArchivo("facil1_corregido.txt")) {
        cout << "ERROR: No se pudo abrir el archivo de mapa." << endl;
        return 1;
    }

    Solver ia(&miTablero);
    ia.solve(); // ¡Que comience el juego!

    return 0;
}