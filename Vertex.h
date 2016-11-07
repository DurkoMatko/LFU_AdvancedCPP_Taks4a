#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED

#include <vector>
#include <string>
#include <cstdlib>

#include "Edge.h"

class Vertex{
	public:
		Vertex(int Id);
		virtual ~Vertex();
		int getId();
		std::string getName();
	protected:
	private:
		int id;
		std::string name;
};

#endif // VERTEX_H_INCLUDED
