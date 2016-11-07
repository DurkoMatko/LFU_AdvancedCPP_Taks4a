#include "Graph.h"
#include "Vertex.h"
#include <iostream>
#include <map>
#include <list>
#include <set>
#include <queue>
#include <stdexcept>
#include <vector>
#include <cstddef>
#include <random>

int test(Graph g){
	
}

struct NameAlreadyUsedException: public std::exception{
  virtual const char* what() const throw(){
    return "Vertice id already in use";
  }
};

struct GraphNotConnected: public std::exception{
  virtual const char* what() const throw(){
    return "The graph is not connected";
  }
};


//bit shift operator overload instead of printGraph() method
std::ostream& operator<<(std::ostream& os, Graph& g)
{
    //here I have to iterate keys - because user can add vertex with random ID
	for(auto iter = g.adjacencyList.cbegin(); iter != g.adjacencyList.cend(); ++iter){		
		os << "Vertice " << iter->first << ":" << std::endl;
		//iterate list of pairs representing edges to other vertices
		for(const auto& onePair : g.adjacencyList.at(iter->first)){
			os << "\t" << onePair.first << "-" << onePair.second << std::endl;
		}
		os << std::endl;
	}
    return os;
}

//bit shift operator overload instead of printGraph() method
std::ostream& operator<<(std::ostream& os, const Graph& g)
{
	os <<"This graph is const" << std::endl;
    //here I have to iterate keys - because user can add vertex with random ID
	for(auto iter = g.adjacencyList.cbegin(); iter != g.adjacencyList.cend(); ++iter){		
		os << "Vertice " << iter->first << ":" << std::endl;
		//iterate list of pairs representing edges to other vertices
		for(const auto& onePair : g.adjacencyList.at(iter->first)){
			os << "\t" << onePair.first << "-" << onePair.second << std::endl;
		}
		os << std::endl;
	}
    return os;
}

Graph::Graph()
{
    //ctor
}

Graph::Graph(unsigned n, bool isConnected)
{
	int vertex1,vertex2,dist,numberOfEdges;

	//define random generators needed
	std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> vertexChooser(0, n-1);
    std::uniform_int_distribution<> distanceGenerator(1, 256);
    if(isConnected){
    	// if connected, number of edges must be min n-1
    	std::uniform_int_distribution<> numberOfEdgesGenerator(n-1, n*(n-1)/2); 
    	numberOfEdges = numberOfEdgesGenerator(eng);
    }
    else{
    	// if not connected number of edges is not important
    	std::uniform_int_distribution<> numberOfEdgesGenerator(0, n*(n-1)/2); 
    	numberOfEdges = numberOfEdgesGenerator(eng);
    }
    
    //create n number of vertexes
	for(int i=0;i<n;i++){
		this->addVertex(i);
	}

	if(isConnected){
		/*start from vertex n.1 and always generate an edge for current index vertex*/	
	    for(int i=1;i<n;i++){
			vertex2 = vertexChooser(eng)%i;			//modulo needed to stay in bounds of already created vertices
	    	dist = distanceGenerator(eng);
	    	//vertexes of edge can't be the same && edge can't already be present in the graph
	    	while(i==vertex2 || this->edgeExists(i,vertex2)){
	    		vertex2 = vertexChooser(eng)%i;
	    	}

	    	this->addEdge(i,vertex2,dist);

	    	//decrement number of left edges to generate
	    	numberOfEdges--;
		}
	}
	//generate rest of edges (connected graph) resp. all edges(unconnected graph) randomly
	else{
	    while(numberOfEdges>0){
	    	vertex1 = vertexChooser(eng);
	    	vertex2 = vertexChooser(eng);
	    	dist = distanceGenerator(eng);
	        //while chosen vertex1 already has edges to all vertexes, choose new vertex1
	    	while(adjacencyList.at(vertex1).size()==n-1){
	    		vertex1 = vertexChooser(eng);
	    	}
	    	//vertexes of edge can't be the same one && edge can't already be in the graph
	    	while(vertex1==vertex2  || this->edgeExists(vertex1,vertex2)){
	    		vertex2 = vertexChooser(eng);
	    	}

	    	//add edge between 2 randomly chosen edges
	    	this->addEdge(vertex1,vertex2,dist);

	    	//decrement number of left edges to generate
	    	numberOfEdges--;
	    }
	}
}

//copy constructor
Graph::Graph(const Graph& g) noexcept{
	adjacencyList.insert(g.adjacencyList.begin(),g.adjacencyList.end());
}

//move constructor
Graph::Graph(Graph&& g) noexcept{
	adjacencyList.insert(g.adjacencyList.begin(),g.adjacencyList.end());
	g.adjacencyList.clear();
}

//copy assign operator
Graph &Graph::operator=(const Graph& g) noexcept{		
	//clear previous data
	adjacencyList.clear();
	adjacencyList.insert(g.adjacencyList.begin(),g.adjacencyList.end());
	return *this;
}

//move assign operator
Graph &Graph::operator=(Graph&& g) noexcept{
	adjacencyList.clear();
    adjacencyList.insert(g.adjacencyList.begin(),g.adjacencyList.end());
	g.adjacencyList.clear();
    return *this;
}

Graph::~Graph()
{
	//dtor
}

bool Graph::vertexExists(int node) const{
	return adjacencyList.find(node) != adjacencyList.end();
}

bool Graph::edgeExists(int firstVertex,int secondVertex) const{
	for(auto& pair : adjacencyList.at(firstVertex)){
		if(pair.first == secondVertex)
			return true;
	}
	return false;
}

void Graph::addVertex(int id){
	try{
		//create new edge list for new vertex	
		if(!adjacencyList.insert(std::make_pair(id, std::list<std::pair<int, int>>())).second){				
			throw NameAlreadyUsedException();
		}
	}
	catch(const NameAlreadyUsedException& e){													//catch exception
		std::cerr << e.what() << " - id: " <<  id << std::endl;
	}
}


std::vector<int> Graph::getVertices(){
	//return all keys of adjacencyList map 
	std::vector<int> vertices;
	for (auto& pair : adjacencyList){
    	vertices.emplace_back(pair.first);
	}
	return vertices;
}

void Graph::addEdge(int firstVertex, int secondVertex, int dist){
	try{
		if(this->vertexExists(firstVertex) && this->vertexExists(secondVertex)){
			adjacencyList.at(firstVertex).push_back(std::make_pair(secondVertex,dist));
			adjacencyList.at(secondVertex).push_back(std::make_pair(firstVertex,dist));	
		}
		else{
			throw std::out_of_range("Vertex does not exist");	
		}
	}
	catch(const std::out_of_range& oor){
		std::cerr << "Out of Range error - addEdge(" << firstVertex << ", " << secondVertex << "," << dist << ") " << oor.what() <<  '\n';
	}
}

bool Graph::isConnected() const{
	//BFS implementation
	std::queue<int> Q;	
	//set is more effective then vector in looking up if contains an element
	std::set<int> visited;	
	//nodes currently or previously in queue in queue
	std::set<int> queued;	
	//root node	
	Q.push(0);

	//while queue is not empty and I haven't visited all vertices
	while(!Q.empty() && visited.size() != adjacencyList.size()){
		int current = Q.front();
		Q.pop();
		visited.insert(current);

		//get list of neighbors for currend vertex and iterate over them
		for(auto neighborIterator = adjacencyList.at(current).begin(); neighborIterator != adjacencyList.at(current).end(); ++neighborIterator){
			//if neigbor wasn't visited or isn't aready in queue,then add it to queue
			if(visited.find(neighborIterator->first) == visited.end() &&
			   queued.find(neighborIterator->first) == queued.end()){
			   		//add to queue
					Q.push(neighborIterator->first);
					queued.insert(neighborIterator->first);
			}
		}
	}

	//return if all vertexes have been visited
	return visited.size() == adjacencyList.size();
}

void Graph::search(int firstVertex,int secondVertex) const{
	//throws exception if the graph is not connected
	if(!this->isConnected())
		throw GraphNotConnected();

	//queue of pair<parent (from), child (to)>
	std::queue<std::pair<int,int>> Q;	
	Q.push(std::make_pair(firstVertex,firstVertex));
	//set is more effective then vector in looking up if contains an element
	std::set<int> visited;	
	std::set<int> queued;		//already in queue
	std::map<int,int> reconstructMap;		//child-parent map to reconstruct path
	int current;

	//while queue is not empty and I haven't visited all vertices
	while(!Q.empty() && current!=secondVertex){
		current = Q.front().second;
		Q.pop();
		visited.insert(current);
		//get list of neighbors for currend vertex and iterate over it
		for(auto neighborIterator = adjacencyList.at(current).begin(); neighborIterator != adjacencyList.at(current).end(); ++neighborIterator){
			//if neigbor wasn't visited or isn't aready in queue,then add it to queue
			if(visited.find(neighborIterator->first) == visited.end() &&
			   queued.find(neighborIterator->first) == queued.end()){
			   		//add to queue
					Q.push(std::make_pair(current,neighborIterator->first));
					reconstructMap[neighborIterator->first] = current;
					queued.insert(neighborIterator->first);
			}
		}
	}

	//reconstruct path
	std::vector<int> pathTaken;
	pathTaken.push_back(current);
	while(current!=firstVertex){
		current=reconstructMap.at(current);
		pathTaken.push_back(current);
	}
	//reverse iterate and print path
	std::cout << "Path from " << firstVertex << " to " << secondVertex << std::endl;
	for (auto it = pathTaken.rbegin(); it != pathTaken.rend(); ++it){
    	std::cout << *it;
    	if(*it != secondVertex)
    		std::cout << "->";
	}
	std::cout << std::endl;
}