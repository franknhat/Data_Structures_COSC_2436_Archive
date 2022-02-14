#include "functions.h"

#include "ArgumentManager.h"

using namespace std;

int main(int argc, char* argv[]) {
  ArgumentManager am(argc, argv);
  string inputFileName=am.get("input");
  string outputFileName=am.get("output");

  ifstream checkValid(inputFileName);
  ofstream output(outputFileName);

  bool validFile = true;

  string currExp;
  int expNum = 0;
  // goes through the inputfile and makes sure every expression is valid.
  while(getline(checkValid,currExp)){
    if(currExp == ""){
      continue;
    }
    expNum++;
    if(!isValid(currExp)){
      output << "Error at: " << expNum << endl;
    }
    if(validFile){
      validFile = isValid(currExp);
    }
  }

  if(validFile){                    // if the file is valid, it checks to see if the equations are similar.
    bool isSimilar = true;
    int arr[expNum];                      //decided to store the answers to the expressions in an array.
    ifstream input(inputFileName);
    string currEq;
    int count = 0;
    while(getline(input,currEq)){
      if(currEq == ""){
        continue;
      }
      
      string equation = convertToNums(currEq);
  
     // for cases where the first element is '-' Ex: -(a+b-A-1+3+B); distributes by replacing the '-' to '+', and then multiplies the final answer by -1.
      if(equation[0] == '-'){                       
        equation[0] = '+';
        equation = distribute(equation);
        equation = removeExtraPara(equation);
        equation = InfixtoPostfix(equation);
        int val = EvaluatePostfix(equation);

        arr[count] = -1 * val;
        count++;

      


      }
      else{
        equation = distribute(equation);
        equation = removeExtraPara(equation);
        equation = InfixtoPostfix(equation);
        int val = EvaluatePostfix(equation);

        arr[count] = val;
        count++;

      }
      
      
    }
    int compareVal = arr[0];

    for(int i = 0; i < expNum;i++){  // comapares all the final answers checks if they are the same.
      if(arr[i] != compareVal){
        isSimilar = false;
      }   
    }

    if(isSimilar){
      output << "Yes" << endl;
    }
    else{
      output << "No" << endl;
    }
   
  } 


 






 




}






  

  
 






  


  




  





  
