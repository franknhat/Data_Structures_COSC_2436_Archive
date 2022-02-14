#include "priorityQueue.h"

priorityQueue::priorityQueue(){
    front=nullptr;
}

priorityQueue::~priorityQueue(){
    node* toDel=front;
    while (front!=nullptr){
        front=front->next;
        delete toDel;
        toDel=front;
    }   
}

bool priorityQueue::isEmpty(){
    return front==nullptr;
}

void priorityQueue::addToOrder(std::string task_, double value_){ //adds by value if values are the smae then priority by what shows up first
    node* temp=new node; //str double node
    temp->task=task_;
    temp->value=value_;
    temp->next=nullptr;
    if(front==nullptr || front->value>temp->value){
        if(!isEmpty())
            temp->next=front;
        front=temp;
    }
    else{
        node* cur=front;
        while(cur->next!=nullptr){ //stops at tail
            if (cur->next->value>value_){
                temp->next=cur->next;
                cur->next=temp;
                return;
            }
            cur=cur->next;
        }
        cur->next=temp; //means value > all other values and stops AT tail;
    }
} 

void priorityQueue::print(){
    node* cur=front;
    while(cur!=nullptr){
        std::cout<<cur->task<<"  "<<cur->value<<std::endl;
        cur=cur->next;
    }
}

void priorityQueue::outputToFile(std::string filename){
    std::ofstream output;
    output.open(filename);
    node* cur=front;
    while(cur!=nullptr){
        output<<cur->task<<std::endl;
        cur=cur->next;
    }
    output.close();
}