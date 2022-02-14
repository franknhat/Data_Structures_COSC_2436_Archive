#include "functions.h"
#include "ArgumentManager.h"
#include <string>

int main(int argc, char* argv[]){
    ArgumentManager am(argc, argv);
    std::string inputFileName=am.get("input");
    std::string outputFileName=am.get("output");
    std::string commandFileName=am.get("command"); 

    FixedLL equationList;
    createLinkedList(inputFileName, equationList);
    runCommands(commandFileName, outputFileName, equationList);
    return 0;
}