#include "State.h"

/*
constructor vacio, para inicializar todo en valores por defecto.
*/
State::State() {
  bloques = nullptr;
  numBloques = 0;
  tiempo = 0;
  operacion = "";
  parent = nullptr;
  F = 0;
}

State::State(BlockState* bloques, int numBloques, int tiempo, string op, State* p, float f) {
  this->numBloques = numBloques;
  this->tiempo = tiempo;
  this->operacion = op;
  this->parent = p;
  this->F = f;

  this ->bloques = new BlockState[numBloques];
  for (int i = 0; i < numBloques; i++) {
    this->bloques[i] = bloques[i];
  }
}

State::~State(){
  if(bloques != nullptr){
    delete[] bloques;
  }

}
bool State::esFinal() {
  return numBloques == 0;
}

void State::print() {
  cout << "Tiempo: " << tiempo << " segundos" << endl;
  cout << "Operacion: " << operacion << endl;
  cout << "Bloques: " << endl;
  for (int i = 0; i < numBloques; i++) {
    cout << "Bloque " << bloques[i].id << ": (" << bloques[i].x << ", " << bloques[i].y << ")" << endl;
  }
}

void State::printOperaciones() {
  if (parent != nullptr) {
    parent->printOperaciones();
  }
  
  if(operacion != ""){
    cout << operacion << " ";
  }
}




