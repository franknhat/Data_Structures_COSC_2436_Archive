#include "ArgumentManager.h"
#include "book.h"
#include "functions.h"

int main(int argc, char* argv[]){
    ArgumentManager am(argc, argv);
    std::string inputFileName= am.get("input");
    std::string outputFileName= am.get("output");
    std::string commandFileName= am.get("command");
    InputFormat(inputFileName);
    CommandManager(commandFileName);
    runCommands();
    outputBooks(outputFileName);
    return 0;
}