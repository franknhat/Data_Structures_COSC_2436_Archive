#ifndef LINESLIST_H
#define LINESLIST_H

#include <iostream>
#include <fstream>

struct lines{
    std::string linestr;
    lines *next;
};

class LinesList{
private:
    lines* head;
    int size; //this is good to keep track of since adding by position good to know
    void swap(lines*, lines*); //helper function for sort
public:
    LinesList();
    ~LinesList();
    void addtoBegin(std::string);
    void addtoEnd(std::string);
    void add(int, std::string);
    void remove(std::string);
    void sort(char);
    void fileoutput(std::string);
    bool isDuplicate(std::string);
};

#endif