#include "bst.h"
#include "ArgumentManager.h"

void doSomething(ifstream& input,ofstream& output,BST& T){
  int currNum;
  while(input >> currNum){
    T.insertBST(T.getRoot(),currNum);
  }
  T.TraversePreOrder(T.getRoot(),output);
} 


int main(int argc, char* argv[]) {
  ArgumentManager am(argc, argv);
  string inputFileName=am.get("input");
  string outputFileName=am.get("output");

  ifstream input(inputFileName);
  ofstream output(outputFileName);
  
  BST tree;

  doSomething(input, output, tree);
  
  input.close();
  output.close();
} 