#include <iostream>
#include<string>
#include "Stack.h"
#include "Heap.h"
#include "Llenar3.h"
#include "Llenar5.h"
#include "Vaciar3.h"
#include "Vaciar5.h"
#include "Trasv35.h"
#include "Trasv53.h"
using namespace std;


#define N_OPER 6

class Solver {
  public:
    Operation* O[N_OPER];
    Solver();
    State* solve(State* initial); // retorna estado final o nullptr sino tiene solucion
};