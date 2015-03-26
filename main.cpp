#include <iostream>
#include "search.h"

using namespace std;

/* main function */
int main(int argc, char* argv[]) {

    if (argc != 2){
        cout<<" Wrong usage of the application!"<<endl;
        cout<< "The usage is: ./MazeSearch input file" << endl;
        exit(1);
    }
    string training_data = (string)argv[1];
    Search search;
    search.readInputFile(training_data);
    cout << "BREADTH FIRST SEARCH" << endl;
    cout << "---------------------------------------------------------" << endl;
    search.bfs();
    cout << "=========================================================\n" << endl;
    search.cleanup();
    cout << "DEPTH FIRST SEARCH" << endl;
    cout << "---------------------------------------------------------" << endl;
    search.dfs();
    cout << "=========================================================\n" << endl;
    search.cleanup();
    cout << "BEST FIRST SEARCH" << endl;
    cout << "---------------------------------------------------------" << endl;
    search.bestFS();
    cout << "=========================================================\n" << endl;
    search.cleanup();
    cout << "ASTAR SEARCH" << endl;
    cout << "---------------------------------------------------------" << endl;
    search.astar();
    cout << "=========================================================\n" << endl;
    search.cleanup();

    return 0;
}

