#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathPlanner.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.

void printPath(Env env, NodeList* solution);


int main(int argc, char** argv){
    


    

    // Load Environment 
    Env env;
    readEnvStdin(env);
    
    
    PathPlanner* pathplanner = new PathPlanner(env, ENV_DIM, ENV_DIM);
    
    NodeList* reachablePositions = nullptr;
    reachablePositions = pathplanner->getReachableNodes();
    
    
    

   
        

    
    // Get the path
    
    NodeList* solution = pathplanner->getPath();
    

    
    //print the path
    printPath(env, solution);
    
    
    delete pathplanner;
    
    delete reachablePositions;
    
    delete solution;

    

}

void readEnvStdin(Env env){
    //Individually goes through each character in the .env file and assigns it to its related position in the 2D-array.
    // e.g. if the first symbol is a '=' (wall symbole) now env[0][0] is equal to '='
    int i = 0;
    int j = 0;
    
    

    while ((!std::cin.eof()) && (j < 20))
    {
        std::cin  >> env[j][i];
        ++i;
        if (i == 20)
        {
            ++j;
            i = 0;
        }
    }
    
    
    
}

void printPath(Env env, NodeList* solution) {
    int length = solution->getLength();

    // First checks if there a path to the goal exist before getting
    //row and column information to avoid a segmentation fault.  
    if (length == 0) {
        std::cout << "No Path to the Goal exists" << std::endl;
    }
    else{
        int curRow;
        int curCol;
        int prevRow = solution->get(length-2)->getRow();
        int prevCol = solution->get(length-2)->getCol();

         
        for (int i = length-2; i >= 0; --i)
        {
            curRow = solution->get(i)->getRow();
            curCol = solution->get(i)->getCol();
            // This set of if statements finds the direction of the 
            //path in the solution NodeList and replacing the approprate
            //position in env with the correct directional marker.
            if (curCol==prevCol && curRow == prevRow-1){
                env[prevRow][prevCol] = '^';
            }
            if (curCol==prevCol+1 && curRow == prevRow){
                env[prevRow][prevCol] = '>';
            }
            if (curCol==prevCol && curRow == prevRow+1){
                env[prevRow][prevCol] = 'v';
            }
            if (curCol==prevCol-1 && curRow == prevRow){
                env[prevRow][prevCol] = '<';
            }
            prevCol = curCol;
            prevRow = curRow;
            
        }
        
        // we can print the env similar to how we read in the env 
        //by simply iterating through each position in the env.
        for (int k = 0; k < 20; k++)
        {
            for (int h = 0; h < 20; h++)
            {
            std::cout << env[k][h];
            }
            std::cout<<std::endl;
        }
    }
}

void printReachablePositions(Env env, NodeList* reachablePositions){
    Node* curNode;
    for (int i = 0; i < reachablePositions->getLength(); ++i)
    {
        curNode = reachablePositions->get(i);
        int curNode_row = curNode->getRow();
        int curNode_col = curNode->getCol();
        int curNode_distToS = curNode->getDistanceToS();

        std::cout << std::endl;
        std::cout << "row = " << curNode_row << " column = " << curNode_col << std::endl;
        std::cout << "Distance to Source = " << curNode_distToS << std::endl;
        std::cout << std::endl;
    }
}

void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceToS() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceToS() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addBack(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addBack(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->get(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceToS() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;

    for (int i = 0; i < nodeList->getLength(); i++)
    {
        Node* getB = nodeList->get(i);
        std::cout << "(" << getB->getRow() << ",";
        std::cout << getB->getCol() << ",";
        std::cout << getB->getDistanceToS() << ") ";
    }
    std::cout << std::endl;
    std::cout << "LIST HAS BEEN PRINTED" << std::endl;
}