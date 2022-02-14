#ifndef BOOK_H
#define BOOK_H

#include <string>

class book{
private:
    std::string genre;
    std::string title;
    std::string author;
    std::string year; //decided to make year a string over into to just make it easier. Like in usuage of that dynamic arrays of commands of strings its far more convienent to just keep it as string
    bool validBook;
public:
    book();
    book(std::string genre_,std::string title_, std::string writer, std::string yr);
    std::string getType();
    std::string searchCommand(int i);
    bool isBook();
    void erase();
    book &operator=(const book RHS);
    std::string const getGenre();
    std::string const getTitle();
    std::string const getAuthor();
    std::string const getYear();
};

#endif