#include "Llenar3.h"

Llenar3::Llenar3() {
  name="LLENAR B3";
}

bool Llenar3::isAppl(State* s) {
  return(s->B3<3);
}

State* Llenar3::apply(State* s) {
  return new State(s->B5, 3, name, s, 0);
}

