#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "queue.h"

void addToFullDynArr(std::string* &darr, int &currSize, std::string const toAdd){
    std::string* temp= new std::string[currSize+1];
    for (int i=0;i<currSize;i++)
        temp[i]=darr[i];
    temp[currSize]=toAdd;
    currSize++;
    delete[] darr;
    darr=temp;
}

void createBookQueues(std::string filename,queue& Q1, queue& Q2){
    std::fstream BookQueuesFile;
    std::string Q1str;
    std::string Q2str;
    BookQueuesFile.open(filename);
    getline(BookQueuesFile, Q1str);
    getline(BookQueuesFile, Q2str);
    BookQueuesFile.close();
        while(Q1str.find(',')!=-1){ //while not at last book of str
            Q1.addQueue(Q1str.substr(0,Q1str.find(','))); //add first book
            Q1str=Q1str.substr(Q1str.find(',')+1); //remove that first book from str
        }
        Q1.addQueue(Q1str); //adds the last book since it wouldnt be added since comma wouldnt be found.
        while(Q2str.find(',')!=-1){
            Q2.addQueue(Q2str.substr(0,Q2str.find(',')));
            Q2str=Q2str.substr(Q2str.find(',')+1);
        }
        Q2.addQueue(Q2str);
}

void organizeBooks(std::string inputBooks,std::string* &shelfArr,int& numBooks,int &timeToOraganize){
    queue bookQueue1;
    queue bookQueue2;
    queue bookQueue3;
    createBookQueues(inputBooks, bookQueue1, bookQueue2);
    while (!bookQueue1.isEmpty() || !bookQueue2.isEmpty()){
        if (!bookQueue1.isEmpty()){
            if(bookQueue1.peek().find("compsci")!=-1){
                addToFullDynArr(shelfArr, numBooks, bookQueue1.dequeue());
                timeToOraganize+=20;
            }
            else{
                bookQueue3.addQueue(bookQueue1.dequeue());
                timeToOraganize+=10;
            }
        }
        if (!bookQueue2.isEmpty()){
            if(bookQueue2.peek().find("compsci")!=-1){
                addToFullDynArr(shelfArr, numBooks, bookQueue2.dequeue());
                timeToOraganize+=20;
            }
            else{
                bookQueue3.addQueue(bookQueue2.dequeue());
                timeToOraganize+=10;
            }
        }
    }
    while (!bookQueue3.isEmpty()){
        addToFullDynArr(shelfArr, numBooks, bookQueue3.dequeue());
        timeToOraganize+=20;
    }
}

void outputToFile(std::string outFileName,int const Time, std::string* const DynArr, int const size){
    ofstream outFile;
    outFile.open(outFileName);
    outFile<<Time<<std::endl;
    for (int i=0; i<size-1;i++){
        outFile<<DynArr[i]<<",";
    }
    outFile<<DynArr[size-1]<<std::endl;
}

#endif