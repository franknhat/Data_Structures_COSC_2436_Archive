#include "function.h"
#include "ArgumentManager.h"

int main(int argc, char* argv[]){
    ArgumentManager am(argc, argv);
    std::string inputFileName= am.get("input");
    std::string outputFileName= am.get("output");

    PriorityQueue codes;
    PriorityQueue commands;

    readFromFile(inputFileName,commands);
    runCommands(outputFileName,codes, commands);

    return 0;
}