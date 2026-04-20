#include "Vaciar5.h"

Vaciar5::Vaciar5() {
  name="VACIAR B5";
}

bool Vaciar5::isAppl(State* s) {
  return(s->B5>0);
}

State* Vaciar5::apply(State* s) {
  return new State(0, s->B3, name, s, 0);
}
