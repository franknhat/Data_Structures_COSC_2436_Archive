#include <iostream>
#include <stack>
#include <fstream>
#include <string>

//used the stack library, as the TA said it was okay to use it.
using namespace std;


// finds a phase in a string.
size_t finder(string str,string phrase){
  size_t found = str.find(phrase);
  return found;
}

// part of evaluating postfix.
int evaluation(int a, int b, int key)
{
    int ans;
    switch(key)
    {
    case 1:
        ans = a + b;
        break;
    case 2:
        ans = a - b;
        break;
    default:
        break;
    }
    return ans;
}


// checks if a char is an operator
bool isOperator(char c){
  if(c == '+' || c == '-'){
    return true;
  }
    return false;
  
}

 // check if a char is open parenthesis
bool isPara(char c){
  if(c == '{' || c == '(' || c == '['){
    return true;
  }
    return false;
}

 // check if a char is closed parenthesis
bool isClosed(char c){
  if(c == '}' || c == ')' || c == ']'){
    return true;
  }
    return false;
}


// checks if an expression is valid (matching parenthesis)
bool isValid(string s){
  stack <char> stk;
  for(int i = 0; i < s.length();i++){
    if(s[i] == '[' || s[i] == '(' || s[i] == '{'){
      stk.push(s[i]);
    }
    else if(s[i] == ']' || s[i] == ')' || s[i] == '}'){
      switch(s[i]){
        case ']':
          if(stk.top() != '['){
            return false;
          }
          stk.pop();
          break;
        case '}':
          if(stk.top() != '{'){
            return false;
          }
          stk.pop();
          break;
        case ')':
          if(stk.top() != '('){
            return false;
          }
          stk.pop();
          break;
      }
    }
  }
  if(stk.empty()){
    return true;
  }
  else{
    return false;
  }



}


// needed to sort an array, you will see why later down in the code.
void BubbleSort(size_t a[], int size){
  for(int i = 0; i < size - 1;i++){
    for(int j = i + 1;j < size;j++){
      if(a[i] < a[j]){
        swap(a[i],a[j]);
      }
    }
  }
  
}


// checks if there is a place where distribtuion is needed in the string.
bool needToDistribute(string s){
  size_t exp1 = finder(s, "+(");
  size_t exp2 = finder(s, "+{");
  size_t exp3 = finder(s, "+[");
  size_t exp4 = finder(s, "-(");
  size_t exp5 = finder(s, "-{");
  size_t exp6 = finder(s, "-[");

  if(exp1 != string::npos || exp2 != string::npos || exp3 != string::npos || exp4 != string::npos || exp5 != string::npos || exp6 != string::npos){

    return true;
  }
    return false;
}


// removes a char in a string (this is for when you want to remove an operator after distributing).
string removeChar(string s, int index){
  string newStr;
  for(int i = 0; i < s.length();i++){
    if(i == index){
      continue;
    }
    else{
      newStr += s[i];
    }
  }
  return newStr;


}

// There was one expression where the parenthesis were giving me trouble, so i just decided to remove all the parenthesis). (I made sure it doesnt affect the equation).
string removeExtraPara(string s){
  for(int i = 0; i < s.length();i++){
    if(isPara(s[i]) || isClosed(s[i])){
      s = removeChar(s, i);
    }
  }
  return s;
}

// Adds a '+' or '-' to a string when needed since distribuing means I have to add or change an operator.
string addToStr(string s, char c, int index){
  string newStr = "";
  if(index == 0){
    newStr = c + s;
  }
  else if(index == s.length()){
    newStr = s + c;
  }
  else{
    int currIndex = 0;
    while(currIndex != index){
      newStr += s[currIndex];
      currIndex++;
    }
  
    
    newStr = newStr + c + s[currIndex];
    currIndex++;
    string restOfStr = s.substr(currIndex);
    newStr += restOfStr;
  }
  return newStr;


}



// Recursivly distributes the equations with a '-' or '+' before a parenthesis.(This was so AIDS).
string distribute(string s){
  if(!needToDistribute(s)){
    return s;
  }
  else{
  

    size_t exp1 = finder(s, "+(");
    size_t exp2 = finder(s, "+{");
    size_t exp3 = finder(s, "+[");
    size_t exp4 = finder(s, "-(");
    size_t exp5 = finder(s, "-{");
    size_t exp6 = finder(s, "-[");


   //(Made this function recurisve since the finder function will only take the first occurence of a certain index where distribution is needed. Example: a+b-(A+1)-(-3-B) <- in this expression it will only find the first '-('.

   // the array will hold all the indicies where distribution is needed.
    size_t arr[] = {exp1,exp2,exp3,exp4,exp5,exp6};
    // sorts so the inner parenthesis is always being distributed first, if there is any, is alwasy distributed first.
    BubbleSort(arr,6);
    
    for(int i = 0; i < 6;i++){
      if(arr[i] != string::npos){
        char op = s[arr[i]];
        int indexOp = arr[i];
        int indexPara = arr[i] + 1;
        // this is to deal with the cases where '+' is the first element in an equation. As this results in an invalid postfix form. Ex: +(a+b-A-1+3+B) 
        if(arr[i] == 0){
          bool firstDigit = true;  // will ignore adding a '+' if it is the first digit of the equation. 
          if(op == '+'){
            int j = arr[i] + 2;
            while(!isClosed(s[j])){
              if(isdigit(s[j])){
                if(firstDigit){
                  firstDigit = false;   
                }
                else{
                  s = addToStr(s, '+', j);
                  j++;
                }
              }
              else if(s[j] == '+'){
                j++;
              
              }
              else if(s[j] == '-'){
                j++;
            
              }
            
              j++;


            
            }
            int indexClosed = j;
            // these three lines just gets rid of the parenthesis and the distributed operator, after distribution was complete.
            s = removeChar(s,indexClosed);   
            s = removeChar(s,indexPara - 1);
            s = removeChar(s, arr[i]);
          }
          
          
        }

        else if(op == '+'){
          int j = arr[i] + 2;
          while(!isClosed(s[j])){
            if(isdigit(s[j])){
              s = addToStr(s, '+', j);
              j++;
            }
            else if(s[j] == '+'){
              j++;
              
            }
            else if(s[j] == '-'){
              j++;
            
            }
            
            j++;


            
          }
          int indexClosed = j;

          s = removeChar(s,indexClosed);
          s = removeChar(s,indexPara - 1);
          s = removeChar(s, arr[i]);
        }
        else if(op == '-'){
          int j = arr[i] + 2;
          while(!isClosed(s[j])){
            if(isdigit(s[j])){
              s = addToStr(s, '-', j);
              j++;
            }
            else if(s[j] == '+'){
              s[j] = '-';
              j++;
              
            }
            else if(s[j] == '-'){
              s[j] = '+';
              j++;
            
            }
            j++;


            
          }
          int indexClosed = j;

          s = removeChar(s,indexClosed);
          s = removeChar(s,indexPara - 1);
          s = removeChar(s, arr[i]);
          
        
          
        }
      }
    }


    return distribute(s); 
    
    /*Recursivly calls distribute again until there is no need to distribute anymore. Ex: a+b-(A+1)-(-3-B)
      after first call to distribute, the equation will look like this, a+b-A-1-(-3-B)

      Since there is still a need to distribute, the fuction will continue to call itself, until it looks like this, a+b-A-1+3+B
    
    */

  




    
    
  }
  

}


// transforms to postfix so we dont have to worry bout parenthesis. (I later decided to get rid of parenthesis completely), so there is some unecessary steps.
string InfixtoPostfix(string s)
{ 
 string postfix = "";
 stack <char> stk;
 for(int i = 0; i < s.length();i++){
   if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] - '0' >= 0 && s[i] - '0' <= 9)){
     postfix += s[i];
   }
   else if(isPara(s[i])){
     stk.push(s[i]);
   }
   else if(isClosed(s[i])){
     if(s[i] == ')'){
       while(stk.top() != '('){
         postfix += stk.top();
         stk.pop();
       }
       stk.pop();
     }
     if(s[i] == ']'){
       while(stk.top() != '['){
         postfix += stk.top();
         stk.pop();
       }
       stk.pop();
     }
     if(s[i] == '}'){
       while(stk.top() != '{'){
         postfix += stk.top();
         stk.pop();
       }
       stk.pop();
     }



   }
   else{
      if(stk.empty()){
        stk.push(s[i]);
      }
      else{
        if(isPara(stk.top())){
          stk.push(s[i]);
        }
        else{
        postfix += stk.top();
        stk.pop();

        if(stk.empty()){
          stk.push(s[i]);
          continue;
        }

        while(isOperator(stk.top())){
          postfix += stk.top();
          stk.pop();
          if(stk.empty()){
            break;
          }
        }
        stk.push(s[i]);
      }
      }



   }




 }
 while(!stk.empty()){
   postfix += stk.top();
   stk.pop();
 }

 return postfix;


}

// substitutes all the variables to a number so we can evaluate it.
string convertToNums(string s){
  for(int j = 0; j < s.length();j++){
    if((!isOperator(s[j])) && (!isdigit(s[j])) && (!isPara(s[j]) && (!isClosed(s[j])))){
      s[j] = '1';
    }

  }

  return s;
    
  


}


// evaluates the expression, which we can later use to find out if the expressions are similar.
int EvaluatePostfix(string s)
{
    stack <char> stk;
    for(int i = 0; i < s.length();i++)
    {
        if(isdigit(s[i]))
        {
            int val = s[i] - '0';
            stk.push(val);
        }
        else
        {
            int key;
            int int1;
            int int2;
            int2 = stk.top();
            stk.pop();
            int1 = stk.top();
            stk.pop();
            if(s[i] == '+')
                key = 1;
            if(s[i] ==  '-')
                key = 2;
  
            stk.push(evaluation(int1,int2,key));





        }

    }
    int finalAns = stk.top();
    stk.pop();
    return finalAns;
}
