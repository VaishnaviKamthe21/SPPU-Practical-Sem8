#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    // Add Edge
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // DFS Utility
    void DFSUtil(int node, vector<bool> &visited) {

        #pragma omp critical
        {
            if (visited[node])
                return;

            visited[node] = true;

            cout << node << " ";
        }

        // Parallel traversal
        #pragma omp parallel for
        for (int i = 0; i < adj[node].size(); i++) {

            int neighbor = adj[node][i];

            if (!visited[neighbor]) {

                #pragma omp task
                DFSUtil(neighbor, visited);
            }
        }
    }

    // Parallel DFS
    void DFS(int start) {

        vector<bool> visited(V, false);

        cout << "Parallel DFS: ";

        #pragma omp parallel
        {
            #pragma omp single
            {
                DFSUtil(start, visited);
            }
        }
    }
};

int main() {

    Graph g(6);

    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(1,3);
    g.addEdge(1,4);
    g.addEdge(2,5);

    g.DFS(0);

    return 0;
}