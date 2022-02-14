#ifndef FUNCTION_H
#define FUNCTION_H

#include <queue>
#include "AVL.h"
#include <fstream>

void appendToTree(AVL &tree, std::string infilename){
    std::ifstream input(infilename);
    std::string numInput;
    std::string temp;
    
    input>>numInput;
    for(int i=0;i<stoi(numInput);i++){
        input>>temp;
        //std::cout<<temp<<std::endl;
        tree.insert(stoi(temp));
    }
    
    input.close();
}

void printLevelOrder(AVL* tree, std::string outfilename){
    std::ofstream output(outfilename);
    std::queue<node* > q;
    
    q.push(tree->getRoot());
    node* temp=nullptr;
    while(q.size()>0){
        temp=q.front();
        if(temp!=tree->getRoot())
            output<<" ";
        output<<temp->value;
        q.pop();
        if(temp->left!=nullptr)
            q.push(temp->left);
        if(temp->right!=nullptr)
            q.push(temp->right);
    }
    
    output.close();
}

#endif