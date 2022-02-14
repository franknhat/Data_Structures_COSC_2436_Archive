#include "AVL.h"

AVL::AVL(){
    root=nullptr;
}

void AVL::DestructorHelper(node*& cur){
    if(cur==nullptr)
        return;
    DestructorHelper(cur->left);
    DestructorHelper(cur->right);
    delete cur;
}

AVL::~AVL(){
    DestructorHelper(root);
}

node*& AVL::getRoot(){
    return root;
}

node* AVL::insertValue(node*& cur, int val, node* par){
    if(cur==nullptr){
        cur=new node(par,val);
        return cur;
    }
    else if(val<cur->value)
        return insertValue(cur->left, val, cur);
    else if(val>cur->value)
        return insertValue(cur->right, val, cur);
    else //if val==cur->val
        return nullptr;
}

void AVL::insert(int val){
    node* cur=insertValue(root, val);
    if(cur==nullptr)
        return;
    int balance;
    while(cur!=nullptr){
        balance=getHeight(cur->left)-getHeight(cur->right);
        //std::cout<<"node "<<cur->value<<"'s bal:"<<balance<<std::endl;
        if(balance<=-2){ //more on right side than left
            if((getHeight(cur->right->left)-getHeight(cur->right->right))<0)
                cur==root?cur=leftR(root):cur->value<cur->parent->value?cur->parent->left=leftR(cur):cur->parent->right=leftR(cur);
            else
                cur==root?cur=rightLeftR(root):cur->value<cur->parent->value?cur->parent->left=rightLeftR(cur):cur->parent->right=rightLeftR(cur);
            cur=cur->right;
        }
        else if(balance>=2){
            if((getHeight(cur->left->left)-getHeight(cur->left->right))<0)
                cur==root?cur=leftRightR(root):cur->value<cur->parent->value?cur->parent->left=leftRightR(cur):cur->parent->right=leftRightR(cur);
            else
                cur==root?cur=rightR(root):cur->value<cur->parent->value?cur->parent->left=rightR(cur):cur->parent->right=rightR(cur);
            cur=cur->left;
        }
        else
            cur=cur->parent;
    }
}

int AVL::getHeight(node* cur){
    return (cur==nullptr?-1:1+std::max(getHeight(cur->left),getHeight(cur->right)));
}

node* AVL::leftR(node*& cur){
    node* temp=cur;
    cur=cur->right;
    cur->parent=temp->parent;
    temp->parent=cur;
    temp->right=cur->left;
    cur->left=temp;
    return cur;
}

node* AVL::rightR(node*& cur){
    node* temp=cur;
    cur=cur->left;
    cur->parent=temp->parent;
    temp->parent=cur;
    temp->left=cur->right;
    cur->right=temp;
    return cur;
}

node* AVL::leftRightR(node*& cur){
    cur->left=leftR(cur->left);
    cur=rightR(cur);
    return cur;
}

node* AVL::rightLeftR(node*& cur){
    cur->right=rightR(cur->right);
    cur=leftR(cur);
    return cur;
}

void AVL::printTree(node* const cur){
    if(cur==nullptr)
        return;
    printTree(cur->left);
    std::cout<<cur->value<<" ";
    printTree(cur->right);
    if(cur==root)
        std::cout<<std::endl;
}