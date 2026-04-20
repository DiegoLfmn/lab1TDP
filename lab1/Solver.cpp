#include "Solver.h"

Solver::Solver() {
  O[0]= new Vaciar5;
  O[1]= new Vaciar3;
  O[2]= new Llenar5;
  O[3]= new Llenar3;
  O[4]= new Trasv53;
  O[5]= new Trasv35;
}

State* Solver::solve(State* initial) {
  Heap open(1000);
  Stack all(1000);

  open.push(initial);
  all.push(initial);

  while (!open.isEmpty()) {
    State* current = open.pop();
    open.push(current);
    all.push(current);

    if (current->esFinal()) {
      return(current);
    }

    // no esta resuelto, procedo a generar los proximos estados a partir de las operaciones aplicables
    for(int k=0; k < N_OPER; k++ ) {
      if(O[k]->isAppl(current)) { // Si se puede aplicar esta operacion
        State* newState = O[k]->apply(current);
        if (!all.find(newState)) {
          open.push(newState);
        } else {
          delete newState; // si ya existe el estado generado, lo borro para no tener memory leaks
        }
      }
    }


  }
  return nullptr;
}