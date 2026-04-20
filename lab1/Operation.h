#ifndef OPERATION_H
#define OPERATION_H

#include<iostream>
#include<string>
#include "State.h"
using namespace std;

class Operation {
  public:
    string name;
    Operation(); // nececitamos un constructor vacío para crear un arreglo de operaciones
    Operation(string n); // puede ser útil para crear operaciones con un nombre específico
    virtual bool isAppl(State* s);
    virtual State* apply(State* s);
};
#endif // OPERATION_H
