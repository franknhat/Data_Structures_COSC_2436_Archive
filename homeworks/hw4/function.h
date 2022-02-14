#ifndef FUNCTION_H
#define FUCNTION_H

#include "PriorityQueue.h"

std::string replace(std::string, char, char);
std::string add(std::string, char, char);
std::string remove(std::string, char);
std::string swap(std::string, char, char);

void readFromFile(std::string inputFileName,PriorityQueue &commands){
    std::ifstream inputFile;
    inputFile.open(inputFileName);
    std::string curLine;
    while(!inputFile.eof()){
        getline(inputFile, curLine);
        if(curLine!="" || curLine!=" ")
            commands.enQueueByPriority(curLine.substr(0,curLine.find('(')), stoi(curLine.substr(curLine.find('(')+1)));
        else
            std::cout<<"Line did not pass: "<<curLine<<std::endl;
    }
    inputFile.close();
}

void runCommands(std::string outFileName,PriorityQueue &codes, PriorityQueue& commands){
    std::ofstream outputting;
    outputting.open(outFileName);
    std::string currCommand;
    std::string currCode;
    while(!commands.isEmpty()){
        currCommand=commands.deQueue();
        if(currCommand.find("DECODE")!=-1){
            codes.enQueue(currCommand.substr(currCommand.find('[')+1,currCommand.find(']')-currCommand.find('[')-1));
            continue;
        }
        if(codes.isEmpty())
            continue;
        currCode=codes.deQueue();
        if(currCommand.find("REPLACE:")!=-1)
            currCode=replace(currCode, currCommand[currCommand.find(',')-1],currCommand[currCommand.find(',')+1]);
        else if(currCommand.find("ADD:")!=-1)
            currCode=add(currCode, currCommand[currCommand.find(',')-1],currCommand[currCommand.find(',')+1]);
        else if(currCommand.find("REMOVE")!=-1)
            currCode=remove(currCode, currCommand[currCommand.find('[')+1]);
        else if(currCommand.find("SWAP")!=-1)
            currCode=swap(currCode, currCommand[currCommand.find(',')-1],currCommand[currCommand.find(',')+1]);
        if(currCommand.find("PRINT")!=-1)
            outputting<<currCode<<std::endl;
        else
            codes.enQueue(currCode);
    }
}

std::string replace(std::string str, char oldChar, char newChar){
    std::string temp="";
    for(int i=0;i<str.length();i++){
        if(str[i]==oldChar)
            temp+=newChar;
        else
            temp+=str[i];
    }
    return temp;
}

std::string add(std::string str, char ch, char adding){
    std::string temp="";
    for(int i=0;i<str.length();i++){
        temp+=str[i];
        if(str[i]==ch)
            temp+=adding;
    }
    return temp;
}

std::string remove(std::string str, char skip){
    std::string temp="";
    for(int i=0;i<str.length();i++){
        if(str[i]!=skip)
            temp+=str[i];
    }
    return temp;
}

std::string swap(std::string str, char char1, char char2){
    std::string temp="";
    for(int i=0;i<str.length();i++){
        if(str[i]==char1)
            temp+=char2;
        else if(str[i]==char2)
            temp+=char1;
        else
            temp+=str[i];
    }
    return temp;
}

#endif