#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "bTree.h"
#include <queue>

void printLevel(node* , int, std::ofstream&, int curHeight=1);

void insertToTree(bTree &tree, std::ifstream &command, std::string inFileName){
    std::string curLine;
    std::ifstream input(inFileName);
    
    command>>curLine;
    tree.setDegree(stoi(curLine.substr(curLine.find('=')+1)));
    
    while(!input.eof()){
        input>>curLine;
        if(curLine!="" &&curLine!=" " && curLine!=" ")
            tree.addToBTree(tree.getSource(),stoi(curLine));
    }

    input.close();
}

void runCommand(bTree tree, std::ifstream &command, std::string outputFileName){
    std::ofstream output(outputFileName);
    std::string curLine;
    std::queue<node *> q;

    int height=tree.findHeight(tree.getSource());
    output<<"Height="<<height<<std::endl;
    while(!command.eof()){
        std::getline(command, curLine);
        curLine=curLine.substr(curLine.find(" ")+1);
        if(curLine!="" && curLine!=" "){
            if(stoi(curLine)>height)
                output<<"EMPTY"<<std::endl;
            else
                printLevel(tree.getSource(), stoi(curLine), output);
            output<<std::endl;
        }
        
    }

    command.close();
    output.close();
}

void printLevel(node* cur, int level, std::ofstream &output, int curHeight){
    if(cur==nullptr)
        return;
    if(curHeight==level){
        for(int i=0;i<cur->curNumValues;i++)
            output<<cur->value[i]<<" ";
        return;
    }
    else if(curHeight<level){
        for(int i=0;i<=cur->curNumValues;i++){
                printLevel(cur->children[i],level, output,curHeight+1);
        }
    }
}

#endif