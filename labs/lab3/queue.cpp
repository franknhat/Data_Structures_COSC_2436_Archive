#include "queue.h"

queue::queue(){
    begining=endQueue=nullptr;
}

queue::~queue(){
    node* toDel= begining;
    while (!isEmpty()){
        if(begining==endQueue)
            endQueue=nullptr;
        begining=begining->next;
        delete toDel;
        toDel=begining;
    }
    begining=endQueue=nullptr;
}

bool queue::isEmpty(){
    return (begining==nullptr) && (endQueue==nullptr);
}

void queue::addQueue(std::string book_){
    node* newNode= new node;
    newNode->next=nullptr;
    newNode->textbook=book_;
    if (isEmpty()){
        begining=endQueue=newNode;
        return;
    }
    endQueue->next=newNode;
    endQueue=newNode;
}

std::string queue::peek(){
    if(!isEmpty()){
        return begining->textbook;
    }
    else
        throw __EXCEPTION__;
}

std::string queue::dequeue(){
    if(!isEmpty()){
        node* delNode=begining;
        std::string popped=delNode->textbook;
        if(begining==endQueue){
            endQueue=nullptr;
        }
        begining=begining->next;
        delete delNode;
        return popped;
    }
    else{
        throw __EXCEPTION__;
    }
}