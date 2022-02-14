#include "graph.h"

graph::graph(){
    arr=nullptr;
    numVert=0;
}

graph::graph(int v){
    arr=new int*[v];
    for(int i=0;i<v;i++)
        arr[i]=new int[v];
    numVert=v;
    for(int i=0;i<numVert;i++)
        for(int j=0;j<numVert;j++)
            arr[i][j]=0;
}

graph::~graph(){
    for(int i=0;i<numVert;i++)
        delete[] arr[i];
    delete [] arr;
}

int graph::getNumVert(){
    return numVert;
}

void graph::setNumVert(int v){
    if(numVert!=0){
        for(int i=0;i<numVert;i++)
            delete[] arr[i];
        delete[] arr;
        arr=nullptr;
    }
    numVert=v;
    arr=new int*[numVert];
    for(int i=0;i<numVert;i++)
        arr[i]=new int[numVert];
    for(int i=0;i<numVert;i++){
        for(int j=0;j<numVert;j++){
            arr[i][j]=0;
        }
    }
}

void graph::createEdge(int v1, int v2, int d){
    if(v1==v2 && d!=0){
        std::cout<<"how??"<<std::endl;
        return;
    }
    arr[v1-1][v2-1]=arr[v2-1][v1-1]=d; //have to -1 to make the vertices mach index values
}

void graph::print(){
    if(arr==nullptr)
        std::cout<<"Empty dumbass"<<std::endl;
    else{
        for(int i=0;i<numVert;i++){
            for(int j=0;j<numVert;j++)
                std::cout<<arr[i][j]<<"\t";
            std::cout<<"\n";
        }
    }
}

int graph::Dijkstra(int source, int destination){
    int* dist=new int[numVert];
    for(int i=0;i<numVert;i++)
        i==source-1?dist[i]=0:dist[i]=-1;

    bool* visted= new bool[numVert]; //tells what edges we can use
    for(int i=0;i<numVert;i++)
        i==source-1?visted[i]=true:visted[i]=false;
    bool allEdges=false;
    
    //implement the algo
    for(int i=0;i<numVert;i++)
        if(arr[source-1][i]>0){
            dist[i]=arr[source-1][i];
            arr[source-1][i]*=-1;
            arr[i][source-1]*=-1;
            visted[i]=true;
        }
    while(!allEdges){
        int minEdgeS=-1, minEdgeE=-1, minDist=-1;
        for(int i=0;i<numVert;i++)
            if(visted[i]==true)
                for(int j=0;j<numVert;j++)
                    if(arr[i][j]>0 && ((arr[i][j]<minDist) || (arr[i][j]==minDist && dist[i]<dist[minEdgeS]) ||minDist==-1)){
                        minEdgeS=i;
                        minEdgeE=j;
                        minDist=arr[i][j];
                    }
        arr[minEdgeE][minEdgeS]*=-1;
        arr[minEdgeS][minEdgeE]*=-1;
        visted[minEdgeE]=true;
        if(dist[minEdgeE]<0 || dist[minEdgeE]>(dist[minEdgeS]+minDist)){
            dist[minEdgeE]=dist[minEdgeS]+minDist;
            std::cout<<"Enter the last if \n";
        }
        allEdges=true;
        for(int i=0;i<numVert;i++)
            for(int j=0;j<i;j++)
                if(arr[i][j]>0)
                    allEdges=false;
    }
    for(int i=0;i<numVert;i++)
        for(int j=0;j<=i;j++)
            if(arr[i][j]<0){
                arr[i][j]*=-1;
                arr[j][i]*=-1;
            }
    int distance=dist[destination-1];
    
    delete[] dist,visted;
    return distance;
}