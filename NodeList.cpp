
#include "NodeList.h"
#include <iostream>



NodeList::NodeList(){
   length = 0;
}


NodeList::~NodeList(){
   

   for (int i = 0; i < length; ++i)
   {
       
       if (!(nodes[i] == nullptr)){
            delete nodes[i];
            nodes[i] = nullptr;
       }
   }
   
}

NodeList::NodeList(NodeList& other){
    

    
    int row = 0;
    int col = 0;
    int DTS = 0;
    // creates deep copy
    for (int i = 0; i < other.getLength(); ++i)
    {
        row = other.get(i)->getRow();
        col = other.get(i)->getCol();
        DTS = other.get(i)->getDistanceToS();
        
        Node copyN(row,col,DTS);
        addBack(&copyN);
    }
    
}


int NodeList::getLength(){
   return length;
}


NodePtr NodeList::get(int i){
    // Returns a NodePtr at the index integer i (passed as the parament to this method) 
    return nodes[i];
}

void NodeList::addBack(NodePtr newNode){
    /*Add an new pointer to a node at the end of the array*/
    N = new Node(newNode->getRow(),newNode->getCol(),newNode->getDistanceToS());
    nodes[length] = N;
    N = nullptr;
    ++length;
}

bool NodeList::containsNode(NodePtr node){
   /*The code Does a Linear search of the nodes array and return true if the passed
    node exists in the nodes array else returns false*/
   for (int i = 0; i < length; i++)
   {
       if (nodes[i] == node)
       {
           return true;
       }
       else 
       {
           return false;
       }
   }
   return false;
}

void NodeList::clear(){
    // Iterates through the nodes list up to length clearing all Nodes 
    //at each pointer in the list unelse it is already a null pointer.
   for (int i = 0; i < length; ++i)
   {
       
       if (!(nodes[i] == nullptr)){
            delete nodes[i];
            nodes[i] = nullptr;
       }
   }
}