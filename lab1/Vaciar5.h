#include "Operation.h"

class Vaciar5:  public Operation {
  public:
  Vaciar5();
  bool isAppl(State* s);
  State* apply(State* s);
};

