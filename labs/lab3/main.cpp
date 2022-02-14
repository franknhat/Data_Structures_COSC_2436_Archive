#include "ArgumentManager.h"
#include "functions.h"

int main(int argc, char* argv[]){ //clean up code and add argument manager
    ArgumentManager am(argc, argv);
    string inputFileName=am.get("input");
    string outputFileName=am.get("output");
    
    int numBooks=0;
    std::string* bookshelf=new std::string[numBooks]; //this will be a dyn array to hold the books when dequeued and add to bookshelf
    int timeTaken=0;
    
    organizeBooks(inputFileName,bookshelf, numBooks, timeTaken);
    outputToFile(outputFileName, timeTaken ,bookshelf, numBooks);

    return 0;
}