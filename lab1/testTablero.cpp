#include <iostream>
#include "Tablero.h"

using namespace std;

int main() {
    Tablero miTablero;
    
    cout << "Cargando archivo facil1_corregido.txt..." << endl;
    
    // Asegúrate de que el archivo facil1_corregido.txt esté en la misma carpeta!
    if (miTablero.cargarArchivo("facil1_corregido.txt")) {
        cout << "Archivo cargado con exito.\n" << endl;
        miTablero.printTablero();
    } else {
        cout << "ERROR: No se pudo abrir el archivo." << endl;
    }

    return 0;
}