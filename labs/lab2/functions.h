#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "GameDataList.h"

bool isValidLine(std::string line){
    int commaCount=0;
    bool hasInt=false;
    bool hasChar=false;
    for (char eachchar:line){ //bruh moment this didnt matter for the lab for some reason
        if (eachchar==',')
            commaCount++;
        if (isdigit(eachchar))
            hasInt=true;
        if (isalpha(eachchar))
            hasChar=true;
    }
    if (commaCount!=1 || hasInt==false || hasChar==false)
        return false;
    for (char eachchar: line.substr(line.find(',')+1)){
        if (isdigit(eachchar)==false)
            return false;
    }
    return true;
}

std::string RemoveWhiteSpace(std::string line){
    std::string newLine="";
    for (int i=0;i<line.size();i++){
        if(line[i]!=' ' && line[i]!='\n' &&line[i]!='\r')
            newLine+=line[i];
    }
    return newLine;
}

void InputManager(std::string infileName, GameDataList &data){
    ifstream input;
    std::string inputline;
    input.open(infileName);
    getline(input,inputline, '\r');
    input.close();
    char delim;
    if (inputline.find('\n')!=-1)
        delim='\n';
    else
        delim='\r';
    input.open(infileName);
    while (!input.eof()){
        getline(input, inputline, delim);
        inputline=RemoveWhiteSpace(inputline);
        if (isValidLine(inputline)==false)
            continue;
        data.addOrder(inputline.substr(0,inputline.find(',')), stoi(inputline.substr(inputline.find(',')+1)));
    }
}
#endif