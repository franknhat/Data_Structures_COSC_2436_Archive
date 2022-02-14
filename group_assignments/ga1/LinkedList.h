#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <fstream>
#include <string>
using namespace std;

struct node{
    node* next;
    string id;
    node* prev;
    node(){next=prev=nullptr; id="";}
    node(string data, node* prev_, node* next_){id=data;next=next_;prev=prev_;}
};

class LinkedList{
private:
    node* head;
    node* tail;
    int size;
public:
    LinkedList();
    ~LinkedList();
    node* getHead(){return head;}
    node* getTail(){return tail;}
    int getSize(){return size;}
    bool isEmpty(){return head==nullptr;}
    void addInOrder(string, node*);
    void removeDuplicate(string, node*);
    void outputToFile(ofstream &, node* );
    bool isFound(string, node*);
};
#endif