#include "doublyLinked.h"

FixedLL::FixedLL(){
    head=tail=nullptr;
    size=0;
}

FixedLL::~FixedLL(){
    fixNode* cur=head;
    while (!isEmpty()){
        head=head->next;
        delete cur;
        cur=head;
        if (head==nullptr)
            tail=nullptr;
    }
    
}

bool FixedLL::isEmpty(){
    return (head==nullptr && tail==nullptr);
}

int FixedLL::getSize(){
    return size;
}

void FixedLL::print(std::ofstream& output_){
    output_<<"List:"<<std::endl;
    if(isEmpty())
        output_<<"EMPTY"<<std::endl;
    else{
        fixNode* curr=head;
        while(curr!=nullptr){
            output_<<curr->type<<":"<<curr->equation<<std::endl;
            curr=curr->next;
        }
    }
    output_<<std::endl;
}

void FixedLL::printBackwards(std::ofstream& output_){
    output_<<"Reversed List:"<<std::endl;
    if(isEmpty())
        output_<<"EMPTY"<<std::endl;
    else{
        fixNode* cur=tail;
        while(cur!=nullptr){
            output_<<cur->type<<":"<<cur->equation<<std::endl;
            cur=cur->prev;
        }
    }
    output_<<std::endl;
}

void FixedLL::push(std::string type_, std::string equation_){
    fixNode* temp = new fixNode;
    temp->equation=equation_;
    temp->type=type_;
    temp->next=temp->prev=nullptr;
    size++;
    if(isEmpty())
        head=tail=temp;
    else{
        tail->next=temp;
        temp->prev=tail;
        tail=temp;
    }
}

void FixedLL::insertPos(std::string type_, std::string equation, int pos){
    fixNode* temp= new fixNode;
    temp->equation=equation;
    temp->type=type_;
    temp->next=nullptr;
    temp->prev=nullptr;
    if (pos>=size)
        return;
    if (pos<=0 && isEmpty()){
        head=temp;
        tail=temp;
    }
    else if (pos<=0){
        temp->next=head;
        head->prev=temp;
        head=temp;
    }
    else if (pos==size-1){
        tail->next=temp;
        temp->prev=tail;
        tail=temp;
    }
    else{
        fixNode* cur=head;
        for (int i=0;i<pos-1;i++){
            cur=cur->next;
        }
        temp->next=cur->next;
        cur->next->prev=temp;
        cur->next=temp;
        temp->prev=cur;
    }
    size++;
}

fixNode* FixedLL::getHead(){
    return head;
}

void FixedLL::removeNode(fixNode* curr){
    if (curr==head && curr==tail){
        head=tail=nullptr;
    }
    else if (curr==head){
        head=head->next;
        head->prev=nullptr;
    }
    else if (curr==tail){
        tail=tail->prev;
        tail->next=nullptr;
    }
    else{
        curr->next->prev=curr->prev;
        curr->prev->next=curr->next;
    }
    delete curr;
    size--;
}

void FixedLL::removeType(std::string type_){
    fixNode* curr=head;
    if(type_=="all"){
        while (head!=nullptr){
            curr=head;
            head=head->next;
            delete curr;
            size--;
        }
        tail=nullptr;
    }
    else{
        fixNode* next;
        while (curr!=nullptr){
            next=curr->next;
            if(curr->type==type_)
                removeNode(curr);
            curr=next;
        }
    }
}

void FixedLL::removePos(int n){
    if (n>=size)
        return;
    else if(n<=0)
        n=0;
    fixNode* curr=head;
    for (int i=0;i<n;i++)
        curr=curr->next;
    removeNode(curr);
}