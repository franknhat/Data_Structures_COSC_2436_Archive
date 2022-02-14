#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Node{
  Node* left;
  Node* right;
  int num;
};

class BST{
  private:
    Node* root;
  public:
    BST() {root = nullptr;}
    bool isEmpty();
    Node*& getRoot();
    Node* insertBST(Node*&,int);
    void TraversePreOrder(Node*,ofstream& output);
    string getSteps(Node*,string& s,int);
};



