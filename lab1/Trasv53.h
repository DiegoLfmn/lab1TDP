#include "Operation.h"

class Trasv53:  public Operation {
  public:
  Trasv53();
  bool isAppl(State* s);
  State* apply(State* s);
};