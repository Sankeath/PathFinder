
#ifndef PATH_PLANNING
#define PATH_PLANNING

#include "Node.h"
#include "NodeList.h"
#include "Types.h"

class PathPlanner {
public:

   


   // Initialise with a given Env of size (rows,cols)
   PathPlanner(Env env, int rows, int cols);

   // Clean-up
   ~PathPlanner();

   // Set The initial position
   void initialPosition(int row, int col);

   
   // Return a DEEP COPY of the NodeList of all node's
   //    that the robot can reach with distances
   NodeList* getReachableNodes();


   
   // Get the path from the starting position to the given goal co-ordinate
   //    The path should be a DEEP COPY
   NodeList* getPath();


   

   // Gives an array Location which stores the row and col of nodes which is in a particular direction from Node P
   // 0 = Up , 1 = Right , 2 = Down , 3 = Left 
   void getLoc(int Location[],int Direction,int P_row,int P_col);

   // Allow you to check if a specific node is in a specific node list
   bool listCompare(NodePtr node,NodeList* nodeList);

   private:
      Env env;
      NodeList* Open_List;
      NodeList* Closed_List;
      //NodeList* DP_Closed_List;
      NodeList* Neighbor;
      //NodeList* DP_Neighbor;
      NodePtr startPos;
      NodePtr P;
      NodePtr Q;
      int goalRow;
      int goalCol;

      
};

#endif // PATH_PLANNING
