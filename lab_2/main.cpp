#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>

#define N 100

using namespace std;

queue<int> myQueue;
vector<int> adjList[N];
int bfs_visited[N] = {0};
int dist[N];
int nodes, edges;
int shortestPaths[N] = {0};
float edgeFlux[N][N] = {0};  // New data structure for edge fluxes
vector<vector<int>> shortestPathList[N];

void printAdjlist();
void read(char *filename);
void bfs2(int start);
void trackShortestPaths(int start);

int main(int argc, char *argv[]) {
    read(argv[1]);
    printAdjlist();

    cout << endl;
    bfs2(1);
    cout << endl;

    cout << "\nShortest paths with bfs: " << endl;

    for (int i = 1; i <= nodes; ++i) {
        cout << "Shortest paths from 1 to " << i << ": " << shortestPaths[i] << endl;
        cout << "Paths: " << endl;
        for (const vector<int> &path: shortestPathList[i]) {
            for (int node: path) {
                cout << node << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    cout << "\nEdge Fluxes: " << endl;
    for (int i = 1; i <= nodes; ++i) {
        for (int j = 1; j <= nodes; ++j) {
            if( edgeFlux[i][j] != 0 ){
                cout << "Edge (" << i << " - " << j << "): " << edgeFlux[i][j] << endl;
            }
        }
    }

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

void bfs2(int start) {
    bfs_visited[start] = 1;
    myQueue.push(start);
    dist[start] = 0;
    shortestPaths[start] = 1;

    while (!myQueue.empty()) {
        int u = myQueue.front();
        myQueue.pop();

        for (int i = 0; i < adjList[u].size(); ++i) {
            int v = adjList[u][i];
            if (bfs_visited[v] == 0) {
                bfs_visited[v] = 1;
                dist[v] = dist[u] + 1;
                myQueue.push(v);
                shortestPaths[v] = shortestPaths[u];
            }

            if (dist[v] == dist[u] + 1) {
                edgeFlux[u][v]++;
            }
        }
    }

    for (int i = 1; i <= nodes; ++i) {
        if (i != start) {
            trackShortestPaths(i);
        }
    }
}

void trackShortestPaths(int start) {
    stack<int> pathStack;
    pathStack.push(start);
    vector<int> currentPath;

    while (!pathStack.empty()) {
        int node = pathStack.top();
        pathStack.pop();
        currentPath.push_back(node);

        if (node == 1) {
            vector<int> path(currentPath.rbegin(), currentPath.rend());
            shortestPathList[start].push_back(path);
        } else {
            for (int neighbor : adjList[node]) {
                if (dist[neighbor] + 1 == dist[node]) {
                    pathStack.push(neighbor);
                }
            }
        }
    }
}
