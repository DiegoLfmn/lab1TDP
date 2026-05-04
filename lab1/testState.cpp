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

    // 2. PRUEBA: Mover el Bloque 1 hacia Abajo por 1 paso
    cout << "\n>>> INTENTANDO: Mover Bloque 1 hacia ABAJO (1 paso)..." << endl;
    MoveDown prueba1(1, 1, &miTablero); // ID=1, Pasos=1, Tablero

    if (prueba1.isAppl(estadoActual)) {
        cout << "[EXITO] Movimiento legal. Aplicando..." << endl;
        State* estadoNuevo = prueba1.apply(estadoActual);
        estadoNuevo->print();
        
        // Lo guardamos como nuestro nuevo estado actual para la siguiente prueba
        delete estadoActual; 
        estadoActual = estadoNuevo;
    } else {
        cout << "[ERROR] Movimiento Ilegal! Chocaste con una pared o bloque." << endl;
    }

    // 3. PRUEBA: Mover el Bloque 1 hacia Arriba por 5 pasos (Para forzar un choque con la pared)
    cout << "\n>>> INTENTANDO: Mover Bloque 1 hacia ARRIBA (5 pasos)..." << endl;
    MoveUp prueba2(1, 5, &miTablero);

    if (prueba2.isAppl(estadoActual)) {
        cout << "[EXITO] Movimiento legal. Aplicando..." << endl;
        State* estadoNuevo = prueba2.apply(estadoActual);
        estadoNuevo->print();
        delete estadoActual;
        estadoActual = estadoNuevo;
    } else {
        cout << "[ERROR] Movimiento Ilegal! Chocaste con una pared o bloque." << endl;
    }

    // Limpiamos la memoria al final
    delete estadoActual;
    return 0;
}