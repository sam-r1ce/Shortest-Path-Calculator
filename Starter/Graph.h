#ifndef GRAPH_H
#define GRAPH_H

#include "LocatorHeap.h"

#include <vector>
using std::vector;


class Edge;

class Vertex
{
public:
    int label;
    vector<Edge*> edges;

    // helpers stored inside a vertex to help with path finding
    // you can use different auxilliary structures if desired
    bool visited;
    float distanceTo;
    vector<Vertex*> pathTo;
    Heap<Vertex*>::Locator locator;
    bool operator < ( const Vertex &v ) const 
    { 
        if(distanceTo<v.distanceTo){
            return true;
        }
        return false;

    }

    Vertex ( int l ) : label (l) { }
};

class Edge
{
public:
    Vertex *v1, *v2;
    float weight;

    Edge ( Vertex *nv1, Vertex *nv2, float newWeight ) : v1 ( nv1 ), v2 ( nv2 ), weight ( newWeight ) { }
};


class Graph
{
protected:
    vector<Vertex*> v;
    vector<Edge*> e;

public:
    Graph () {}

    void clearGraph(){
        for (auto vertex : v) {
            delete vertex;
        }
        v.clear();

        for (auto edge : e) {
            delete edge;
        }
        e.clear();
    }

    void copyGraph(const Graph& other){
            for (auto vertex : other.v)
            {
                Vertex* newVertex = new Vertex(vertex->label);
                v.push_back(newVertex);
            }

            
            for (auto edge : other.e)
            {
                insertEdge(edge->v1->label,edge->v2->label,edge->weight);
            }
    }

    ~Graph ()
    {
        clearGraph();
    }

    Graph(const Graph& other){
        
        copyGraph(other);
    }

    Graph& operator=(const Graph& other){
        if (this != &other) 
        {
            clearGraph();

            copyGraph(other);

            
        }
        return *this;
    }


    void insertVertex ( int label )
    {
        Vertex* newvertex = new Vertex(label);
        v.push_back(newvertex);
    }

    void insertEdge ( int l1, int l2, float weight )
    {
        Vertex* vertex1 = nullptr;
        Vertex* vertex2 = nullptr;

        for (auto vertex : v) {
            if (vertex->label ==l1) {
                vertex1 = vertex;
            }
            else if (vertex->label== l2) {
                vertex2 = vertex;
            }

            if (vertex1!= nullptr&& vertex2!= nullptr){
                break;
            }
        }
        if (vertex1== nullptr|| vertex2== nullptr){
            return;
        }

        Edge* newedge= new Edge(vertex1, vertex2, weight);
        vertex1->edges.push_back(newedge);
        vertex2->edges.push_back(newedge);
        e.push_back(newedge);
    }

    vector<Vertex*> shortestPath(int start, int end) {
//     // Step 1: Initialize vertex properties
    Heap<Vertex*> pq;
    Vertex* startVertex = v.at(start);
    startVertex->distanceTo = 0;
    startVertex->locator=pq.insertElement(startVertex);
    startVertex->pathTo.push_back(startVertex);

    

    for (auto vertex : v) {
        if(vertex==startVertex){
            continue;
        }
        vertex->visited = false;
        vertex->distanceTo = __FLT_MAX__;
        vertex->pathTo.clear();
        vertex->locator = pq.insertElement(vertex);
        
    }
    
    


    while (!v.at(end)->visited) {
        
        Vertex* currentVertex = pq.removeMin();
        
        
        
        for (auto edge : currentVertex->edges) {
            if(edge->v1 != currentVertex){
                continue;
            }
            Vertex* closeVertex = edge->v2;
            if (closeVertex->visited) {
                continue;
            }
            float newDistance =currentVertex->distanceTo + edge->weight;

            // cout << currentVertex->label << endl;
            
            // cout << closeVertex->label << " " << newDistance<< " " << closeVertex->distanceTo<< endl;
            
            if (newDistance < closeVertex->distanceTo) {
                closeVertex->distanceTo = newDistance;
                
                closeVertex->pathTo.clear();
                for(auto verticies:currentVertex->pathTo){
                    // cout <<" " <<verticies->label << endl;
                    closeVertex->pathTo.push_back(verticies);
                    
                }
                if(currentVertex!=v.at(start)){
                    closeVertex->pathTo.push_back(currentVertex);
                }
                
                pq.update(closeVertex->locator);
            }
        }
        currentVertex->visited = true;
        // v.at(end)->pathTo.push_back(currentVertex);
    }

    v.at(end)->pathTo.push_back(v.at(end));

    return v.at(end)->pathTo;
}


};

#endif
