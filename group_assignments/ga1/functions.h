#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stack>
#include <queue>
#include "LinkedList.h"

void addToGuilty(LinkedList&, LinkedList&, LinkedList&);
string decode(string);
void outputInnocent(ofstream&, node*, node*);

void inputFromBars(string inputFileName, LinkedList &Guilty,LinkedList &Bar1, LinkedList &Bar2){
  ifstream in;
  in.open(inputFileName);
  if(!in.is_open()){
    cerr << "Unable to open .txt file." << endl;
    exit(1);
  }

  string lineRead = "";
  bool fromBar1 = false;
  bool fromBar2 = false;

  while(!in.eof()){
    getline(in, lineRead);
    if(lineRead != ""){
      if(lineRead == "Bar1"){
        fromBar1 = true;
        fromBar2 = false;
      } else if(lineRead == "Bar2"){
        fromBar1 = false;
        fromBar2 = true;
      }     
      else if(fromBar1 == true && fromBar2 == false)
        Bar1.addInOrder(decode(lineRead),Bar1.getHead());
      else if(fromBar1 == false && fromBar2 == true)
        Bar2.addInOrder(decode(lineRead),Bar2.getHead());
    }
  }
  in.close();
  addToGuilty(Guilty, Bar1, Bar2);
}

void addToGuilty(LinkedList &guilty, LinkedList &Bar1, LinkedList &Bar2){
if(!Bar1.isEmpty()&& !Bar2.isEmpty()){
    node *curr = Bar1.getHead();
    node *curr2 = Bar2.getHead();
    string temp;
    while(curr != nullptr){
      if (Bar2.isFound(curr->id, curr2)){
        guilty.addInOrder(curr -> id, guilty.getHead());
        temp=curr->id;
        curr=curr->next;
        Bar1.removeDuplicate(temp, Bar1.getHead());
        Bar2.removeDuplicate(temp, Bar2.getHead());
        curr2=Bar2.getHead();
      }
      else
        curr = curr -> next;
    }
  }
}

void outputResults(string outputFileName, LinkedList &Guilty, LinkedList &Bar1, LinkedList &Bar2){ //I was getting errors if I didnt pass by reference
  ofstream outputting;
  outputting.open(outputFileName);

  if(!Guilty.isEmpty()){
    outputting<<"Guilty:"<<endl;
    Guilty.outputToFile(outputting, Guilty.getHead());
  }
  if(!Bar1.isEmpty() || !Bar2.isEmpty()){
    outputting<<"Innocent:"<<endl;
    outputInnocent(outputting, Bar1.getHead(), Bar2.getHead());
  }
  outputting.close();
}

string decode(string line){
  stack<char> st;
  for (int i = 0; i < line.length(); i++){
    if (line[i] != ')'){
      st.push(line[i]); //add to stack to easily access the top or parts added last mainly needed for ()
    }
    else{
      queue<char> q;
      while (st.top() != '('){ //add to queue then back to the stack to reverse it easily
        q.push(st.top());
        st.pop();
      }
      st.pop(); // pop '(' 
      while (!q.empty()){
        st.push(q.front());
        q.pop();
      }
    }
  }
  string dec = "";//string to return
  while (!st.empty()){
    dec= st.top()+ dec;
    st.pop();
  }
  return dec;
}

void outputInnocent(ofstream &output, node* bar1, node* bar2){
    if(bar1!=nullptr && bar2!=nullptr){ //when both are not empty since added in order only need to compare the curr nodes at a time
      if(stoll(bar1->id) < stoll(bar2->id)){
        output<<bar1->id<<endl;
        outputInnocent(output,bar1->next,bar2);
      }
      else{
        output<<bar2->id<<endl;
        outputInnocent(output,bar1,bar2->next);
      }
    }
    //when one of them are empty the other one just needs to output.
    else if(bar1!=nullptr){
      output<<bar1->id<<endl;
      outputInnocent(output,bar1->next,bar2);
    }
    else if(bar2!=nullptr){
      output<<bar2->id<<endl;
      outputInnocent(output,bar1,bar2->next);
    }
}

#endif