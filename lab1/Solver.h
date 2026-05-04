#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <string>
#include "Tree.h"
#include "Heap.h"
#include "State.h"
#include "Operation.h"
#include "Tablero.h"

using namespace std;


class Solver {
private:
  Tablero* tablero;
  Heap* open; // estdos por explorar
  Tree* closed; // estados ya explorados, para evitar ciclos y no volver a explorar los mismos estados
  int nodosExpandidos;
  int calcularHeuristica(State* s);
public: 
  Solver(Tablero* tablero);
  ~Solver();

  void solve();
};

#endif