#include <map>
#include <string>
#include <fstream>
#include "ArgumentManager.h"

int main(int argc, char* argv[]){
    ArgumentManager am(argc, argv);
    std::string inputFileName= am.get("input");
    std::string outputFileName= am.get("output");

    std::ifstream input(inputFileName);
    std::ofstream output(outputFileName);
    std::map<std::string, int> map;
    std::map<std::string, int>::iterator it;
    std::string inputStr;
    int numInputs, temp;

    input>>numInputs;
    for(int i=0;i<numInputs;i++){
        input>>inputStr;
        it=map.find(inputStr);
        if (it==map.end())
            map.insert(std::pair<std::string, int>(inputStr,1));
        else
            it->second++;
    }
    for(it=map.begin();it!=map.end();it++)
        output<<it->first<<": "<<it->second<<std::endl;
    input.close();
    output.close();
    return 0;
}