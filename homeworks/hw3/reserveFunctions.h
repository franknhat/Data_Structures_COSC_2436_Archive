#ifndef RESERVEFUNCTIONS_H
#define RESERVEFUNCTIONS_H

#include "stack.cpp"
#include "doublyLinked.h"

void push_reserve_doubly(FixedLL & daList, Stack<std::string> &daStack, std::string how){
    if(how=="prefix" || how=="postfix"){
        fixNode* cur=daList.getHead();
        fixNode* todel;
        while(cur!=nullptr){
            if (cur->type==how){ //type equation
                daStack.push(cur->type,cur->equation);
                todel=cur;
                cur=cur->next;
                daList.removeNode(todel);
            }
            else
                cur=cur->next;
        }
    }
    else if (how=="all"){
        fixNode* cur=daList.getHead();
        fixNode* todel=cur;
        while (cur!=nullptr){
            daStack.push(cur->type,cur->equation);
            todel=cur;
            cur=cur->next;
            daList.removeNode(todel);
        }
    }
    else{
        if(!daList.isEmpty()){
            int index=stoi(how);
            if(index>=daList.getSize())
                return;
            else if (index<=0)
                index=0;
            fixNode* cur=daList.getHead();
            for (int i=0;i<index;i++)
                cur=cur->next;
            daStack.push(cur->type, cur->equation);
            daList.removeNode(cur);
        }
    }
}

void pop_reserve_doubly(FixedLL& dalist, Stack<std::string> &dastack, int pos){
    if(dastack.isEmpty())
        return;
    if (pos>=dalist.getSize())
        dalist.push(dastack.peek(),dastack.peek2());
    else
        dalist.insertPos(dastack.peek(),dastack.peek2(), pos);
    dastack.pop();
}

void emptyReserve(FixedLL& dalist, Stack<std::string> &dastack, int pos){
    bool addAtEnd=false;
    if (pos!=0 && pos>=dalist.getSize())
        addAtEnd=true;
    while(!dastack.isEmpty()){
        if (addAtEnd)
            dalist.push(dastack.peek(),dastack.peek2());
        else
            dalist.insertPos(dastack.peek(),dastack.peek2(),pos);
        dastack.pop();    
    }
}
#endif