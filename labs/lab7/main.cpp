#include "ArgumentManager.h"
#include "functions.h"

int main(int argc, char* argv[]){
    ArgumentManager am(argc, argv);
    std::string inputFileName= am.get("input");
    std::string outputFileName= am.get("output");

    int source,end;
    graph test;
    
    createGraph(test,inputFileName,source,end);

    std::ofstream output(outputFileName);
    output<<test.Dijkstra(source,end)<<std::endl;
    output.close();

    return 0;
}