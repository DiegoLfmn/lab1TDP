#include "Stack.h"

Stack::Stack(int N) {
  stack = new State*[N]; // reservamos memoria para N punteros de State
  p=-1; // convencion de stack vacio
  this->N=N;
}

void Stack::push(State* s) {
  if (p>=N-1) {
    State** newStack = new State*[2*N]; 
    for(int i=0; i<N; i++) {
      newStack[i] = stack[i];
    }
    delete[] stack; // liberamos la memoria de la pila anterior
    stack = newStack;
    N = 2*N;
  }
  p++;
  stack[p] = s;
}

State* Stack::pop() {
  if (p==-1) { // si esta vacio
    return nullptr;
  }
  p--;
  return stack[p+1];
}

bool Stack::find(State* s) {
  for(int i=0; i<=p; i++) {
    if (stack[i]->B5 == s->B5 && 
        stack[i]->B3 == s->B3) {
      return true;
    }
  }
  return false;
}