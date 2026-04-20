#include "Trasv53.h"

Trasv53::Trasv53() {
  name="TRASV B5 A B3";
}

bool Trasv53::isAppl(State* s) {
  return(s->B5>0 && s->B3<3); // que exista algo en B5 y espacio en B3
}

State* Trasv53::apply(State* s) {
  int trasv=min(s->B5, 3-s->B3); // lo que se pueda trasvasar de B5 a B3
  return new State(s->B5-trasv, s->B3+trasv, name, s, 0);
}
