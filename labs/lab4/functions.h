#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "priorityQueue.h"

void readFromFile(std::string infilename, priorityQueue &Q){
    std::ifstream input;
    input.open(infilename);
    std::string line;
    int firstDigIdx=0;
    while (!input.eof()){
        getline(input, line);
        if(line.length()>1){
            firstDigIdx=0;
            for (int i=0;i<line.length();i++){
                if(isdigit(line[i]) && firstDigIdx==0)
                    firstDigIdx=i;
            }
            Q.addToOrder(line.substr(0,firstDigIdx-1),stod(line.substr(firstDigIdx)));
        }
    }
    
    input.close();
}

#endif