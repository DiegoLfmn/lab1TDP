#include <iostream>
#include "Tablero.h"
#include "State.h"
#include "Operation.h"

using namespace std;

int main() {
    Tablero miTablero;
    
    cout << "Cargando archivo facil1_corregido.txt..." << endl;
    if (!miTablero.cargarArchivo("facil1_corregido.txt")) {
        cout << "ERROR: No se pudo abrir el archivo." << endl;
        return 1;
    }

    // 1. Generamos el estado inicial
    State* estadoActual = miTablero.generarEstadoInicial();
    cout << "\n=== ESTADO INICIAL ===" << endl;
    estadoActual->print();

    // 2. PRUEBA DE COLISION (Debería dar error por chocar con el bloque 4)
    cout << "\n>>> INTENTANDO: Mover Bloque 1 hacia ABAJO (1 paso)..." << endl;
    MoveDown prueba1(1, 1, &miTablero);
    
    if (prueba1.isAppl(estadoActual)) {
        cout << "[EXITO] Movimiento legal. Aplicando..." << endl;
        State* estadoNuevo = prueba1.apply(estadoActual);
        delete estadoActual; 
        estadoActual = estadoNuevo;
    } else {
        cout << "[ERROR] Movimiento Ilegal! Chocaste con una pared o bloque." << endl;
    }

    // 3. PRUEBA DE ESCAPE HACIA UNA SALIDA
    // Vamos a forzar un movimiento largo hacia la derecha para probar el escáner de puertas
    cout << "\n>>> INTENTANDO: Mover Bloque 1 hacia DERECHA (8 pasos)..." << endl;
    MoveRight pruebaEscape(1, 8, &miTablero);

    if (pruebaEscape.isAppl(estadoActual)) {
        cout << "[EXITO] Movimiento legal o escape detectado. Aplicando..." << endl;
        State* estadoNuevo = pruebaEscape.apply(estadoActual);
        
        cout << "\n=== NUEVO ESTADO ===" << endl;
        estadoNuevo->print(); 
        
        delete estadoActual;
        estadoActual = estadoNuevo;
    } else {
        cout << "[ERROR] Movimiento Ilegal! (La puerta no es del mismo color o hay bloques bloqueando)." << endl;
    }

    // Limpiamos la memoria al final
    delete estadoActual;
    return 0;
}