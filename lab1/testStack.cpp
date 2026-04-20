#include "Stack.h"

int main() {
  Stack s(2); // creamos una pila con capacidad inicial de 2

  State* e;
  for(int i=0;i<100;i++) {
    e = new State(i, i+1, "operacion " + to_string(i), nullptr, 0);
    s.push(e);
  }

  for(int i=0;i<100;i++) {
    e = s.pop();
    if (e != nullptr) {
      e->print(); 
      delete e; // liberamos la memoria del estado
    } else {
      cout << "Pila vacia" << endl;
    }
  }

}