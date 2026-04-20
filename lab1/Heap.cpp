#include "Heap.h"

Heap::Heap() {
  this->capacity = 10;
  this->size = 0;
  this->arr = new State*[capacity]; 
}

Heap::Heap(int capacity){
    this->capacity = capacity;
    this->size = 0;
    this->arr = new State*[capacity];
}
  
Heap::~Heap(){
    delete[] arr;
}

void Heap::push(State* s){
    if(size == capacity){
        State ** newArr = new State*[capacity*2];
        for(int i=0; i<size; i++){
            newArr[i] = arr[i]; 
        }
        delete[] arr;
        arr = newArr;
        capacity *= 2;
    }
    arr[size] = s;
    size++;
    heapifyUp(size-1);
}

void Heap::heapifyUp(int index){
    while(index>0 && 
          arr[(index-1)/2]->F < arr[index]->F){
        State* temp = arr[index];
        arr[index] = arr[(index-1)/2];
        arr[(index-1)/2] = temp;
        index = (index-1)/2;
    }
}

State* Heap::pop(){
    if(size == 0){
        return nullptr;
    }
    State* temp = arr[0];
    arr[0] = arr[size-1];
    size--;
    heapifyDown(0);
    return temp;
}

void Heap::heapifyDown(int index){
    int largest = index;
    int left = 2*index + 1;
    int right = 2*index + 2;
    if(left < size && arr[left]->F > arr[largest]->F){
        largest = left;
    }
    if(right < size && arr[right]->F > arr[largest]->F){
        largest = right;
    }
    if(largest != index){
        State* temp = arr[index];
        arr[index] = arr[largest];
        arr[largest] = temp;
        heapifyDown(largest);
    }
}

bool Heap::isEmpty(){
    return size == 0;
}

void Heap::print(){
    for(int i=0; i<size; i++){
        arr[i]->print();
    }
}
