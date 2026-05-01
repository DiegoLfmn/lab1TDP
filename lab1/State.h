#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <string>

using namespace std;
/*
Esta clase corresponde al estado del problema de los bidones.
*/
struct BlockState {
    int id;
    int x;
    int y;
};
class State {
  public:
  // datos:variables de instancia
  BlockState* bloques; // arreglo de bloques
  int numBloques;
  int tiempo; // tiempo transcurrido para llegar a este estado



  string operacion;
  State* parent;
  float F; // costo total

  // constructor
  State(); // constructor vacio
  State(BlockState* bloques, int numBloques, int tiempo, string operacion, State* parent, float F); // constructor con parámetros
  
  
  ~State(); // destructor

  
  
  
  // métodos
  bool esFinal(); // si este estado es el estado final.
  void print(); // imprime el estado
  void printOperaciones(); // imprime la secuencia de operaciones desde el estado inicial hasta este estado.
};

#endif // STATE_H