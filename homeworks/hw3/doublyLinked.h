#ifndef DOUBLYLINKED_H
#define DOUBLYLINKED_H

#include <fstream>
#include <string>

struct fixNode{
    fixNode* next;
    fixNode* prev;
    std::string equation;
    std::string type;
};

class FixedLL{
private:
    fixNode* head;
    fixNode* tail;
    int size;
public:
    FixedLL();
    ~FixedLL();
    int getSize();
    bool isEmpty();
    void print(std::ofstream&);
    void printBackwards(std::ofstream&);
    void push(std::string, std::string);
    void insertPos(std::string, std::string, int);
    void removeNode(fixNode*);
    fixNode* getHead();
    void removeType(std::string);
    void removePos(int);
};

#endif