#include "functions.h"
#include "ArgumentManager.h"

int main(int argc, char* argv[]){
    ArgumentManager am(argc, argv);
    std::string inputFileName= am.get("input");
    std::string outputFileName= am.get("output");
 
    AVL test;
   
    appendToTree(test, inputFileName);
    printLevelOrder(&test, outputFileName);
    return 0;
}