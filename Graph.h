#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <string>
#include <cstdio>
#include <list>
#include <map>
#include <map>
#include "Vertex.h"
#include "Edge.h"

class Graph{
	public:
		Graph();
		Graph(unsigned n, bool isConnected);
		Graph(const Graph& g) noexcept;	//copy constructor
		Graph(Graph&& g) noexcept;   //move constructor
		virtual ~Graph() noexcept;
		bool vertexExists(int node) const;			//existNode
		bool edgeExists(int firstVertex,int secondVertex) const;
		void addVertex(int id);
		std::vector<int> getVertices();
		void addEdge(int firstVertex, int secondVertex, int dist);
		bool isConnected() const;
		void search(int firstVertex, int secondVertex) const;
		friend std::ostream& operator<<(std::ostream& os, const Graph& g);		//needs to be friend cuz it's defined outside of class and needs to access ajacencyList
		friend std::ostream& operator<<(std::ostream& os, Graph& g);		//needs to be friend cuz it's defined outside of class and needs to access ajacencyList
		Graph& operator=(const Graph& g) noexcept;
		Graph& operator=(Graph&& g) noexcept;

	protected:
	private:
		std::map<int,std::list<std::pair<int, int>>> adjacencyList;		
};


#endif // GRAPH_H_INCLUDED