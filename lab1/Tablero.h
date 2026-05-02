#ifndef TABLERO_H
#define TABLERO_H


#include "State.h"
#include <iostream>

#include <fstream>
#include <string>

using namespace std;

struct BlockConfig {
    int id;
    char color;
    int width;
    int height;
    int init_x,init_y; // posicion inicial
    bool* geometry; //arreglo dinamico para tner los valores matriciales en un arreglo weight * height
};

struct ExitConfig {
    char color;
    int x;
    int y;
    char orientation;
    int li,lf,step;
};


class Tablero {
  public:
    string nombre;
    int width;
    int height;
    int stepLimit;

    char** paredes;

    BlockConfig* blockConfigs;
    int numBlocks;

    ExitConfig* exitConfigs;
    int numExits;
    //constructor y destructor
    Tablero();

    ~Tablero();


    // métodos
    int extraerEntero(string linea, string etiqueta);
    char extraerCaracter(string linea, string etiqueta);
    
    bool cargarArchivo(string filename);

    State* generarEstadoInicial();

    void printTablero();


    
};

















#endif // TABLERO_H