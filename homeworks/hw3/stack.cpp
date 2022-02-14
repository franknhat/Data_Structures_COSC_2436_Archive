#include "stack.h"

template <typename T>
Stack<T>::Stack(){
    top=nullptr;
    size=0;
}

template <typename T>
Stack<T>::~Stack(){
    typeNode<T>* cur=top;
    while (!isEmpty())
        pop();
}

template <typename T>
bool Stack<T>::isEmpty(){
    return top==nullptr;
}

template <typename T>
typeNode<T>* Stack<T>::getTop(){
    return top;
}

template <typename T>
void Stack<T>::push(T const data_){
    typeNode<T>* temp = new typeNode<T>;
    temp->data=data_;
    temp->next=top;
    top=temp;
    size++;
}

template <typename T>
void Stack<T>::push(T const data1_, T  const data2_){
    typeNode<T>* temp = new typeNode<T>;
    temp->data=data1_;
    temp->data2=data2_;
    temp->next=top;
    top=temp;
    size++;
}

template <typename T>
T Stack<T>::pop(){
    typeNode<T>* popNode=top;
    T returnifEmpty;
    if(isEmpty())
        return returnifEmpty;
    T popped=popNode->data;
    top=top->next;
    delete popNode;
    size--;
    return popped;
}

template <typename T>
T Stack<T>::peek(){
    if(isEmpty()){
        T returnifEmpty;
        return returnifEmpty;
    }    
    return top->data;
}

template <typename T>
T Stack<T>::peek2(){
    T returnIfEmpty;
    if (isEmpty())
        return returnIfEmpty;
    return top->data2;
}

template <typename T>
int Stack<T>::getSize(){
    return size;
}

template <typename T> //this is a helper function solely for flip stack
void Stack<T>::setTopToNull(){ //need this or will seg fault with flip stack since it will delete the stack
    top=nullptr;
}

template <typename T>
void Stack<T>::flipstack(){
    Stack<T> temp;
    typeNode<T>* cur=top;
    while (top!=nullptr){
        temp.push(cur->data,cur->data2);
        top=top->next;
        delete cur;
        cur=top;
    }
    top=temp.getTop();
    temp.setTopToNull();
}