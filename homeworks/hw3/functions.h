#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "reserveFunctions.h"

std::string removeWhiteSpace(std::string str){
    std::string returnString="";
    for (int i=0;i<str.length();i++){
        if(str[i]!=' '){
            returnString+=str[i];
        }
    }
    return returnString;
}

void prefixToPostfix(std::string &input_){
    Stack<std::string> stack_;
    std::string temp;
    for (int i=input_.length()-1;i>=0;i--){
        temp="";
        if (input_[i]=='*' || input_[i]=='/'|| input_[i]=='+'|| input_[i]=='-'){
            for (int i=0;i<2;i++)
                temp+=stack_.pop();
        }
        temp+=input_[i];
        stack_.push(temp);
    }
    input_=stack_.peek();
}

void postfixToPrefix(std::string &input_){
    Stack<std::string> stack_;
    std::string temp;
    for (int i=0;i<input_.length();i++){
        temp="";
        if (input_[i]=='*' || input_[i]=='/'|| input_[i]=='+'|| input_[i]=='-'){
            for (int i=0;i<2;i++)
                temp=stack_.pop()+temp;
        }
        temp=input_[i]+temp;
        stack_.push(temp);
    }
    input_=stack_.peek();
}

void convertNodeType(fixNode* &node){
    if (node->type=="prefix"){
        node->type="postfix";
        prefixToPostfix(node->equation);
    }
    else if (node->type=="postfix"){
        node->type="prefix";
        postfixToPrefix(node->equation);
    }
}

void createLinkedList(std::string infilename, FixedLL &ll){
    std::ifstream input_;
    input_.open(infilename);
    std::string currentLine;
    while(!input_.eof()){
        getline(input_, currentLine);
        if(currentLine.find("prefix:")!=-1 || currentLine.find("postfix:")!=-1)
            ll.push(currentLine.substr(0,currentLine.find(':')),removeWhiteSpace(currentLine.substr(currentLine.find(':')+1)));//type then equation
    }
    input_.close();
}

void runCommands(std::string commandFileName, std::string outputfileName, FixedLL &ll){
    std::ifstream commands;
    std::ofstream outputing;
    Stack<std::string> reserveStack;
    commands.open(commandFileName);
    outputing.open(outputfileName);
    std::string currentCommand;
    while(!commands.eof()){
        getline(commands,currentCommand);
        if(currentCommand.find("print")!=-1){
            if (currentCommand=="printList")
                ll.print(outputing);
            else if (currentCommand=="printListBackwards")
                ll.printBackwards(outputing);
            else if(currentCommand.find("Size")!=-1) //couldnt get ofstream to work with template class
                outputing<<"Reserve Size: "<<reserveStack.getSize()<<std::endl<<std::endl;
            else if (currentCommand.find("Top")!=-1){
                outputing<<"Top of Reserve: ";
                if(reserveStack.isEmpty())
                    outputing<<"EMPTY";
                else
                    outputing<<reserveStack.peek()<<":"<<reserveStack.peek2();
                outputing<<std::endl<<std::endl;
            }
        }
        else if (currentCommand.find("convert")!=-1){
            if (currentCommand=="convertList (postfix)"){
                fixNode* cur=ll.getHead();
                while (cur!=nullptr){
                    if (cur->type=="postfix")
                        convertNodeType(cur);
                    cur=cur->next;
                }
            }
            else if (currentCommand=="convertList (prefix)"){
                fixNode* cur=ll.getHead();
                while (cur!=nullptr){
                    if (cur->type=="prefix")
                        convertNodeType(cur);
                    cur=cur->next;
                }
            }
            else if (currentCommand=="convertList (all)"){
                fixNode* cur=ll.getHead();
                while (cur!=nullptr){
                    convertNodeType(cur);
                    cur=cur->next;
                }
            }
            else if (currentCommand=="convertReserve"){
                typeNode<std::string>* cur=reserveStack.getTop();
                if(!reserveStack.isEmpty()){
                    if(cur->data=="prefix"){
                        cur->data="postfix";
                        prefixToPostfix(cur->data2);
                    }
                    else{
                        cur->data="prefix";
                        postfixToPrefix(cur->data2);
                    }
                }
            }
            else{ //convert pos
                int where=stoi(currentCommand.substr(currentCommand.find('(')+1,currentCommand.find(')')-currentCommand.find('(')-1));
                fixNode* cur=ll.getHead();
                if (where>=ll.getSize()){
                    cur=nullptr;
                    where=0;
                }
                for (int i=0;i<where;i++)
                    cur=cur->next;
                if(cur!=nullptr)
                    convertNodeType(cur);
            }
        }
        else if(currentCommand.find("removeList")!=-1){
            if(isdigit(currentCommand[currentCommand.find('(')+1]) || (currentCommand[currentCommand.find('(')+1=='-'] && isdigit(currentCommand[currentCommand.find('(')+2])))
                ll.removePos(stoi(currentCommand.substr(currentCommand.find('(')+1,currentCommand.find(')')-currentCommand.find('(')-1)));
            else
                ll.removeType(currentCommand.substr(currentCommand.find('(')+1,currentCommand.find(')')-currentCommand.find('(')-1));
        }
        else if(currentCommand.find("pushReserve")!=-1)
            push_reserve_doubly(ll, reserveStack, currentCommand.substr(currentCommand.find('(')+1,currentCommand.find(')')-currentCommand.find('(')-1));
        else if(currentCommand.find("popReserve")!=-1)//popReserve (position)
            pop_reserve_doubly(ll, reserveStack, stoi(currentCommand.substr(currentCommand.find('(')+1,currentCommand.find(')')-currentCommand.find('(')-1)));
        else if (currentCommand=="flipReserve")
            reserveStack.flipstack();
        else if (currentCommand.find("emptyReserve")!=-1)
            emptyReserve(ll,reserveStack,stoi(currentCommand.substr(currentCommand.find('(')+1,currentCommand.find(')')-currentCommand.find('(')-1)));
    }
    commands.close();
    outputing.close();
}

#endif