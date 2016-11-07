#include "Edge.h"
#include "Graph.h"
#include "Graph.cpp"
#include "Vertex.h"
#include <iostream>

int main(){

	//testing not connected graph
	Graph g(5,false);	//not connected graph with 5 vertexes
	g.addVertex(30);
	g.addEdge(3,30,100);
	g.addEdge(3,32,100);
	std::cout << g;
	
	try{
		g.search(3,4);
	}
	catch(const GraphNotConnected& gnc){
		std::cerr << gnc.what() <<  '\n';
	}


	//testing connected graph
	std::cout << "\n\n\nConnected graph" <<std::endl;
	Graph gConnected(7,true);
	std::cout << gConnected;
	std::cout << gConnected.isConnected() << std::endl;
	gConnected.search(2,6);


	
	//testing const graph
	std::cout << "\n\n\nConst graph" <<std::endl;
	const Graph gConst(4,true);
	std::cout << gConst;

	//testing copy constructor
	std::cout << "\n\n\nCopied graph" <<std::endl;
	Graph gCopied(g);
	std::cout << gCopied;

	//testing copy assignment operator
	std::cout << "\n\n\nCopy-assigned graph" <<std::endl;
	gCopied = g;
	std::cout << gCopied;

	//testing move constructor
	std::cout << "\n\n\nMoved graph" <<std::endl;
	Graph gMoved = std::move(g);
	std::cout << gMoved;

	//testing move assignment constructor
	std::cout << "\n\n\nMove-assigned graph" <<std::endl;
	gMoved = std::move(gConnected);
	std::cout << gMoved;

	return EXIT_SUCCESS;
}
