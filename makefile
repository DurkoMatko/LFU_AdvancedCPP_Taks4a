all : GraphImplementation

GraphImplementation: Graph.o MyMain.o
	g++ -o GraphImplementation MyMain.o 

MyMain.o: main.cpp
	g++ -c main.cpp -o MyMain.o -std=c++11

Graph.o: Graph.cpp
	g++ -c -o Graph.o Graph.cpp -std=c++11


clean:
	rm GraphImplementation Graph.o MyMain.o



