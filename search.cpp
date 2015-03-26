#include "search.h"

// Constructor used for BFS and DFS
Node::Node(int row, int col, int depth, Node * parent) {
    this->row = row;
    this->col = col;
    this->depth = depth;
    this->parent = parent;
}

// Constructor used for A* search and Greedy BFS
Node::Node(int row, int col, int depth, int functionF, Node * parent) {
    this->row = row;
    this->col = col;
    this->depth = depth;
    this->functionF = functionF;
    this->parent = parent;
}

// Constructor
Search::Search()
{
    this->cost = 0;
}

void Search::readInputFile(string file_name) {
    int row = 0;
    this->cost = 0;
    ifstream mapFile(file_name.c_str());
    if (mapFile.is_open())
    {
        while (!mapFile.eof()) {
            string line;
            getline(mapFile,line);
            if(line == "") break;
            vector<char> temp;
            for (int i = 0; i < line.length(); i++) {
                temp.push_back(0);
            }
            maze.push_back(temp);
            route.push_back(temp);
            for (int i = 0; i < line.length(); i++) {
                // read the maze line by line and update the
                // blank route.
                maze[row][i] = line[i];
                route [row][i] = maze [row][i];
                //cout << maze [row][i];
                if (maze[row][i] == START) {
                    startRow = row;
                    startCol = i;
                } else if (maze[row][i] == END) {
                    exitRow = row;
                    exitCol = i;
                }
            }
            //cout << endl;
            row++;
            noOfColumns = line.length();
        }
        noOfRows = row;
        mapFile.close();
    } else {
        cout << "Unable to open file";
    }
}

void Search::bfs() {
    openNodes.push_back(new Node(startRow, startCol, 0, 0));
    route[startRow][startCol] = OPEN;

    // Keep track of where we are in the maze
    int row = 0;
    int col = 0;
    // maze solved?
    bool win = false; //

    // Keep searching an exit is determined or no solution is found
    while(openNodes.size() != 0) {
        // Get the row and column of the current position
        row = openNodes.front()->getRow();
        col = openNodes.front()->getCol();
        route[row][col] = CLOSED; 							// Current position has now been opened and explored
        cost++; 												// Increase cost for each node explored
        if(maze[row][col] == END) { 						// Check if we have found the goal
            closedNodes.push_back(openNodes.front());
            openNodes.pop_front();
            win = true;
            break; 												// Goal has been found
        } else { 												// Goal has not been found so we must check surrounding nodes
            closedNodes.push_back(openNodes.front());
            openNodes.pop_front(); 								// Get rid of the first element in the deque

            int depth = (closedNodes.back()->getDepth()) + 1; 	// Depth of the next node will be +1 of the current node recently added to the closed deque
            Node * parent = closedNodes.back();				// Parent address is the previous node

            // Try left of the current position
            if ((col-1 > -1) && route[row][col-1] != WALL && route[row][col-1] != CLOSED && route[row][col-1] != OPEN) {
                route[row][col-1] = OPEN;
                openNodes.push_back(new Node(row,col-1,depth,parent));
            }
            // Try above the current position
            if ((row-1 > -1) && route[row-1][col] != WALL && route[row-1][col] != CLOSED && route[row-1][col] != OPEN) {
                route[row-1][col] = OPEN;
                openNodes.push_back(new Node(row-1, col, depth, parent));
            }
            // Try right of the current position
            if ((col+1 < noOfColumns) && route[row][col+1] != WALL && route[row][col+1] != CLOSED && route[row][col+1] != OPEN) {
                route[row][col+1] = OPEN;
                openNodes.push_back(new Node(row, col+1, depth, parent));
            }
            // Try below the current position
            if ((row+1 < noOfRows) && route[row+1][col] != WALL && route[row+1][col] != CLOSED && route[row+1][col] != OPEN) {
                route[row+1][col] = OPEN;
                openNodes.push_back(new Node(row+1, col, depth, parent));
            }
        }
    }

    if (!win) {
        cout << "This maze has no solution!" << endl;
    }
    printSolution();
}

void Search::dfs() {
    openNodes.push_front(new Node(startRow, startCol, 0, 0));
    route[startRow][startCol] = OPEN;

    // Keep track of where we are in the maze
    int row = 0;
    int col = 0;
    bool win = false; // Did we solve the maze?
    // Keep searching an exit is determined or no solution is found
    while(openNodes.size() != 0) {
        // Get the row and column of the current position
        row = openNodes.front()->getRow();
        col = openNodes.front()->getCol();
        route[row][col] = CLOSED; 								// Current position has now been opened and explored
        cost++; 												// Increase cost for each node explored
        if(maze[row][col] == END) { 							// Check if we have found the goal
            closedNodes.push_back(openNodes.front());
            openNodes.pop_front();
            win = true;
            break; 													// Goal has been found
        } else { 													// Goal has not been found so we must check surrounding nodes
            closedNodes.push_back(openNodes.front());
            openNodes.pop_front(); 									// Get rid of the first element in the deque
            int depth = (closedNodes.back()->getDepth()) + 1; 	// Depth of the next node will be +1 of the current node recently added to the closed deque
            Node * parent = closedNodes.back();					// Parent address is the previous node
            // Try above the current position
            if ((row-1 > -1) && route[row-1][col] != WALL && route[row-1][col] != CLOSED && route[row-1][col] != OPEN) {
                route[row-1][col] = OPEN;
                openNodes.push_front(new Node(row-1, col, depth, parent));
            }
            // Try below the current position
            if ((row+1 < noOfRows) && route[row+1][col] != WALL && route[row+1][col] != CLOSED && route[row+1][col] != OPEN) {
                route[row+1][col] = OPEN;
                openNodes.push_front(new Node(row+1, col, depth, parent));
            }
            // Try left of the current position
            if ((col-1 > -1) && route[row][col-1] != WALL && route[row][col-1] != CLOSED && route[row][col-1] != OPEN) {
                route[row][col-1] = OPEN;
                openNodes.push_front(new Node(row, col-1, depth, parent));
            }
            // Try right of the current position
            if ((col+1 < noOfColumns) && route[row][col+1] != WALL && route[row][col+1] != CLOSED && route[row][col+1] != OPEN) {
                route[row][col+1] = OPEN;
                openNodes.push_front(new Node(row, col+1, depth, parent));
            }
        }
    }
    if (!win) {
        cout << "This maze has no solution!" << endl;
    }
    printSolution();
}

void Search::astar() {
    // manhattan distance
    int functionF = abs(startRow - exitRow) + abs(startCol - exitCol);
    openNodes.push_back(new Node(startRow, startCol, 0, functionF, 0));
    route[startRow][startCol] = OPEN;

    // Keep track of where we are in the maze
    int row = 0;
    int col = 0;
    bool win = false; // Did we solve the maze?

    // Keep searching an exit is determined or no solution is found
    while(openNodes.size() != 0) {
        // Get the row and column of the current position
        row = openNodes.front()->getRow();
        col = openNodes.front()->getCol();
        route[row][col] = CLOSED; 								// Current position has now been opened and explored
        cost++; 													// Increase cost for each node explored
        if(maze[row][col] == END) { 							// Check if we have found the goal
            closedNodes.push_back(openNodes.front());
            openNodes.pop_front();
            win = true;
            break; 													// Goal has been found
        } else { 													// Goal has not been found so we must check surrounding nodes
            closedNodes.push_back(openNodes.front());
            openNodes.pop_front();
            int depth = (closedNodes.back()->getDepth()) + 1; 	// Depth of the next node will be +1 of the current node recently added to the closed deque
            Node * parent = closedNodes.back();					// Parent address is the previous node

            // Try left of the current position
            if ((col-1 > -1) && route[row][col-1] != WALL && route[row][col-1] != CLOSED && route[row][col-1] != OPEN) {
                route[row][col-1] = OPEN;
                insertionAstar(row, col-1, depth, parent);
            }
            // Try above the current position
            if ((row-1 > -1) && route[row-1][col] != WALL && route[row-1][col] != CLOSED && route[row-1][col] != OPEN) {
                route[row-1][col] = OPEN;
                insertionAstar(row-1, col, depth, parent);
            }
            // Try right of the current position
            if ((col+1 < noOfColumns) && route[row][col+1] != WALL && route[row][col+1] != CLOSED && route[row][col+1] != OPEN) {
                route[row][col+1] = OPEN;
                insertionAstar(row, col+1, depth, parent);
            }
            // Try below the current position
            if ((row+1 < noOfRows) && route[row+1][col] != WALL && route[row+1][col] != CLOSED && route[row+1][col] != OPEN) {
                route[row+1][col] = OPEN;
                insertionAstar(row+1, col, depth, parent);
            }
        }
    }
    if (!win) {
        cout << "This maze has no solution!" << endl;
    }
    printSolution();
}

void Search::insertionAstar(int row, int col, int depth, Node * parent) {
    // A * Search uses a priority queue
    // Insert elements in the deque according to priority
    int gN = depth;
    int hN = abs(exitRow - row) + abs(exitCol - col);
    int functionF = gN + hN;
    bool insertSuccess = false;

    // Use insertion sort to insert the element into deque according to highest priority (ie. lowest functionF value)
    if (openNodes.size() == 0) {
        openNodes.push_back(new Node(row, col, depth, functionF, parent));
    } else {
        deque<Node *>::iterator it;
        int i = 0;
        for (it = openNodes.begin(); it != openNodes.end(); it++) {
            if (functionF < openNodes[i]->getFunctionF()) {
                openNodes.insert(it, new Node(row, col, depth, functionF, parent));
                insertSuccess = true;
                break;
            }
            i++;
        }
        if (!insertSuccess) {
            openNodes.push_back	(new Node(row, col, depth, functionF, parent));
        }
    }
}

void Search::bestFS() {

    int functionF = abs(startRow - exitRow) + abs(startCol - exitCol);
    openNodes.push_back(new Node(startRow, startCol, 0, functionF, 0));
    route[startRow][startCol] = OPEN;

    // Keep track of where we are in the maze
    int row = 0;
    int col = 0;
    bool win = false; // Did we solve the maze?

    // Keep searching an exit is determined or no solution is found
    while(openNodes.size() != 0) {
        // Get the row and column of the current position
        row = openNodes.front()->getRow();
        col = openNodes.front()->getCol();
        route[row][col] = CLOSED; 								// Current position has now been opened and explored
        cost++; 													// Increase cost for each node explored
        if(maze[row][col] == END) { 							// Check if we have found the goal
            closedNodes.push_back(openNodes.front());
            openNodes.pop_front();
            win = true;
            break; 												// Goal has been found
        } else { 												// Goal has not been found so we must check surrounding nodes
            closedNodes.push_back(openNodes.front());
            openNodes.pop_front();
            int depth = (closedNodes.back()->getDepth()) + 1; 	// Depth of the next node will be +1 of the current node recently added to the closed deque
            Node * parent = closedNodes.back();				// Parent address is the previous node
            // Try above the current position
            if ((row-1 > -1) && route[row-1][col] != WALL && route[row-1][col] != CLOSED && route[row-1][col] != OPEN) {
                route[row-1][col] = OPEN;
                insertionBFS(row-1, col, depth, parent);
            }
            // Try below the current position
            if ((row+1 < noOfRows) && route[row+1][col] != WALL && route[row+1][col] != CLOSED && route[row+1][col] != OPEN) {
                route[row+1][col] = OPEN;
                insertionBFS(row+1, col, depth, parent);
            }
            // Try left of the current position
            if ((col-1 > -1) && route[row][col-1] != WALL && route[row][col-1] != CLOSED && route[row][col-1] != OPEN) {
                route[row][col-1] = OPEN;
                insertionBFS(row, col-1, depth, parent);
            }
            // Try right of the current position
            if ((col+1 < noOfColumns) && route[row][col+1] != WALL && route[row][col+1] != CLOSED && route[row][col+1] != OPEN) {
                route[row][col+1] = OPEN;
                insertionBFS(row, col+1, depth, parent);
            }           
        }
    }
    if (!win) {
        cout << "This maze has no solution!" << endl;
    }
    printSolution();
}

void Search::insertionBFS(int row, int col, int depth, Node * parent) {
    // A * Search uses a priority queue
    // Insert elements in the deque according to priority
    int heuristic = abs(exitRow - row) + abs(exitCol - col);
    bool insertSuccess = false;

    // Use insertion sort to insert the element into deque according to highest
    // priority (ie. lowest functionF value)
    if (openNodes.size() == 0) {
        openNodes.push_back(new Node(row, col, depth, heuristic, parent));
    } else {
        deque<Node *>::iterator it;
        int i = 0;
        for (it = openNodes.begin(); it != openNodes.end(); it++) {
            if (heuristic < openNodes[i]->getFunctionF()) {
                openNodes.insert(it, new Node(row, col, depth, heuristic, parent));
                insertSuccess = true;
                break;
            }
            i++;
        }
        if (!insertSuccess) {
            openNodes.push_back	(new Node(row, col, depth, heuristic, parent));
        }
    }
}

void Search::cleanup() {
    // Reinitialize the maze
    for (int i = 0; i < noOfRows; i++) {
        for (int j = 0; j < noOfColumns; j++) {
            route [i][j] = maze[i][j];
        }
    }
    // Clear out the deque and reset variables
    openNodes.clear();
    closedNodes.clear();
    cost = 0;
}

void Search::printSolution() {
    // Building the path taken by the agent by climbing the tree from the exit state
    Node * it;
    deque<Node *> path;
    for (it = closedNodes.back(); it->getParent() != 0; it = it->getParent()) {
        path.push_front(it);
    }
    path.push_front(it);
    // Display the the path found in the maze
    // Used tokens that are easy to read
    cout << "Path Taken" << endl;
    for (int i = 0; i < noOfRows; i++) {
        for (int j = 0; j < noOfColumns; j++) {
            if(maze [i][j] == WALL) cout << "%";
            else if(maze [i][j] == START) cout << "P";
            else if(maze [i][j] == END) cout << "E";
            else {
                 bool on_the_path = false;
                 for(int k = 0; k < path.size(); k++) {
                      if(path[k]->getRow() == i && path[k]->getCol() == j)
                          on_the_path = true;
                 }
                 if(on_the_path) cout << ".";
                 else cout << " ";
            }
        }
        cout << "\n";
    }

    cout << endl << endl;
    cout << "Path Cost: " << path.size()-1 << endl;
    cout << "Final no of expanded nodes: " << closedNodes.size()-1<< endl;
}
