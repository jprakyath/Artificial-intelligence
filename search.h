#ifndef SEARCH_H
#define SEARCH_H
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <deque>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <stack>

// Used to define different blocks on the map
#define START   'P'
#define WALL    '%'
#define OPEN    'O'
#define CLOSED  'C'
#define END     '.'

using namespace std;

// Hold row,col coordinates and attributes of places in the maze
class Node
{
    int row, col;               	// Store the position of the agent
    int depth;						// Store the agent's current depth
    int functionF;					// f(n) = g(n) + h(n) , this is the estimated total path cost
    Node * parent;					// Keep track of parent address

    public:
    // Constructor used for BFS and DFS
    Node(int row,int col,int depth,Node * parent);

    // Constructor used for A* search and Greedy BFS
    Node(int row,int col,int depth,int functionF,Node * parent);

    // Delete the pointer to the parent node
    ~Node() {
        delete parent;
    }
    // Accessor methods
    inline int getRow() { return row; }
    inline int getCol() { return col; }
    inline int getDepth() { return depth; }
    inline int getFunctionF() { return functionF; }
    inline Node * getParent() { return parent; }
};

class Search
{
    vector< vector<char> > maze;
    vector< vector<char> > route;
    int startRow, startCol;
    int exitRow, exitCol;
    int cost;						// Total number of moves made

    // Deques are implemented for their use as a Queue and Stack
    deque<Node *> openNodes;
    deque<Node *> closedNodes;

    int noOfRows;
    int noOfColumns;

public:
    Search();
    void readInputFile(string file_name);
    void bfs();
    void dfs();
    void astar();
    void insertionAstar(int row, int col, int depth, Node * parent);
    void bestFS();
    void insertionBFS(int row, int col, int depth, Node * parent);
    void cleanup();
    void printSolution();
};

#endif // SEARCH_H
