#include "GameDataList.h"

GameDataList::GameDataList(){
    head=nullptr;
}

void GameDataList::addOrder(std::string name_, int score_){
    GameData* temp=new GameData;
    temp->name=name_;
    temp->score=score_;
    temp->next=nullptr;
    if(head==nullptr){
        head=temp;
        return;
    }
    GameData* prev=nullptr;
    GameData* cu=head;
    while (cu!=nullptr){
        if (cu==head && temp->score>=cu->score){
            temp->next=head;
            head=temp;
            return;
        }
        else if (cu->next==nullptr && cu->score>=temp->score){
            cu->next=temp;
            return;
        }
        else if(temp->score>=cu->score){
            prev->next=temp;
            temp->next=cu;
            return;
        }
    prev=cu;
    cu=cu->next;
    }
}

void GameDataList::print(){
    GameData* cu=head;
    while (cu!=nullptr){
        std::cout<<cu->name<<","<<cu->score<<std::endl;
        cu=cu->next;
    }
    
}

void GameDataList::outputToFile(std::string outputName){
    std::ofstream output;
    output.open(outputName);
    GameData* cu=head;
    while (cu!=nullptr){
        output<<cu->name<<","<<cu->score<<std::endl;
        cu=cu->next;
    }
    if(head==nullptr){
        output<<"No valid data in input"<<std::endl;
    }
}

GameDataList::~GameDataList(){
    GameData* temp=head;
    while (head!=nullptr){
        head=head->next;
        delete temp;
        temp=head;
    }
}
