#include "bst.h"

bool BST::isEmpty(){
  if(root == nullptr){
    return true;
  }
    return false;
}

Node*& BST::getRoot(){
  return root;
}

Node* BST::insertBST(Node*& cu, int n){
  if(cu == nullptr){
    cu = new Node;
    cu->left = cu->right = nullptr;
    cu->num = n;
    if(isEmpty()){
      root = cu;
    }
    return cu;
  }
  else if(n > cu->num){
    cu->right = insertBST(cu->right, n);
  }
  else if(n < cu->num){
    cu->left = insertBST(cu->left, n);
  }
  return cu;
}

void BST::TraversePreOrder(Node* r,ofstream& output){
  if(isEmpty()){
    return;
  }
  
  if(r == nullptr){
    return;
  }
  else{
    string s = "";
    output << getSteps(root,s, r->num) + "] ";
    output << r->num << endl ;
    TraversePreOrder(r->left,output);
    
    TraversePreOrder(r->right,output);
  
  } 
}

string BST::getSteps(Node* r, string& s, int find){
  if(s == ""){
    s += "[x";
  }
  if(find == root->num){
    return s;
  }
  if(find > r->num){
    s += 'r';
    getSteps(r->right, s, find);
  }
  else if(find < r->num){
    s += 'l';
    getSteps(r->left, s, find);
  }
  return s;

}




