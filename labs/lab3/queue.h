#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <fstream>
#include <string>
struct node{
    node* next;
    std::string textbook;
};

class queue{
private:
    node* begining;
    node* endQueue;
public:
    queue();
    ~queue();
    void addQueue(std::string);
    std::string dequeue();
    bool isEmpty();
    std::string peek();
};

#endif