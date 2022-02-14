#ifndef AVL_H
#define AVL_H

#include <algorithm>
#include <iostream>

struct node{
    node* left;
    node* right;
    node* parent;
    int value;
    node(node* par,int val){
        left=right=nullptr;
        value=val;
        parent=par;
    }
};

class AVL
{
private:
    node* root;
    void DestructorHelper(node*&);
    //node* insertValue(node*&, int, node* par=nullptr);
public:
    AVL();
    ~AVL();
    node* insertValue(node*&, int, node* par=nullptr);
    node*& getRoot();
    void insert(int);
    node*& largetLeft(node*);
    node* leftR(node*&);
    node* rightR(node*&);
    node* leftRightR(node*&);
    node* rightLeftR(node*&);
    int getHeight(node* const);
    void printTree(node* cosnt);
};

#endif