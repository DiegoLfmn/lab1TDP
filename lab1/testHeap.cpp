#include "Heap.h"

int main() {
    Heap* h = new Heap(2);
    cout << "Pushing elements into heap:" << endl;
    h->push(new State(100, 0, "operacion 1", nullptr, 10));
    h->push(new State(20, 0, "operacion 2", nullptr, 0));
    h->push(new State(300, 0, "operacion 3", nullptr, 9));
    h->push(new State(40, 0, "operacion 4", nullptr, 1));
    h->push(new State(500, 0, "operacion 5", nullptr, 5));
    h->push(new State(60, 0, "operacion 6", nullptr, 2));
    h->push(new State(700, 0, "operacion 7", nullptr, 8));
    h->print();

    cout << "Popping elements from heap:" << endl;

    while(!h->isEmpty()){
        State* s = h->pop();
        s->print();
    }
    return 0;   
}