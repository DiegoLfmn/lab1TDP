#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <string>

using namespace std;
/*
Esta clase corresponde al estado del problema de los bidones.
*/

class State {
  public:
  // datos:variables de instancia
  int B5;
  int B3;
  string operacion;
  State* parent;
  float F; // costo total
  // constructor
  State(); // constructor vacio
  State(int B5, 
        int B3, 
        string op, 
        State* p,
        float f); // constructor con parámetros
  // métodos
  bool esFinal(); // si este estado es el estado final.
  void print(); // imprime el estado
  void printOperaciones(); // imprime la secuencia de operaciones desde el estado inicial hasta este estado.
};

#endif // STATE_H