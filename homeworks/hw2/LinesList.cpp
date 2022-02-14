#include "LinesList.h"

LinesList::LinesList(){
    head=nullptr;
    size=0;
}

LinesList::~LinesList(){
    lines* current = head;
    while( head != nullptr ) {
        head=head->next;
        delete current;
    }
}

void LinesList::addtoBegin(std::string str){
    lines* temp=new lines;
    temp->linestr=str;
    temp->next= nullptr;
    if (head==nullptr)
        head=temp;
    else{
        temp->next=head;
        head=temp;
    }
    size++;
}

void LinesList::addtoEnd(std::string str){
    lines *temp= new lines;
    temp->linestr=str;
    temp->next=nullptr;
    if (head==nullptr){
        head=temp;
        size++;
        return;
    }
    lines * cu=head;
    while (cu->next!=nullptr){
        cu=cu->next;
    }
    cu->next=temp;
    size++;
}

void LinesList::add(int index, std::string str){
    if (index>size || index<0) //This first since its comparing two ints and not going thro the linked list if not real index
        return;
    if (isDuplicate(str)==true) //if finds a duplicate dont add
        return;
    if (index==0){
        addtoBegin(str);
    }
    else if (index==size){
        addtoEnd(str);
    }
    else{ //head cant be null ptr in this case cuz the size would be ==0 so it would call index or it will be too large to add
        lines* temp= new lines;
        lines* cu=head;
        temp->linestr=str;
        temp->next=nullptr;
        int pos=0;
        cu= head;
        for (int i=0;i<index;i++){//this should put it 1 berfore its desired index
            cu=cu->next;
        }
        temp->next=cu->next;
        cu->next=temp; // since cu is desired index-1 basically just placed temp at the desired index
        size++;
    }
}

void LinesList::remove(std::string str){
    lines* cu=head;
    lines* prev=nullptr;
    while(cu!= nullptr){
        if (cu->linestr.find(str)!=-1){
            if (cu==head){ //seprate senario since there is no prev to do ->= which could cause errors
                head=cu->next;
                delete cu;
                cu=head;
                size--;
            }
            else{
                prev->next=cu->next; //sets the next from prev to basically skip current (want to delete current)
                delete cu;
                cu=prev->next; //no need to change prev since we confirmed prev is fine
                size--;
            }
        }
        else{
        prev=cu;
        cu=cu->next;
        }
    }
    if (size==0) //although it may do it automatically when head gets deleted I feel like it will be good habbit to set it myself if it ==0
        head=nullptr;
}

void LinesList::swap(lines* cu, lines* prev){
    std::string temp; //this works lmao switching the data
    temp=cu->linestr;
    cu->linestr=cu->next->linestr;
    cu->next->linestr=temp;
}

void LinesList::sort(char type){ //l to organize by length a by alphabet
    bool exchanges;
    lines* cu;
    lines* prev;
    if (head==nullptr)
        return;
    do{
        exchanges=false;
        cu=head;
        prev=nullptr;
        while (cu->next!=nullptr){//while not at the last node
            if (type=='l'){
                if(cu->linestr.length()>cu->next->linestr.length()){
                    swap(cu,prev);
                    exchanges=true;
                }
            }
            else if (type=='a'){
                if(cu->linestr > cu->next->linestr){
                    swap(cu,prev);
                    exchanges=true;
                }
            }
            prev=cu;
            cu=cu->next;
        }
    } while (exchanges==true);
}

void LinesList::fileoutput(std::string outputName){
    std::ofstream output;
    output.open(outputName);
    lines* cu=head;
    while (cu!=nullptr){
        output<<cu->linestr<<std::endl;
        cu=cu->next;
    }
    output.close();
}

bool LinesList::isDuplicate(std::string searchstr){
    lines* cu=head;
    while (cu!=nullptr){
        if (cu->linestr==searchstr)
            return true;
        cu=cu->next;
    }
    return false;
}