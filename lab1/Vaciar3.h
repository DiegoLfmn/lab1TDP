#include "Operation.h"

class Vaciar3:  public Operation {
  public:
  Vaciar3();
  bool isAppl(State* s);
  State* apply(State* s);
};