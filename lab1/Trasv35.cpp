#include "Trasv35.h"

Trasv35::Trasv35() {
  name="TRASV B3 A B5";
}

bool Trasv35::isAppl(State* s) {
  return(s->B3>0 && s->B5<5); // que exista algo en B3 y espacio en B5
}

State* Trasv35::apply(State* s) {
  int trasv=min(s->B3, 5-s->B5); // lo que se pueda trasvasar de B3 a B5
  return new State(s->B5+trasv, s->B3-trasv, name, s, 0);
}

