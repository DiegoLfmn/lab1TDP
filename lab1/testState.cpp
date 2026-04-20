#include "State.h"

int main() {
  State s1(5, 0, "llenar B5", nullptr, 0);
  s1.print();
  State s2(2, 3, "tras 53", &s1, 0);
  s2.print();
  State s3(2, 0, "vaciar 3", &s2, 0);
  s3.print();
  State s4(0, 2, "tras 53", &s3, 0);
  s4.print();
  State s5(5, 2, "llenar B5", &s4, 0);
  s5.print();
  State s6(4, 3, "tras 53", &s5, 0);
  s6.print();

  s6.printOperaciones();
  return 0;
}