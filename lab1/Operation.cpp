#include "Operation.h"


Operation::Operation() : block_id(0), pasos(0), tablero(nullptr) {}

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

bool Operation::hayBloqueEnPosicion(State* current, int x, int y, int excluido_id) {
    for (int i = 0; i < current -> numBloques;i++){
      if(current -> bloques[i].id == excluido_id) continue; // ignorar el bloque que se está moviendo

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
      if (x >= bloque_x && x < bloque_x + bw && y >= bloque_y && y < bloque_y + bh) {
            int geoIndex = (y - bloque_y) * bw + (x - bloque_x);
            if (bgeom[geoIndex] == true) {
                return true; 
            }
        }



    }
    return false;
}



// logica para mover arruba

bool MoveUp::isAppl(State* current) {
    int idx = -1;
    for (int i = 0; i < current->numBloques; i++){
        if (current -> bloques[i].id == block_id){
            idx = i;
            break;
        }
    }
    if(idx == -1) return false; // bloque no encontrado

    int current_x = current -> bloques[idx].x;
    int current_y = current -> bloques[idx].y;
    int bw = 0, bh = 0;
    bool* bgeom = nullptr;

    for (int k = 0; k < tablero->numBlocks; k++) {
        if (tablero->blockConfigs[k].id == block_id) {
            bw = tablero->blockConfigs[k].width;
            bh = tablero->blockConfigs[k].height;
            bgeom = tablero->blockConfigs[k].geometry;
            break;
        }
    }

    for (int step = 1; step <= pasos; step++){
        int test_y = current_y - step;
        for(int dy = 0; dy < bh; dy++){
            for(int dx = 0; dx < bw; dx++){
                if(bgeom[dy * bw + dx]){
                    int check_x = current_x + dx;
                    int check_y = test_y + dy;
                    if(check_x < 0 || check_x >= tablero->width || check_y < 0 || check_y >= tablero->height) {
                        return false; // fuera de límites
                    }
                    if (tablero->paredes[check_y][check_x] == '#'){
                        return false; // hay una pared
                    }

                    if (hayBloqueEnPosicion(current,check_x,check_y,block_id)){
                        return false; // hay otro bloque
                    }


                }
            }
        }
        
    }
    return true; // si pasa todas las verificaciones, la operación es aplicable

}


State* MoveUp::apply(State* current) {
    BlockState* tempBloques = new BlockState[current->numBloques];
    for (int i = 0; i < current->numBloques; i++){
        tempBloques[i] = current->bloques[i];
    }

    for(int i = 0; i< current->numBloques; i++){
        if(tempBloques[i].id == block_id){
            tempBloques[i].y -= pasos; // mover hacia arriba disminuye la coordenada y
            break;
        }
    }
    string opStr = "U" + to_string(block_id) + "," + to_string(pasos);
    State* newState = new State(tempBloques, current->numBloques, current->tiempo + 1, opStr, current, 0);
    delete[] tempBloques; // liberar memoria temporal
    return newState;

}

// mover abajo
bool MoveDown::isAppl(State* current) {
    // Similar a MoveUp pero verificando hacia abajo
    int idx = -1;
    for (int i=0;i<current->numBloques;i++){
        if (current -> bloques[i].id == block_id){
            idx = i;
            break;
        }
    }
    if(idx == -1) return false; // bloque no encontrado

    int current_x = current -> bloques[idx].x;
    int current_y = current -> bloques[idx].y;
    int bw = 0, bh = 0;
    bool* bgeom = nullptr;

    for(int k =0; k<tablero->numBlocks; k++){
        if (tablero->blockConfigs[k].id == block_id){
            bw = tablero->blockConfigs[k].width;
            bh = tablero->blockConfigs[k].height;
            bgeom = tablero->blockConfigs[k].geometry;
            break;
        }
    }

    for (int step = 1; step <= pasos; step++){
        int test_y = current_y + step;
        for(int dy = 0; dy < bh; dy++){
            for(int dx = 0; dx < bw; dx++){
                if(bgeom[dy * bw + dx]){
                    int check_x = current_x + dx;
                    int check_y = test_y + dy;


                    if(check_x < 0 || check_x >= tablero->width || check_y < 0 || check_y >= tablero->height) {
                        return false; // fuera de límites
                    }
                    if (tablero->paredes[check_y][check_x] == '#'){
                        return false; // hay una pared
                    }

                    if (hayBloqueEnPosicion(current,check_x,check_y,block_id)){
                        return false; // hay otro bloque
                    }
                }
            }
        }
    }


    return true; 
}


State* MoveDown::apply(State* current) {
    // Similar a MoveUp pero moviendo hacia abajo
    BlockState* tempBloques = new BlockState[current->numBloques];
    for (int i = 0; i < current->numBloques; i++){
        tempBloques[i] = current->bloques[i];
    }

    for(int i = 0; i< current->numBloques; i++){
        if(tempBloques[i].id == block_id){
            tempBloques[i].y += pasos; // mover hacia abajo aumenta la coordenada y
            break;
        }
    }
    string opStr = "D" + to_string(block_id) + "," + to_string(pasos);
    State* newState = new State(tempBloques, current->numBloques, current->tiempo + 1, opStr, current, 0);
    delete[] tempBloques; // liberar memoria temporal
    return newState;
}



// verifica y aplica movimiento hacia la izquierda
bool MoveLeft::isAppl(State* current) {
    int idx = -1;
    for (int i=0;i<current->numBloques;i++){
        if (current -> bloques[i].id == block_id){
            idx = i;
            break;
        }
    }
    if(idx == -1) return false; // bloque no encontrado
    
    int current_x = current -> bloques[idx].x;
    int current_y = current -> bloques[idx].y;
    int bw = 0, bh = 0;
    bool* bgeom = nullptr;

    for(int k =0; k < tablero->numBlocks; k++){
        if(tablero->blockConfigs[k].id == block_id){
            bw = tablero->blockConfigs[k].width;
            bh = tablero->blockConfigs[k].height;
            bgeom = tablero->blockConfigs[k].geometry;
            break;
        }
    }

    for(int step =1; step <= pasos; step++){
        int test_x = current_x -step;
        for(int dy = 0; dy < bh; dy++){
            for(int dx = 0; dx < bw; dx++){
                if(bgeom[dy * bw + dx]){
                    int check_x = test_x + dx;
                    int check_y = current_y + dy;

                    if(check_x < 0 || check_x >= tablero->width || check_y < 0 || check_y >= tablero->height) {
                        return false; // fuera de límites
                    }
                    if (tablero->paredes[check_y][check_x] == '#'){
                        return false; // hay una pared
                    }

                    if (hayBloqueEnPosicion(current,check_x,check_y,block_id)){
                        return false; // hay otro bloque
                    }
                }
            }
        }
    }
    return true; 
}


State* MoveLeft::apply(State* current) {
    BlockState* tempBloques = new BlockState[current->numBloques];
    for (int i = 0; i < current->numBloques; i++){
        tempBloques[i] = current->bloques[i];
    }

    for(int i = 0; i< current->numBloques; i++){
        if(tempBloques[i].id == block_id){
            tempBloques[i].x -= pasos; // mover hacia izquierda disminuye la coordenada x
            break;
        }
    }
    string opStr = "L" + to_string(block_id) + "," + to_string(pasos);
    State* newState = new State(tempBloques, current->numBloques, current->tiempo + 1, opStr, current, 0);
    delete[] tempBloques; // liberar memoria temporal
    return newState;
}


// verifica y aplica movimiento hacia la derecha
bool MoveRight::isAppl(State* current) {
    int idx = -1;
    for(int i=0;i<current->numBloques;i++){
        if (current -> bloques[i].id == block_id){
            idx = i;
            break;
        }
    }
    if(idx == -1) return false; // bloque no encontrado

    int current_x = current -> bloques[idx].x;
    int current_y = current -> bloques[idx].y;
    int bw = 0, bh = 0;
    bool* bgeom = nullptr;

    for(int k =0; k < tablero->numBlocks; k++){
        if(tablero->blockConfigs[k].id == block_id){
            bw = tablero->blockConfigs[k].width;
            bh = tablero->blockConfigs[k].height;
            bgeom = tablero->blockConfigs[k].geometry;
            break;
        }
    }


    for(int step =1; step <= pasos; step++){
        int test_x = current_x + step;
        for(int dy = 0; dy < bh; dy++){
            for(int dx = 0; dx < bw; dx++){
                if(bgeom[dy * bw + dx]){
                    int check_x = test_x + dx;
                    int check_y = current_y + dy;

                    if(check_x < 0 || check_x >= tablero->width || check_y < 0 || check_y >= tablero->height) {
                        return false; // fuera de límites
                    }
                    if (tablero->paredes[check_y][check_x] == '#'){
                        return false; // hay una pared
                    }

                    if (hayBloqueEnPosicion(current,check_x,check_y,block_id)){
                        return false; // hay otro bloque
                    }
                }
            }
        }
    }
    return true;
}


State* MoveRight::apply(State* current) {
    BlockState* tempBloques = new BlockState[current->numBloques];
    for (int i = 0; i < current->numBloques; i++){
        tempBloques[i] = current->bloques[i];
    }

    for(int i = 0; i< current->numBloques; i++){
        if(tempBloques[i].id == block_id){
            tempBloques[i].x += pasos; // mover hacia derecha aumenta la coordenada x
            break;
        }
    }
    string opStr = "R" + to_string(block_id) + "," + to_string(pasos);
    State* newState = new State(tempBloques, current->numBloques, current->tiempo + 1, opStr, current, 0);
    delete[] tempBloques; // liberar memoria temporal
    return newState;
}
