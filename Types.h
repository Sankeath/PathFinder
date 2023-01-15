
#ifndef TYPES
#define TYPES

#include <math.h> 

#define ENV_DIM                     20
#define NODE_LIST_ARRAY_MAX_SIZE    4*(ENV_DIM * ENV_DIM)

// A 2D array to represent the maze or observations
// REMEMBER: in a grid, the location (x,y) is found by grid[y][x]!
typedef char Env[ENV_DIM][ENV_DIM];

#define SYMBOL_WALL     '='
#define SYMBOL_EMPTY    '.'
#define SYMBOL_GOAL     'G'
#define SYMBOL_START    'S'

#endif // TYPES
