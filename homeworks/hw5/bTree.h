#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <algorithm>
#include <fstream>
struct node{
    node** children;
    int* value;
    int degree;
    int curNumValues;
    node(){
        value=nullptr;
        children=nullptr;
    }
    node(int deg){
        degree=deg;
        children= new node*[deg+1];
        value= new int[deg];
        curNumValues=0;
        for(int i=0;i<=deg;i++){
            children[i]=nullptr;
            if(i<deg)
                value[i]=0;
        }
    }
};

class bTree{
private:
    node* source;
    int nodeDegree;
    void destructorHelper(node*&);
public:
    bTree();
    bTree(int);
    ~bTree();
    node*& getSource();
    node* peekSource();
    void addToBTree(node*&, int);
    void setDegree(int);
    int getDegree();
    int findHeight(node* cosnt);
};

#endif