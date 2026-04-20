#include "Vaciar3.h"

Vaciar3::Vaciar3() {
  name="VACIAR B3";
}

bool Vaciar3::isAppl(State* s) {
  return(s->B3>0);
}

State* Vaciar3::apply(State* s) {
  return new State(s->B5, 0, name, s, 0);
}

