#include "PriorityQueue.h"

PriorityQueue::PriorityQueue(){
    front=end=nullptr;
}

PriorityQueue::~PriorityQueue(){
    node* temp=front;
    while(front!=nullptr){
        front=front->next;
        delete temp;
        temp=front;
    }
    end=nullptr;
}

bool PriorityQueue::isEmpty(){
    return front==nullptr && end==nullptr;
}

void PriorityQueue::enQueueByPriority(std::string data_, int prio){
    if(front==nullptr || prio<front->priority){
        node* temp=new node(data_, prio, front);
        if(isEmpty())
            end=temp;
        front=temp;
    }
    else{
        node* cur=front;
        node* temp= new node(data_, prio, nullptr);
        while(cur->next!=nullptr){ //stops at tail
            if (cur->next->priority>prio){
                temp->next=cur->next;
                cur->next=temp;
                return;
            }
            cur=cur->next;
        }
        cur->next=temp; //means value > all other values and stops AT tail;
        end=temp;
    }
}

void PriorityQueue::enQueue(std::string data_, int prio){ //priority shouldnt matter when enQueue like a circular queue
    if(isEmpty()){
        front=end=new node(data_, prio, nullptr);
        return;
    }
    end->next=new node(data_, prio, nullptr);
    end=end->next;
}

std::string PriorityQueue::deQueue(){
    if(isEmpty())
        return "Empty";
    node* temp=front;
    std::string returnStr=front->data;
    if(front==end)
        front=end=nullptr;
    else
        front=front->next;
    temp->next=nullptr;
    delete temp;
    return returnStr;
}

void PriorityQueue::testPrint(){
    if(isEmpty()){
        std::cout<<"Empty"<<std::endl;
        return;
    }
    node* cur=front;
    while(cur!=nullptr){
        std::cout<<" | "<<cur->data<<" / "<<cur->priority;
        cur=cur->next;
    }
    std::cout<<" |"<<std::endl;
}