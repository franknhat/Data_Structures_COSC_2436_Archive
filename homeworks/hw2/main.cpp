#include "ArgumentManager.h"
#include "functions.h"

int main(int argc, char* argv[]){
    ArgumentManager am(argc, argv);
    std::string inputFileName= am.get("input");
    std::string outputFileName= am.get("output");
    std::string commandFileName= am.get("command"); 
    
    LinesList inputLines;
    inputManager(inputFileName,inputLines);
    runCommands(commandFileName, inputLines);
    inputLines.fileoutput(outputFileName);
    return 0;
}