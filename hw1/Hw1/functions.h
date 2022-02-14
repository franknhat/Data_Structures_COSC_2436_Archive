#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <fstream>
#include <iostream>
#include "book.h"

int numBooks=0;
book *books= new book [numBooks];

std::string** commands=new std::string*[4]; //create a 2d dynamic array later for the commands with the first index representing the command type genre title author year
int cmdcounter[4]={0,0,0,0}; //keep count for the number of commands per index/command type

template <typename T> //This is to dynamically change the size of the array by one so I do not have to create two arrays of 10000 for the lines entered and books
void arrayAdd1Element(T* &array, int &counter){
    T *temp= new T[counter+1]; //creating a temp dynamic array wise size+1 of tocopy
    for (int i=0;i<counter;i++) //deep copy original oarray of what should have information
        temp[i]=array[i];
    delete[] array; //deleting the array
    array=temp;
    counter++;
}

void createbooks(std::string bookline, int titlepos_, int authorpos_, int yearpos_); //I just like it better when the functions are in order of usuage this needs to be defined before Input format since this function is being used in the input format function
void removeSpaces(std::string &str);

void InputFormat(std::string InputName){
    std::string validbook;
    std::string *lines=new std::string[0]; //array to store the input lines from the files
    int count=0;
    std::ifstream inFile(InputName);
    if (inFile.is_open()){
        while (!inFile.eof()){
            arrayAdd1Element<std::string>(lines,count);
            getline(inFile, lines[count-1],'\n'); //doing count-1 since the template function from prev line adds one to the count
        }
    }
        inFile.close();
        for (int i=0;i<count;i++)
            removeSpaces(lines[i]);
        for (int i=0;i<count;i++){
            if (lines[i].find("genre")==1 && lines[i].find("title")>1 && lines[i].find("author")>lines[i].find("title") && lines[i].find("year")>lines[i].find("author")){ //finding them and seeing if in order
                arrayAdd1Element<book>(books,numBooks);
                validbook=lines[i];
                createbooks(validbook, lines[i].find("title"), lines[i].find("author"), lines[i].find("year"));
            }
        }
    delete[] lines;
}

void createbooks(std::string bookline, int titlepos_, int authorpos_, int yearpos_){
    std::string genre, title, author, year;
    genre=bookline.substr(7,titlepos_-8); //title pos-8 is the length of the genre 7 is the length of "{genre:" -8 instead of 7 to account for the comma
    title=bookline.substr(titlepos_+6,authorpos_-(titlepos_+7)); //title pos_+6 to account for length of "title:" titlepos-(authorpos+8) 8 accounts for length of "title:" and the comma at the end
    author=bookline.substr(authorpos_+7,yearpos_-(authorpos_+8)); //similar explainaation to previous
    year=bookline.substr(yearpos_+5,4); //+5 for year: and year is length of 4 so just 4 is fine stoi since I made the year int in my book class 
    for (int i=0;i<numBooks;i++){ //finds next available nullptr to add new book class
        if (books[i].isBook()==false){
            books[i]= book(genre, title, author, year);
            break;
        }
    }
}

void removeSpaces(std::string &str){
    int count = 0; //counts nonwhite spaces
    for (int i = 0; i<str.length(); i++){
        if (str[i] != ' '){
            str[count] = str[i]; //changing string to how it would be without white spaces count is always <=i so wont be issue with multiple white spaces
            count++;
        }
    }
    str[count] = '\0'; //marking end of the string
}

void CommandManager(std::string CommandName){
    std::string *Commandlines= new std::string[0];
    int numlines=0;
    for(int i = 0; i < 4; ++i)//a twod dynamic array with first index 0-3 (size 4) representing genre,title,author, and year respectivly and the second index represents the "command" for that category if any
        commands[i] = new std::string[0];
    std::fstream inFile(CommandName);
     if (inFile.is_open()){
        while (!inFile.eof()){
            arrayAdd1Element<std::string>(Commandlines,numlines);
            getline(inFile, Commandlines[numlines-1],'\n'); //doing count-1 since the template function from prev line adds one to the count
        }
     }
    inFile.close();
    for(int i=0;i<numlines;i++){
        switch (Commandlines[i][0]){ //under the assumption that the commands are spelt correctly this looks at the first letter using switch rather than .find() 4 times to see what it contains
        case 'g': //if genre append to commands[0] my dynamic array for genres
            arrayAdd1Element<std::string>(commands[0],cmdcounter[0]);
            commands[0][cmdcounter[0]-1]=Commandlines[i].substr(6); //cmd counter -1 since cmdcounter is the size of the array have to -1 since u cant for ex access arry[1] in an array of size 1
            break;
        case 't':
            arrayAdd1Element<std::string>(commands[1],cmdcounter[1]);
            commands[1][cmdcounter[1]-1]=Commandlines[i].substr(6);//also the substr(length of command type) is hard coded since it under the assumption there are no errors within the commands so I hard coded the length of each type so I hard coded the start of the string (info of the command type)
            break;
        case 'a':
            arrayAdd1Element<std::string>(commands[2],cmdcounter[2]);
            commands[2][cmdcounter[2]-1]=Commandlines[i].substr(7);
            break;
        case 'y':
            arrayAdd1Element<std::string>(commands[3],cmdcounter[3]);
            commands[3][cmdcounter[3]-1]=Commandlines[i].substr(5);
            break;
        default: //it should never get here I have this here to avoid the warning on the server
            break;
        }
    }
    delete [] Commandlines; //dont need anymore now that the commands are stored in commands 2d array
}

void runCommands(){
    for (int i=0; i<numBooks;i++){
        for (int j=0;j<4;j++){
            for (int k=0;k<cmdcounter[j];k++){
                if(books[i].searchCommand(j)== commands[j][k] || cmdcounter[j]==0) //if found break from individual command loop to the next command type
                    break;
                else if(books[i].searchCommand(j)!=commands[j][k] && k==cmdcounter[j]-1) //if book does not match any of the commands in the command array, delete/erase the book
                    books[i].erase();
            }
        }
    }
}

void outputBooks(std::string outputName){
    ofstream outFile;
    outFile.open(outputName);
    for (int i=0;i<numBooks;i++){
        if(books[i].isBook()==true) //since my erase function just erases values in book, if book has values it outputs into the file
            outFile<<"{genre:"<<books[i].getGenre()<<",title:"<<books[i].getTitle()<<",author:"<<books[i].getAuthor()<<",year:"<<books[i].getYear()<<"}"<<std::endl;
    }
    outFile.close();
    delete [] books;
    for(int i=0;i<4;i++) 
        delete[] commands[i];    
    delete[] commands;
}

#endif