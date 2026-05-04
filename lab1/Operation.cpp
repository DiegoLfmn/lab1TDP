#include "Operation.h"




Operation::Operation(int b_id, int pasos, Tablero* tablero){
    this->block_id = b_id;
    this->pasos = pasos;
    this->tablero = tablero;
}

Operation::~Operation() {}

MoveUp::MoveUp(int b_id, int pasos, Tablero* tablero) : Operation(b_id, pasos, tablero) {}
MoveDown::MoveDown(int b_id, int pasos, Tablero* tablero) : Operation(b_id, pasos, tablero) {}
MoveLeft::MoveLeft(int b_id, int pasos, Tablero* tablero) : Operation(b_id, pasos, tablero) {}
MoveRight::MoveRight(int b_id, int pasos, Tablero* tablero) : Operation(b_id, pasos, tablero) {}

/*bool Operation::isAppl(State* current) {
    // Implementación genérica, puede ser sobreescrita por las clases derivadas
    return true;
}


bool Operation::isAppl(State* s) {
  return false; 
}

State* Operation::apply(State* s) {
  return nullptr;
}
*/

// revisamos si hay un bloque en la posición dada, ignorando el bloque que se está moviendo (excluido_id)

bool Operation::hayBloqueEnPosicion(State* current, int x, int y, int excluido_id) {
    for (int i = 0; i < current -> numBloques;i++){
        if(current -> bloques[i].id == excluido_id) {
            continue; // ignorar el bloque que se está moviendo
        }

        int bloque_x = current -> bloques[i].x;
        int bloque_y = current -> bloques[i].y;
        int bw = 0 , bh = 0; // ancho y alto del bloque

        bool* bgeom = nullptr; // geometría del bloque

        for (int k = 0; k < tablero->numBlocks; k++) {
            if (tablero->blockConfigs[k].id == current->bloques[i].id) {
                bw = tablero->blockConfigs[k].width;
                bh = tablero->blockConfigs[k].height;
                bgeom = tablero->blockConfigs[k].geometry;
                break;
            }
        }
        /*
        if (x >= bloque_x && x < bloque_x + bw && y >= bloque_y && y < bloque_y + bh) {
            int geoIndex = (y - bloque_y) * bw + (x - bloque_x);
            if (bgeom[geoIndex] == true) {
                return true; 
            }
        
        }
        */
        if(x >= bloque_x && x < bloque_x + bw && y >= bloque_y && y < bloque_y + bh){
            if(bgeom[(y - bloque_y) * bw + (x - bloque_x)]){
                return true;
            }
        }


    }
    return false;
}

bool Operation::esMiSalida(int x, int y, char miColor){
    for(int i = 0; i < tablero->numExits; i++){
        if(tablero->exitConfigs[i].color == miColor){
            // vemos si la posición de salida coincide con la posición dada
            if(tablero->exitConfigs[i].x == x && tablero->exitConfigs[i].y == y){
                return true;
            }
            // también consideramos la orientación de la salida para bloques que ocupan más de una celda
            if(tablero->exitConfigs[i].orientation == 'V' && tablero->exitConfigs[i].x == x && y >= tablero->exitConfigs[i].li && y <= tablero->exitConfigs[i].lf){
                return true;
            }
            if(tablero->exitConfigs[i].orientation == 'H' && tablero->exitConfigs[i].y == y && x >= tablero->exitConfigs[i].li && x <= tablero->exitConfigs[i].lf){
                return true;
            }
        }
    }
    return false;
}

bool Operation::seEscapa(int new_x, int new_y, int b_id){
    int bw = 0, bh = 0;
    bool *bgeom = nullptr;
    char miColor = ' ';

    for(int k= 0 ; k < tablero->numBlocks; k++){
        if (tablero->blockConfigs[k].id == b_id){
            bw = tablero->blockConfigs[k].width;
            bh = tablero->blockConfigs[k].height;
            bgeom = tablero->blockConfigs[k].geometry;
            miColor = tablero->blockConfigs[k].color;
            break;
        }
    }

    for(int dy = 0; dy < bh; dy++){
        for(int dx = 0; dx < bw; dx++){
            if(bgeom[dy * bw + dx]){
                int check_x = new_x + dx;
                int check_y = new_y + dy;
                
                if(check_x < 0 || check_x >= tablero->width || check_y < 0 || check_y >= tablero->height){
                    return true; // se escapa del tablero
                }
                if(esMiSalida(check_x, check_y, miColor)){
                    return true; // se escapa por su salida
                }
            }
        }
    }
    return false;    
}



// logica para mover arruba

bool MoveUp::isAppl(State* current) {
    int idx = -1; char miColor = ' ';
    for (int i = 0; i < current->numBloques; i++) { if (current->bloques[i].id == block_id) { idx = i; break; } }
    if (idx == -1) return false;

    int curr_x = current->bloques[idx].x, curr_y = current->bloques[idx].y;
    int bw = 0, bh = 0; bool* bgeom = nullptr;
    for (int k = 0; k < tablero->numBlocks; k++) {
        if (tablero->blockConfigs[k].id == block_id) {
            bw = tablero->blockConfigs[k].width; bh = tablero->blockConfigs[k].height;
            bgeom = tablero->blockConfigs[k].geometry; miColor = tablero->blockConfigs[k].color; break;
        }
    }

    bool is_escaping = false;
    for (int step = 1; step <= pasos; step++) {
        int test_y = curr_y - step; 
        for (int dy = 0; dy < bh; dy++) {
            for (int dx = 0; dx < bw; dx++) {
                if (bgeom[dy * bw + dx]) {
                    int check_x = curr_x + dx, check_y = test_y + dy;
                    if (check_x < 0 || check_x >= tablero->width || check_y < 0 || check_y >= tablero->height) {
                        if (is_escaping) continue; else return false;
                    }
                    if (tablero->paredes[check_y][check_x] == '#') {
                        if (esMiSalida(check_x, check_y, miColor)) is_escaping = true;
                        else return false;
                    } else if (hayBloqueEnPosicion(current, check_x, check_y, block_id)) return false;
                }
            }
        }
    }
    return true;
}


State* MoveUp::apply(State* current) {
    int idx = -1;
    for (int i = 0; i < current->numBloques; i++) { if (current->bloques[i].id == block_id) { idx = i; break; } }
    
    bool escapo = seEscapa(current->bloques[idx].x, current->bloques[idx].y - pasos, block_id);
    int new_numBloques;
    if(escapo == true){
        // Si el bloque se escapa, el nuevo número de bloques es uno menos que el actual
        new_numBloques = current->numBloques - 1;
    } else {
        // Si el bloque no se escapa, el número de bloques permanece igual
        new_numBloques = current->numBloques;
    }
    // int new_numBloques = escapo ? current->numBloques - 1 : current->numBloques;
    
    BlockState* tempBloques = nullptr;
    if (new_numBloques > 0) tempBloques = new BlockState[new_numBloques];

    int c = 0;
    for (int i = 0; i < current->numBloques; i++) {
        if (current->bloques[i].id == block_id) {
            if (escapo) continue; // Si escapo, no lo agregamos al nuevo estado!
            tempBloques[c] = current->bloques[i]; tempBloques[c].y -= pasos; c++;
        } else {
            tempBloques[c] = current->bloques[i]; c++;
        }
    }

    string opStr = "U" + to_string(block_id) + "," + to_string(pasos);
    State* newState = new State(tempBloques, new_numBloques, current->tiempo + 1, opStr, current, 0);
    if (tempBloques != nullptr) delete[] tempBloques;
    return newState;
}

// mover abajo
bool MoveDown::isAppl(State* current) {
    // Similar a MoveUp pero verificando hacia abajo
    int idx = -1; char miColor = ' ';
    for (int i = 0; i < current->numBloques; i++) { if (current->bloques[i].id == block_id) { idx = i; break; } }
    if (idx == -1) return false;

    int curr_x = current->bloques[idx].x, curr_y = current->bloques[idx].y;
    int bw = 0, bh = 0; bool* bgeom = nullptr;
    for (int k = 0; k < tablero->numBlocks; k++) {
        if (tablero->blockConfigs[k].id == block_id) {
            bw = tablero->blockConfigs[k].width; bh = tablero->blockConfigs[k].height;
            bgeom = tablero->blockConfigs[k].geometry; miColor = tablero->blockConfigs[k].color; break;
        }
    }

    bool is_escaping = false;
    for (int step = 1; step <= pasos; step++) {
        int test_y = curr_y + step; 
        for (int dy = 0; dy < bh; dy++) {
            for (int dx = 0; dx < bw; dx++) {
                if (bgeom[dy * bw + dx]) {
                    int check_x = curr_x + dx, check_y = test_y + dy;
                    if (check_x < 0 || check_x >= tablero->width || check_y < 0 || check_y >= tablero->height) {
                        if (is_escaping) continue; else return false;
                    }
                    if (tablero->paredes[check_y][check_x] == '#') {
                        if (esMiSalida(check_x, check_y, miColor)) is_escaping = true;
                        else return false;
                    } else if (hayBloqueEnPosicion(current, check_x, check_y, block_id)) return false;
                }
            }
        }
    }
    return true; 
}


State* MoveDown::apply(State* current) {
    // Similar a MoveUp pero moviendo hacia abajo
    int idx = -1;
    for (int i = 0; i < current->numBloques; i++) { if (current->bloques[i].id == block_id) { idx = i; break; } }
    
    bool escapo = seEscapa(current->bloques[idx].x, current->bloques[idx].y + pasos, block_id);
    int new_numBloques;
    if(escapo == true){
        // Si el bloque se escapa, el nuevo número de bloques es uno menos que el actual
        new_numBloques = current->numBloques - 1;
    } else {
        // Si el bloque no se escapa, el número de bloques permanece igual
        new_numBloques = current->numBloques;
    }
    // int new_numBloques = escapo ? current->numBloques - 1 : current->numBloques;
    
    BlockState* tempBloques = nullptr;
    if (new_numBloques > 0) tempBloques = new BlockState[new_numBloques];

    int c = 0;
    for (int i = 0; i < current->numBloques; i++) {
        if (current->bloques[i].id == block_id) {
            if (escapo) continue; 
            tempBloques[c] = current->bloques[i]; tempBloques[c].y += pasos; c++;
        } else {
            tempBloques[c] = current->bloques[i]; c++;
        }
    }

    string opStr = "D" + to_string(block_id) + "," + to_string(pasos);
    State* newState = new State(tempBloques, new_numBloques, current->tiempo + 1, opStr, current, 0);
    if (tempBloques != nullptr) delete[] tempBloques;
    return newState;
}



// verifica y aplica movimiento hacia la izquierda
bool MoveLeft::isAppl(State* current) {
    int idx = -1; char miColor = ' ';
    for (int i = 0; i < current->numBloques; i++) { if (current->bloques[i].id == block_id) { idx = i; break; } }
    if (idx == -1) return false;

    int curr_x = current->bloques[idx].x, curr_y = current->bloques[idx].y;
    int bw = 0, bh = 0; bool* bgeom = nullptr;
    for (int k = 0; k < tablero->numBlocks; k++) {
        if (tablero->blockConfigs[k].id == block_id) {
            bw = tablero->blockConfigs[k].width; bh = tablero->blockConfigs[k].height;
            bgeom = tablero->blockConfigs[k].geometry; miColor = tablero->blockConfigs[k].color; break;
        }
    }

    bool is_escaping = false;
    for (int step = 1; step <= pasos; step++) {
        int test_x = curr_x - step; 
        for (int dy = 0; dy < bh; dy++) {
            for (int dx = 0; dx < bw; dx++) {
                if (bgeom[dy * bw + dx]) {
                    int check_x = test_x + dx, check_y = curr_y + dy;
                    if (check_x < 0 || check_x >= tablero->width || check_y < 0 || check_y >= tablero->height) {
                        if (is_escaping) continue; else return false;
                    }
                    if (tablero->paredes[check_y][check_x] == '#') {
                        if (esMiSalida(check_x, check_y, miColor)) is_escaping = true;
                        else return false;
                    } else if (hayBloqueEnPosicion(current, check_x, check_y, block_id)) return false;
                }
            }
        }
    }
    return true; 
}


State* MoveLeft::apply(State* current) {
    int idx = -1;
    for (int i = 0; i < current->numBloques; i++) { if (current->bloques[i].id == block_id) { idx = i; break; } }
    
    bool escapo = seEscapa(current->bloques[idx].x - pasos, current->bloques[idx].y, block_id);
    int new_numBloques;
    if(escapo == true){
        // Si el bloque se escapa, el nuevo número de bloques es uno menos que el actual
        new_numBloques = current->numBloques - 1;
    } else {
        // Si el bloque no se escapa, el número de bloques permanece igual
        new_numBloques = current->numBloques;
    }
    //int new_numBloques = escapo ? current->numBloques - 1 : current->numBloques;
    
    BlockState* tempBloques = nullptr;
    if (new_numBloques > 0) tempBloques = new BlockState[new_numBloques];

    int c = 0;
    for (int i = 0; i < current->numBloques; i++) {
        if (current->bloques[i].id == block_id) {
            if (escapo) continue; 
            tempBloques[c] = current->bloques[i]; tempBloques[c].x -= pasos; c++;
        } else {
            tempBloques[c] = current->bloques[i]; c++;
        }
    }

    string opStr = "L" + to_string(block_id) + "," + to_string(pasos);
    State* newState = new State(tempBloques, new_numBloques, current->tiempo + 1, opStr, current, 0);
    if (tempBloques != nullptr) delete[] tempBloques;
    return newState;
}


// verifica y aplica movimiento hacia la derecha
bool MoveRight::isAppl(State* current) {
    int idx = -1; char miColor = ' ';
    for (int i = 0; i < current->numBloques; i++) { if (current->bloques[i].id == block_id) { idx = i; break; } }
    if (idx == -1) return false;

    int curr_x = current->bloques[idx].x, curr_y = current->bloques[idx].y;
    int bw = 0, bh = 0; bool* bgeom = nullptr;
    for (int k = 0; k < tablero->numBlocks; k++) {
        if (tablero->blockConfigs[k].id == block_id) {
            bw = tablero->blockConfigs[k].width; bh = tablero->blockConfigs[k].height;
            bgeom = tablero->blockConfigs[k].geometry; miColor = tablero->blockConfigs[k].color; break;
        }
    }

    bool is_escaping = false;
    for (int step = 1; step <= pasos; step++) {
        int test_x = curr_x + step; 
        for (int dy = 0; dy < bh; dy++) {
            for (int dx = 0; dx < bw; dx++) {
                if (bgeom[dy * bw + dx]) {
                    int check_x = test_x + dx, check_y = curr_y + dy;
                    if (check_x < 0 || check_x >= tablero->width || check_y < 0 || check_y >= tablero->height) {
                        if (is_escaping) continue; else return false;
                    }
                    if (tablero->paredes[check_y][check_x] == '#') {
                        if (esMiSalida(check_x, check_y, miColor)) is_escaping = true;
                        else return false;
                    } else if (hayBloqueEnPosicion(current, check_x, check_y, block_id)) return false;
                }
            }
        }
    }
    return true;
}


State* MoveRight::apply(State* current) {
    int idx = -1;
    for (int i = 0; i < current->numBloques; i++) { if (current->bloques[i].id == block_id) { idx = i; break; } }
    
    bool escapo = seEscapa(current->bloques[idx].x + pasos, current->bloques[idx].y, block_id);
    int new_numBloques;
    if(escapo == true){
        // Si el bloque se escapa, el nuevo número de bloques es uno menos que el actual
        new_numBloques = current->numBloques - 1;
    } else {
        // Si el bloque no se escapa, el número de bloques permanece igual
        new_numBloques = current->numBloques;
    }
    
    //int new_numBloques = escapo ? current->numBloques - 1 : current->numBloques;
    
    BlockState* tempBloques = nullptr;
    if (new_numBloques > 0) tempBloques = new BlockState[new_numBloques];

    int c = 0;
    for (int i = 0; i < current->numBloques; i++) {
        if (current->bloques[i].id == block_id) {
            if (escapo) continue; 
            tempBloques[c] = current->bloques[i]; tempBloques[c].x += pasos; c++;
        } else {
            tempBloques[c] = current->bloques[i]; c++;
        }
    }

    string opStr = "R" + to_string(block_id) + "," + to_string(pasos);
    State* newState = new State(tempBloques, new_numBloques, current->tiempo + 1, opStr, current, 0);
    if (tempBloques != nullptr) delete[] tempBloques;
    return newState;
}
