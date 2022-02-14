#include "ArgumentManager.h"
#include "functions.h"

int main(int argc, char* argv[]){
    ArgumentManager am(argc, argv);
    string inputFileName= am.get("input");
    string outputFileName= am.get("output");

    GameDataList data;
    InputManager(inputFileName, data);
    data.outputToFile(outputFileName);
    return 0;
}