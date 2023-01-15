
#ifndef NODE
#define NODE

#include "Types.h"

class Node {
public:

   

   // get row-co-ordinate
   int getRow();

   // get Column-co-ordinate
   int getCol();

   // getters and setters for distance to source
   int getDistanceToS();
   void setDistanceToS(int distanceToS);


   
   
   // Constructor/Destructor
   Node(int row, int col, int distanceToS);
   ~Node();
    
    
private:
    int row;
    int col;
    int distanceToS;
    

};


// Pointer to a Position-Distance
typedef Node* NodePtr;

#endif // NODE
