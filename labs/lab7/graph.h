#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

class graph{
private:
    int** arr;
    int numVert;
public:
    graph();
    graph(int);
    ~graph();
    int getNumVert();
    void setNumVert(int);
    void createEdge(int, int, int);
    void print();
    int Dijkstra(int, int);
};

#endif