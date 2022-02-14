#include "functions.h"
#include "ArgumentManager.h"

int main(int argc, char* argv[]){ //clean up code and add argument manager
    ArgumentManager am(argc, argv);
    string inputFileName=am.get("input");
    string outputFileName=am.get("output");

    priorityQueue Q;
    readFromFile(inputFileName, Q);
    Q.outputToFile(outputFileName);
}