#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>


#define N 100

using namespace std;

queue <int>myQueue;
vector <int> adjList[N];
int bfs_visited[N] = {0};
int dist[N];
int n,m;

void bfs2(int start)
{
    bfs_visited[start] = 1;
    myQueue.push(start);

    while(!myQueue.empty())
    {
        int u = myQueue.front();
        cout << u << " ";
        for (int i = 0; i < adjList[u].size(); ++i) {
            int v = adjList[u][i];
            if(bfs_visited[v] == 0)
            {
                bfs_visited[v] = 1;
                dist[v] = dist[u] + 1;
                myQueue.push(v);
            }
        }
        myQueue.pop();
    }
}

void read(char *filename)
{
    ifstream fin(filename);

    if( !fin){
        cout << "Error when opening file!" << endl;
        exit(-2);
    }

    //read nodes, edges
    fin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u,v;
        fin >> u >> v;
        adjList[u ].push_back(v );
        adjList[v ].push_back(u );
    }
}

void printAdjlist()
{
    for (int i = 1; i <= n; ++i) {
        cout << i << ": ";
        for (int j = 0; j < adjList[i].size(); ++j) {
            cout << adjList[i][j] << " ";
        }
        cout << endl;
    }
}

int main(int argc, char *argv[]) {
    read( argv[1] );
    printAdjlist();

    cout << endl;
    bfs2(2);
    cout << endl;

    for (int i = 1; i <= n; ++i) {
        cout << i << " " << dist[i]<< endl;
    }

    return 0;
}