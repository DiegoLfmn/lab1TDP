#include "Operation.h"

Operation::Operation() {
  name="";
}

Operation::Operation(string n) {
  name=n;
}

bool Operation::isAppl(State* s) {
  return false; 
}

State* Operation::apply(State* s) {
  return nullptr;
}

