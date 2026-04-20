#include "Operation.h"

class Llenar5:  public Operation {
  public:
  Llenar5();
  bool isAppl(State* s);
  State* apply(State* s);
};