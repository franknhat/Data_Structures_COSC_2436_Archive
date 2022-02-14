#include "functions.h"
#include "ArgumentManager.h"

int main(int argc, char* argv[]){
    ArgumentManager am(argc, argv);
    std::string inputFileName= am.get("input");
    std::string outputFileName= am.get("output");
    std::string commandFileName= am.get("command");

    ifstream readCommand(commandFileName);
    
    bTree test;
    insertToTree(test, readCommand, inputFileName);
    runCommand(test, readCommand, outputFileName);

    readCommand.close();
    return 0;
}