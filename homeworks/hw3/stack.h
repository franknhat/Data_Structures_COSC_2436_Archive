#ifndef STACK_H
#define STACK_H

template <typename T>
struct typeNode{
    T data;
    T data2; //only used in reserve stack
    typeNode* next;
};

template <typename T>
class Stack{
private:
    typeNode<T>* top;
    int size;
    void setTopToNull();//needed for flip so that it doesnt seg fault with destructor;
public:
    Stack();
    ~Stack();
    bool isEmpty();
    void push(T const);
    void push(T const,T const);
    T pop();
    T peek();
    T peek2();
    typeNode<T>* getTop();
    int getSize();
    void flipstack();
};

#endif