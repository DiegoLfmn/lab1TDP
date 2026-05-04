all: testState testStack testSolver testHeap

State.o: State.cpp State.h
	g++ -g -c State.cpp
Stack.o: Stack.cpp Stack.h
	g++ -g -c Stack.cpp
Solver.o: Solver.cpp Solver.h
	g++ -g -c Solver.cpp
Operation.o: Operation.cpp Operation.h
	g++ -g -c Operation.cpp
Heap.o: Heap.cpp Heap.h
	g++ -g -c Heap.cpp

testState: testState.cpp State.cpp Tablero.cpp Operation.cpp
	g++ -o testState testState.cpp State.cpp Tablero.cpp Operation.cpp
testStack: State.o Stack.o testStack.cpp 
	g++ -g State.o Stack.o testStack.cpp -o testStack
testSolver: testSolver.cpp Solver.cpp Tablero.cpp Tree.cpp Operation.cpp State.cpp Heap.cpp
	g++ -o testSolver testSolver.cpp Solver.cpp Tablero.cpp Tree.cpp Operation.cpp State.cpp Heap.cpp
testHeap: Heap.o State.o testHeap.cpp
	g++ -g Heap.o State.o testHeap.cpp -o testHeap
testTablero: testTablero.cpp Tablero.cpp State.cpp
	g++ -o testTablero testTablero.cpp Tablero.cpp State.cpp

clean: 
	rm -f *.o testState testStack testSolver testHeap testTablero