#include "book.h"

book::book(){
    genre="";
    title="";
    author="";
    year="";
    validBook=false;
}

book::book(std::string genre_,std::string title_, std::string writer, std::string yr){
    genre=genre_;
    title=title_;
    author=writer;
    year=yr;
    validBook=true;
}

book& book::operator=(book RHS){
    this->genre=RHS.genre;
    this->author=RHS.author;
    this->title=RHS.title;
    this->year=RHS.year;
    this->validBook=RHS.validBook;
    return *this;
}

std::string const book::getGenre(){
    return genre;
}

std::string const book::getTitle(){
    return title;
}

std::string const book::getAuthor(){
    return author;
}

std::string const book::getYear(){
    return year;
}

bool book::isBook(){
    return validBook; //erase the rest of this function other than this line
}

void book::erase(){ //technically can just set as invalid w/out erasing and change from erase to set invalid or sum
    genre="";
    title="";
    author="";
    year="";
    validBook=false;
}

std::string book::getType(){
    //if (validBook==true)
    return "book";
    //else
        //return "not a valid book";
    
} 

//might just erase this since it doesnt seem to be called anywhere else

std::string book::searchCommand(int i){
    switch (i){
    case 0:
        return getGenre();
        break;
    case 1:
        return getTitle();
        break;
    case 2:
        return getAuthor();
        break;
    case 3:
        return getYear();
        break;
    default: //this should never happen I just have this here to avoid warning on the server
        return "how did you get here?????";
        break;
    }
}