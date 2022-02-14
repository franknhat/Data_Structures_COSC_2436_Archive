#ifndef GAMEDATALIST_H
#define GAMEDATALIST_H

#include <iostream>
#include <fstream>

struct GameData{
    std::string name;
    int score;
    GameData* next;
};

class GameDataList
{
private:
    GameData* head;
public:
    GameDataList();
    void addOrder(std::string, int);
    void outputToFile(std::string);
    void print();
    ~GameDataList();
};

#endif