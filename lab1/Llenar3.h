#include "Operation.h"

class Llenar3:  public Operation {
  public:
   Llenar3();
   bool isAppl(State* s);
   State* apply(State* s);
};