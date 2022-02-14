#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <fstream>
#include <string>
#include "LinesList.h"

void inputManager(std::string inName, LinesList& LinkedList){
    ifstream inputLines;
    inputLines.open(inName);
    std::string inputstr;
    std::string inputcmd;
    getline(inputLines, inputcmd, '\n');
    while (!inputLines.eof()){
        getline(inputLines, inputstr, '\n'); 
        if (LinkedList.isDuplicate(inputstr)==false && inputstr!=""){
            if (inputcmd=="End")
                LinkedList.addtoEnd(inputstr);
            else //default to putting at the front so it can be sorted after if the command at the start was to sort
                LinkedList.addtoBegin(inputstr);
        }
    }
    inputLines.close(); 
    if (inputcmd== "Alphabetically")
        LinkedList.sort('a');
    else if (inputcmd== "Length")
        LinkedList.sort('l');
}

void runCommands(std::string cmdName, LinesList& LinkedList){
    ifstream cmdfile;
    std::string cmd;
    cmdfile.open(cmdName);
    while (!cmdfile.eof()){
        getline(cmdfile, cmd, '\n');
        if (cmd.find("Sort (length")!= -1)
            LinkedList.sort('l');
        else if (cmd.find("Sort (alphabetically)")!= -1)
            LinkedList.sort('a');
        else if (cmd.find("Add")!= -1)
            LinkedList.add(stoi(cmd.substr(cmd.find("(")+1,cmd.find(")")-cmd.find("(")-1)), cmd.substr(cmd.find("[")+1,cmd.find("]")-cmd.find("[")-1));
        else if (cmd.find("Remove")!= -1)
            LinkedList.remove(cmd.substr(cmd.find("[")+1,cmd.find("]")-cmd.find("[")-1));
    }
    cmdfile.close();
}

#endif