#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

#include "Graph.h"

int main(int argc, const char * argv[]) {

	Graph g1;
	g1.insertVertex(0);
	g1.insertVertex(1);
	g1.insertEdge(0,1,1);
	g1.insertEdge(1,0,1);

	vector<Vertex*> p = g1.shortestPath(0,1);

	if (true) {
	  Graph g;
	  
	  g.insertVertex(0);
	  g.insertVertex(1);
	  g.insertVertex(2);
	  g.insertVertex(3);
	  
	  g.insertEdge(0,1,5);
	  g.insertEdge(1,0,5);
	  g.insertEdge(1,3,5);
	  g.insertEdge(3,1,5);
	  g.insertEdge(0,2,7);
	  g.insertEdge(2,3,0.5);
	  g.insertEdge(3,2,0.5);
	  
	  g1 = g;
	
	}

	p = g1.shortestPath(0,3);

}