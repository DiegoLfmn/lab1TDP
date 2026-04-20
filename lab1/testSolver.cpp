#include "Solver.h"

int main() {
  State* s = new State(0,0,"inicio",nullptr,0);

  Solver bot;
  State* final = bot.solve(s);

  if (final!=nullptr) {
    cout << "Solucion encontrada!" << endl;
    final->printOperaciones();
  } else {
    cout << "No se encontro solucion" << endl;
  }

}