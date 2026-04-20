all: testState testStack testSolver testHeap

State.o: State.cpp State.h
	g++ -g -c State.cpp
Stack.o: Stack.cpp Stack.h
	g++ -g -c Stack.cpp
Solver.o: Solver.cpp Solver.h
	g++ -g -c Solver.cpp
Operation.o: Operation.cpp Operation.h
	g++ -g -c Operation.cpp
Llenar5.o: Llenar5.cpp Llenar5.h
	g++ -g -c Llenar5.cpp
Llenar3.o: Llenar3.cpp Llenar3.h
	g++ -g -c Llenar3.cpp
Vaciar5.o: Vaciar5.cpp Vaciar5.h
	g++ -g -c Vaciar5.cpp
Vaciar3.o: Vaciar3.cpp Vaciar3.h
	g++ -g -c Vaciar3.cpp
Trasv35.o: Trasv35.cpp Trasv35.h
	g++ -g -c Trasv35.cpp
Trasv53.o: Trasv53.cpp Trasv53.h
	g++ -g -c Trasv53.cpp
Heap.o: Heap.cpp Heap.h
	g++ -g -c Heap.cpp

testState: State.o testState.cpp
	g++ -g State.o testState.cpp -o testState
testStack: State.o Stack.o testStack.cpp 
	g++ -g State.o Stack.o testStack.cpp -o testStack
testSolver: Heap.o Operation.o Llenar3.o Llenar5.o Vaciar3.o Vaciar5.o Trasv35.o Trasv53.o Solver.o Heap.o Stack.o State.o testSolver.cpp 
	g++ -g Heap.o Operation.o Llenar3.o Llenar5.o Vaciar3.o Vaciar5.o Trasv35.o Trasv53.o Solver.o Stack.o State.o testSolver.cpp -o testSolver
testHeap: Heap.o State.o testHeap.cpp
	g++ -g Heap.o State.o testHeap.cpp -o testHeap

clean: 
	rm -f *.o testState testStack testSolver testHeap