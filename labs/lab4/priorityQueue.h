#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <string>
#include <iostream>
#include <fstream>

struct node{
    node* next;
    double value;
    std::string task;
};

class priorityQueue
{
private:
    node* front;
public:
    priorityQueue();
    ~priorityQueue();
    bool isEmpty();
    void addToOrder(std::string, double);
    void print();
    void outputToFile(std::string);
};

#endif