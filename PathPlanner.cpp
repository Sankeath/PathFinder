
#include "PathPlanner.h"

#include <iostream>

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

PathPlanner::PathPlanner(Env env, int rows, int cols){
    
    int i = 0;
    int j = 0;
    
    
    // reads in the passed environment again to use inside of pathplanner
    while ((j < 20))
    {
        this->env[j][i] = env[j][i];
        if (env[j][i] == 'S') {
            initialPosition(j,i);
        }
        if (env[j][i] == 'G') {
            this->goalCol = i;
            this->goalRow = j;
        }
        ++i;
        if (i == 20)
        {
            ++j;
            i = 0;
        }
    }

    Open_List = new NodeList();
    Closed_List = new NodeList();
    

}

PathPlanner::~PathPlanner(){
   delete startPos;
   
   delete Open_List;
   delete Closed_List;
   delete Neighbor;
}

void PathPlanner::initialPosition(int row, int col){
   startPos = new Node(row,col,0); 
}

NodeList* PathPlanner::getReachableNodes(){
    //Assume that the starting postition is initialised before this point.
    Open_List->addBack(startPos);

    P = Open_List->get(0);
    
    bool checked_all_sides = false;
    
    bool p_found = false;
    bool node_exists;
    bool can_check;
    int i = 0;
    
    
    int P_row;
    int P_col;
    int P_distToS; 
    int Location[2];
    int row;
    int col;
    int Open_List_Length;
    bool breakLoop;
    // Loops until every reachable position is found in the environment
    while (!p_found )
    {
        // For the P Node loop until all four of P's sides (UP,DOWN,RIGHT,LEFT) have been check for reachability
        while(!checked_all_sides)
        {   
            P_row = P->getRow();
            P_col = P->getCol();
            P_distToS = P->getDistanceToS();
            
            getLoc(Location,i,P_row,P_col);
            
            row = Location[0];
            col = Location[1];
            can_check = true;
            
            // checks if the row and col position of the side the code 
            //is currently checking is a positon in the current envrionment dimension.
            if ((row > ENV_DIM || row < 0) && (col > ENV_DIM || col < 0)){
                can_check = false;
            }
            // checks if the current side the code is are checking (UP,DOWN,RIGHT,LEFT) 
            //is a reachable position if so then adding it to the open list
            if((!(env[row][col] == SYMBOL_WALL) || (env[row][col] == 'G') )&& (can_check)){
                
                
                Q = new Node(row,col,P_distToS+1);
                node_exists = listCompare(Q,Open_List);
                // only add to open list if Q is not in open list already 
                if (!(node_exists)){
                    Open_List->addBack(Q);
                    
                }
                delete Q;
                Q = nullptr;
            }
            ++i;
            // checks if all sides (UP,DOWN,RIGHT,LEFT) have been checked
            if (i == 4) {
                checked_all_sides = true;
                i = 0;
            }
        }
        // Add current P to closed list as we know its reachable    
        Closed_List->addBack(P);
        Open_List_Length = Open_List->getLength();
        breakLoop = false;

        // Finds a P node thats is in the open list but not in the closed list
        for (int i = 0; i < Open_List_Length && !breakLoop ; ++i)
        {

            
            P = Open_List->get(i);
            
            p_found = listCompare(P,Closed_List);

            // if a current P Node is not found in the closed list them break the for loop
            if (!p_found){
                breakLoop = true;
            }
            
        }
        
        checked_all_sides = false;
    
        
    }
    // creates deep copy
    NodeList* DP_Closed_List = new NodeList(*Closed_List);

    return DP_Closed_List;
}

NodeList* PathPlanner::getPath(){

    
    int loc[2];
    int i = 0;
    bool new_G_found = false;
    Neighbor = new NodeList();
    int lengthCL = Closed_List->getLength();
    int curr_goal_row = goalRow;
    int curr_goal_col = goalCol; 
    int curr_goal_DTS = 0;
    bool path_goal_found = false;
    // FInds the Distance to source of the goal position and also check if the goal position is reachable, 
    // as if it is it would be in the closed list. 
    for (int i = 0; i < lengthCL; ++i)
    {
        int curRow = 0;
        int curCol = 0; 
        curRow = Closed_List->get(i)->getRow();
        curCol = Closed_List->get(i)->getCol();    

        if (goalRow == curRow && goalCol == curCol) {
            curr_goal_DTS = Closed_List->get(i)->getDistanceToS();
            path_goal_found = true;
        }
    }
    // if goal position is not reachable the code returns a deep copy of the empty NodeList Neighbors
    if (!path_goal_found) {
        NodeList* DP_Neighbor = new NodeList(*Neighbor);
        return DP_Neighbor;
    }
    
    //Add the goal node as the first 
    Node node(curr_goal_row,curr_goal_col,curr_goal_DTS);
    Neighbor->addBack(&node);
    

    int curRow = 0 ;
    int curCol = 0;
    int curDTS = 0;
    
    // checks all sides (UP,DOWN,RIGHT,LEFT) until no node exists in closed 
    //list such that its distance to source is one less than the goal node 
    //(goal node starts at the position of the intial goal defined in the maze before hand).
    while (i < 4)
    {   
        // get the postion of the current side the code is checking relative to the current goal position
        getLoc(loc,i,curr_goal_row,curr_goal_col);
        
        
        for (int i = 0; (i < lengthCL) && (!new_G_found); ++i)
        {
            curRow = Closed_List->get(i)->getRow();
            curCol = Closed_List->get(i)->getCol();
            curDTS = Closed_List->get(i)->getDistanceToS();
            //checks if the distance to source of the current node is one less than 
            //the goals distance to source and also check if current node is the correct 
            //side of the goal position we are looking for.
            if (curCol == loc[1] && curRow == loc[0] && curDTS == curr_goal_DTS-1){
                // if a node with DTS minus one is found then add it to neighbor (our solution list)
                Node node(curRow,curCol,curDTS);
                Neighbor->addBack(&node);
                new_G_found = true;
            } 
        }
        // change current goal to the node with DTS minus one 
        if (new_G_found){
            
            curr_goal_col = curCol;
            curr_goal_row = curRow;
            curr_goal_DTS = curDTS;
            i = 0;
            new_G_found = false;
        }
        else {
            ++i;
        }
        
    }
    
    NodeList* DP_Neighbor = new NodeList(*Neighbor);
   
    return DP_Neighbor;
}

void PathPlanner::getLoc(int Location[],int Direction,int P_row,int P_col){
            //Checks Above Current P Node
            if (Direction==UP){
                Location[0] = P_row-1;
                Location[1] = P_col;
            }
            //Checks to the right of Current P Node
            if (Direction==RIGHT){
                Location[0] = P_row;
                Location[1] = P_col+1;
            }
            //Checks Below Current P Node
            if (Direction==DOWN){
                Location[0] = P_row+1;
                Location[1] = P_col;
            }
            //Checks to the left of Current P Node
            if (Direction==LEFT){
                Location[0] = P_row;
                Location[1] = P_col-1;
            }
}

bool PathPlanner::listCompare(NodePtr node,NodeList* nodeList){

    
    int list_length = nodeList->getLength();
    int node_row = node->getRow();
    int node_col = node->getCol();
    
    Node* curNode;
    for (int i = 0; i < list_length; ++i)
    {
        
        curNode = nodeList->get(i);
        int curNode_row = curNode->getRow();
        int curNode_col = curNode->getCol();
        
        if ((node_row == curNode_row) && (node_col == curNode_col) ){
            
            return true;
        }
        
    }
    
    return false ;
}
