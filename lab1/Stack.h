#include <iostream>
#include <string>
#include "State.h"

using namespace std;

class Stack {
  public:
    State** stack; // almacenamos punteros de State
    int p; // indice del ultimo elemento agregado a la pila
    int N; // tamaño de la pila
    Stack(int N);
    void push(State* s);
    State* pop();
    
    bool find(State* s); // revisa si exite un estado con esas cantidades de agua
};