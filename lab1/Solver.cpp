#include "Solver.h"
#include <iostream>
#include <cmath> // para abs()

using namespace std;

Solver::Solver(Tablero* tablero) {
  this->tablero = tablero;

  this->open = new Heap(100000); // capacidad inicial, se puede ajustar según el problema
  this->closed = new Tree();
  this->nodosExpandidos = 0;
}

Solver::~Solver() {
  delete open;
  delete closed;
}


int Solver::calcularHeuristica(State* s){
  int h_total = 0;

  // Revisamos cada bloque en el estado actual
  for (int i = 0; i < s->numBloques; i++){
    char miColor = ' ';
    // Encontramos el color del bloque actual
    for (int k = 0; k < tablero->numBlocks; k++){
      if (tablero->blockConfigs[k].id == s->bloques[i].id){
        miColor = tablero->blockConfigs[k].color;
        break;
      }
    }
    int min_dist = 999999; // distancia mínima a una salida del mismo color, inicializada a un valor grande
    bool tieneSalida = false; // bandera para saber si el bloque tiene una salida del mismo color 

    for(int j = 0; j < tablero->numExits; j++){
      if (tablero->exitConfigs[j].color == miColor){
        tieneSalida = true;

        // formula de distancia Manhattan |x1 -x2| + |y1 - y2|
        int dist = abs(s->bloques[i].x - tablero->exitConfigs[j].x) + abs(s->bloques[i].y - tablero->exitConfigs[j].y);

        if(dist < min_dist){
          min_dist = dist;
        }
      }
    }
    // si el bloque tiene una salida, sumamos su distancia a la total

    if (tieneSalida){
      h_total += min_dist;
    }


  }
  return h_total;
}



void Solver::solve(){
  State* inicial= tablero->generarEstadoInicial();
  int h_inicial = calcularHeuristica(inicial);
  inicial->f = inicial->tiempo + h_inicial;

  open->push(inicial);

  cout << "Iniciando busqueda A* " << endl;

  while (!open->isEmpty()){
    State* current = open->pop();

    if(current->numBloques == 0){
      cout << "Solucion encontrada!" << endl;
      cout << "pasos total" << current->tiempo << endl;
      cout << "nodos expandidos: " << nodosExpandidos << endl;

      cout << "Secuencia de operaciones: " << endl;
      current->printOperaciones();
      return;
    }

    closed->insert(current);
    nodosExpandidos++;

    int max_pasos = tablero->width > tablero->height ? tablero->width : tablero->height; // máximo pasos posibles en una dirección, para limitar la generación de vecinos

    // generar vecinos
    for (int i = 0; i < current->numBloques; i++){
      int b_id = current->bloques[i].id;

      for(int pasos = 1; pasos < max_pasos; pasos++){
        Operation* ops[4];
        ops[0] = new MoveUp(b_id, pasos, tablero);
        ops[1] = new MoveDown(b_id, pasos, tablero);
        ops[2] = new MoveLeft(b_id, pasos, tablero);
        ops[3] = new MoveRight(b_id, pasos, tablero);


        for(int op_idx = 0; op_idx < 4; op_idx++){
          if(ops[op_idx]->isAppl(current)){
            State* neighbor = ops[op_idx]->apply(current);

            if(!closed->contains(neighbor)){
              int h = calcularHeuristica(neighbor);
              neighbor->f = neighbor->tiempo + h; // f = g + h
              open->push(neighbor);
            } else {
              delete neighbor; // si el vecino ya fue explorado, liberamos la memoria
            }
          }
          delete ops[op_idx]; // liberamos la memoria de la operación después de usarla

        }
      }
    }
  }
  // si el heap se vacía sin encontrar una solución, entonces no hay solución
  cout << "No se encontró solución." << endl;
}


