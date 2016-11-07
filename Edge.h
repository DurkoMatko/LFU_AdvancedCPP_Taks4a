#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

class Vertex;

class Edge{
	public:
		Edge(Vertex &Origin, Vertex &Destination, int Distance);
		virtual ~Edge();
		Vertex& getOrigin();
		Vertex& getDestination();
		int getDistance();
	protected:
	private:
		Vertex &origin;
    	Vertex &destination;
    	int distance;
};


#endif //EDGE_H_INCLUDED