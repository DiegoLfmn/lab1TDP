#ifndef OPERATION_H
#define OPERATION_H

#include<iostream>
#include<string>
#include "State.h"
#include "Tablero.h"
using namespace std;

class Operation {
  public:
    int block_id;
    int pasos;
    Tablero* tablero; // referencia al tablero para verificar la validez de la operación
    
    Operation(int b_id, int pasos, Tablero* tablero); // constructor con parámetros
    virtual ~Operation(); // destructor virtual para permitir la herencia

    virtual bool isAppl(State* current) = 0;
    virtual State* apply(State* current)= 0;

    bool hayBloqueEnPosicion(State* current, int x, int y, int excluido_id); // método para verificar si hay un bloque en una posición dada
    bool esMiSalida(int x, int y, char miColor); // método para verificar si esta operación lleva al estado final
    bool seEscapa(int new_x, int new_y, int b_id); // método para verificar si el bloque se escapa del tablero
};


class MoveUp : public Operation {
  public:
    MoveUp(int b_id, int pasos, Tablero* tablero);
    bool isAppl(State* current) override;
    State* apply(State* current) override;
};

class MoveDown : public Operation {
  public:
    MoveDown(int b_id, int pasos, Tablero* tablero);
    bool isAppl(State* current) override;
    State* apply(State* current) override;
};

class MoveLeft : public Operation {
  public:
    MoveLeft(int b_id, int pasos, Tablero* tablero);
    bool isAppl(State* current) override;
    State* apply(State* current) override;
};

class MoveRight : public Operation {
  public:
    MoveRight(int b_id, int pasos, Tablero* tablero);
    bool isAppl(State* current) override;
    State* apply(State* current) override;
};
#endif // OPERATION_H
