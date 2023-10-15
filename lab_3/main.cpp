#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <stack>
#include <algorithm>

#define N 100

using namespace std;


vector<int> adjList[N];
int nodes, edges;


void printAdjlist();
void read(char *filename);

//sorting functions
bool compareNodesByNeighborCount(const vector<int>& a, const vector<int>& b) {
    return a.size() < b.size();
}

int main(int argc, char* argv[]) {
    //read the file, and printing the adjacency list
    read(argv[1]);
    printAdjlist();

    //sorting the adjacency list by neighbours
    sort(adjList + 1, adjList + nodes + 1, compareNodesByNeighborCount);

    //sorted adjacency list
    // a kiiratasnal rendezte a szomszedok szama alapjan, viszont a hozzajuk tartozo nodeokat, nem jo sorrendben irja ki
    cout << "\nSorted adjacency list: " << endl;
    printAdjlist();



    return 0;
}

void printAdjlist() {
    for (int i = 1; i <= nodes; ++i) {
        cout << i << ": ";
        for (int j = 0; j < adjList[i].size(); ++j) {
            cout << adjList[i][j] << " ";
        }
        cout << endl;
    }
}

void read(char *filename) {
    ifstream fin(filename);

    if (!fin) {
        cout << "Error when opening file!" << endl;
        exit(-2);
    }

    fin >> nodes >> edges;
    for (int i = 1; i <= edges; ++i) {
        int u, v;
        fin >> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
}
