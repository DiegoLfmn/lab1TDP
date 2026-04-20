#include "State.h"

/*
constructor vacio, asigna -1 a ambos bidones para indicar que no se han inicializado.
*/
State::State() {
  B5 = -1;
  B3 = -1;
  operacion = "";
  parent = nullptr;
}

State::State(int B5, 
          int B3,
          string op, 
          State* p,
          float f) {
  this->B5 = B5;
  this->B3 = B3;
  this->operacion = op;
  this->parent = p;
  this->F = f;
}

bool State::esFinal() {
  // el estado final es aquel en el que el bidón de 5 litros tiene exactamente 4 litros.
  return B5 == 4;
}

void State::print() {
  cout << "B5: " << B5 << " B3: " << B3 << "operacion: " << operacion << " F: " << F << endl;
}

void State::printOperaciones() {
  if (parent != nullptr) {
    parent->printOperaciones();
  }
  print();
}




