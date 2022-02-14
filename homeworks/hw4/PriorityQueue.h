#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>
#include <fstream>
#include <string>

struct node{
    node* next;
    std::string data;
    int priority;
    node();
    node(std::string data_, int prio, node* n){data=data_; priority=prio; next=n;}
};

class PriorityQueue
{
private:
    node* front;
    node* end;
public:
    PriorityQueue();
    ~PriorityQueue();
    bool isEmpty();
    void enQueue(std::string, int prio=0);
    void enQueueByPriority(std::string, int);
    std::string deQueue();
    

    void testPrint();
};

#endif