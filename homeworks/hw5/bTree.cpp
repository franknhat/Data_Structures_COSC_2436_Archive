#include "bTree.h"

bTree::bTree(){
    source=nullptr;
    nodeDegree=0;
}

bTree::bTree(int deg){
    source=nullptr;
    nodeDegree=deg;
}

void bTree::destructorHelper(node*& cur){
    if(cur==nullptr)
        return;
    if(cur->value!=nullptr)
        delete [] cur->value;
    if(cur->children!=nullptr){
        for(int i=0;i<=cur->curNumValues;i++){
            if(cur->children[i]!=nullptr){
                destructorHelper(cur->children[i]);
                delete cur->children[i];
                cur->children[i]=nullptr;
            }
        }
        //delete [] cur->children; //why is memory management so hard
        //cur->children=nullptr;
    }
    if(cur->children==nullptr && cur->value==nullptr)
        delete cur;
    cur=nullptr;
}

bTree::~bTree(){
    destructorHelper(source);
    delete source;
}

node*& bTree::getSource(){
    return source;
}

void bTree::addToBTree(node*& cur, int key){
    if(source==nullptr){ //if source==nullptr
        source=new node(nodeDegree);
        source->value[source->curNumValues++]=key;
    }
    else{
        bool isLeaf=true;
        for(int i=0;i<=nodeDegree;i++)
            if(cur->children[i]!=nullptr)
                isLeaf=false;
        if(isLeaf){
            for(int i=0;i<cur->curNumValues;i++)
                if(cur->value[i]==key)
                    return;
            cur->value[cur->curNumValues++]=key;
            std::sort(cur->value, cur->value+cur->curNumValues);
        }
        else{
            int location=0;
            for(int i=0;i<cur->curNumValues;i++){
                if(key>cur->value[i])
                    location++;
                if(key==cur->value[i])
                    return;
            }
            addToBTree(cur->children[location], key);
            if(cur->children[location]->curNumValues==nodeDegree){ //if the node is overfiled
                cur->value[cur->curNumValues++]=cur->children[location]->value[(nodeDegree-1)/2];
                std::sort(cur->value, cur->value+cur->curNumValues);
                int index=0;
                for(;index<=cur->curNumValues;index++) //find location of inserted in arr
                    if(cur->value[index]==cur->children[location]->value[(nodeDegree-1)/2])
                        break;
                for(int i=nodeDegree;i>index;i--){
                    cur->children[i]=nullptr;
                    cur->children[i]=cur->children[i-1];
                }
                node* temp=new node(nodeDegree);
                node* temp2=new node(nodeDegree);
                for(int i=0;i<=(nodeDegree-1)/2;i++){
                    if(i<(nodeDegree-1)/2){
                        temp->value[i]=cur->children[location]->value[i];
                        temp->curNumValues++;
                    }
                    temp->children[i]=cur->children[location]->children[i];
                }
                for(int i=((nodeDegree-1)/2)+1;i<=nodeDegree;i++){
                     if(i<nodeDegree){
                        temp2->value[i-((nodeDegree-1)/2+1)]=cur->children[location]->value[i];
                        temp2->curNumValues++;
                    }
                    temp2->children[i-((nodeDegree-1)/2+1)]=cur->children[location]->children[i];
                }
                delete cur->children[index];
                //delete cur->children[index+1]; //fuck memory management
                cur->children[index]=cur->children[index+1]=nullptr;
                cur->children[index]=temp;
                cur->children[index+1]=temp2;
            }   
        }
    }
    if(cur==source && cur->curNumValues==nodeDegree){
        node* temp = new node(nodeDegree);
        temp->children[0]=new node(nodeDegree);
        temp->children[1]=new node(nodeDegree);
        temp->value[temp->curNumValues++]=cur->value[((nodeDegree-1)/2)];
        for(int i=0;i<=(nodeDegree-1)/2;i++){
            if(i<(nodeDegree-1)/2){
                temp->children[0]->value[i]=cur->value[i];
                temp->children[0]->curNumValues++;
            }
            temp->children[0]->children[i]=cur->children[i];
        }
        for(int i=((nodeDegree-1)/2)+1;i<=nodeDegree;i++){
            if(i<nodeDegree){
                temp->children[1]->value[i-((nodeDegree-1)/2+1)]=cur->value[i];
                temp->children[1]->curNumValues++;
            }
            temp->children[1]->children[i-((nodeDegree-1)/2+1)]=cur->children[i];
        }
        delete cur;
        cur=nullptr;
        source=cur=temp;
    }
}

void bTree::setDegree(int deg){
    nodeDegree=deg;
}

int bTree::getDegree(){
    return nodeDegree;
}

int bTree::findHeight(node* const cur){
    if(cur==nullptr)
        return 0;
    int max=1+findHeight(cur->children[0]);
    for(int i=1;i<=cur->curNumValues;i++)
        if(1+findHeight(cur->children[i])>max)
            max=1+findHeight(cur->children[i]);
    return max;
}

node* bTree::peekSource(){
    return source;
}