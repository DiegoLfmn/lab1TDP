#include "Operation.h"

class Trasv35:  public Operation {
  public:
   Trasv35();
   bool isAppl(State* s);
   State* apply(State* s);
};