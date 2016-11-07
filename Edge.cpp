#include "Edge.h"
#include "Vertex.h"

Edge::~Edge()
{
    //dtor
}

Edge::Edge(Vertex &Origin, Vertex &Destination, int Distance):distance(Distance),origin(Origin),destination(Destination){
	
}

Vertex& Edge::getOrigin() {
	return this->origin;
}

Vertex& Edge::getDestination() {
	return this->destination;
}

int Edge::getDistance() {
	return distance;
}
