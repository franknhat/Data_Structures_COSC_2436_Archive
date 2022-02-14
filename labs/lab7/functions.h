#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "graph.h"
#include <fstream>
#include <string>

void createGraph(graph &daGraph, std::string inputFileName, int &start, int& fin){
    std::ifstream input(inputFileName);
    int numV,numE, v1, v2, d;
    input>>numV>>numE>>start>>fin;
    daGraph.setNumVert(numV);
    for(int i=0;i<numE;i++){
        input>>v1>>v2>>d;
        daGraph.createEdge(v1,v2,d);
    }
}

#endif