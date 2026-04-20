#include <iostream>
#include "State.h"
using namespace std;

class Heap {
    public:
      State** arr;
      int size;
      int capacity;
      Heap();
      Heap(int capacity);
      ~Heap();
      void push(State* s);
      State* pop();
      void heapifyDown(int index); 
      void heapifyUp(int index);
      void print();
      bool isEmpty();
};