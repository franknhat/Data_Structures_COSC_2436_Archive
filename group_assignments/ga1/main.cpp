#include "ArgumentManager.h"
#include "functions.h"

int main(int argc, char* argv[]){
  ArgumentManager am(argc, argv);
  string inputFileName=am.get("input");
  string outputFileName=am.get("output");

  LinkedList Bar1, Bar2, hoes; //hoes==guilty. I just prefer code that I can sorta understand so in functions.h you wont find hoes I call it guilty
  
  inputFromBars(inputFileName, hoes, Bar1, Bar2);
  outputResults(outputFileName, hoes, Bar1, Bar2);
  return 0; 
}