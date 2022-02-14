#include "LinkedList.h"

LinkedList::LinkedList(){
  head = tail =nullptr;
  size = 0;
}

LinkedList::~LinkedList(){
  node* cur=head;
  while(!isEmpty()){
    head=head->next;
    delete cur;
    cur=head;
  }
}

void LinkedList::addInOrder(string data, node* cur){
  if (isEmpty()||stoll(data)<stoll(head->id)){ //if empty or head->data > id add to front
    if(isEmpty()){
      head=tail=new node(data, nullptr, nullptr);
    }
    else{
      node* temp=new node(data, nullptr, head);
      head->prev=temp;
      head=temp;
    }
    size++;
    return;
  }
  else if(cur==nullptr){
    node* temp=new node(data, tail, nullptr);
    tail->next=temp;
    tail=temp;
    size++;
  }
  else if (stoll(cur->id)==stoll(data))
    return;
  else if(stoll(data)<stoll(cur->id)){
    node* temp=new node(data,cur->prev,cur);
    cur->prev->next=temp;
    cur->prev=temp;
    size++;
  }
  else
    addInOrder(data, cur->next);
}

void LinkedList::removeDuplicate(string data,node* cur){
  if(cur==nullptr)
    return;
  if(stoll(cur->id)==stoll(data)){
    if(cur==head && cur==tail)
      head=tail=nullptr;
    else if(cur==head){
      head=head->next;
      head->prev=nullptr;
    }
    else if(cur==tail){ 
      tail=tail->prev;
      tail->next=nullptr;
    }
    else{
      cur->next->prev=cur->prev;
      cur->prev->next=cur->next;
    }
    delete cur;
  }
  else if (cur -> next == nullptr)
    return;
  else
    removeDuplicate(data, cur->next);
}

bool LinkedList::isFound(string data, node* cur){
  if(cur==nullptr)
    return false;
  else if (stoll(cur->id)==stoll(data))
    return true;
  return isFound(data, cur->next);
}

void LinkedList::outputToFile(ofstream &output_, node* cur){ 
  if(cur!=nullptr){
    output_ << cur->id<<endl;
    outputToFile(output_, cur->next);
  }
}