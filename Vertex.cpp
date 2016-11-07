#include "Vertex.h"
#include "Edge.h"
#include <iostream>

Vertex::Vertex(int Id):id(Id)
{

}

Vertex::~Vertex()
{
    //dtor
}

int Vertex::getId(){
    return id;
}

std::string Vertex::getName() {
	return name;
} 


