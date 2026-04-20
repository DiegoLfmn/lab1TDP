#include "Llenar5.h"

Llenar5::Llenar5() {
  name="LLENAR B5";
}

bool Llenar5::isAppl(State* s) {
  return(s->B5<5);
}

State* Llenar5::apply(State* s) {
  return new State(5, s->B3, name, s, 0);
}
