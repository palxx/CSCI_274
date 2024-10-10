#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, weight;
    
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class UnionFind {
public:
    vector<int> parent, rank;
    
    // Initialize with n elements
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }
    
    // Find the root of element u with path compression
    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);  // Path compression
        }
        return parent[u];
    }
    
    // Union by rank
    void unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        
        if (rootU != rootV) {
            if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

class Kruskal {
public:
    // Kruskal's algorithm to find MST
    int kruskalMST(int V, vector<Edge>& edges) {
        sort(edges.begin(), edges.end());  // Sort edges by weight
        
        UnionFind uf(V);  // Create union-find for V vertices
        int mstWeight = 0;
        vector<Edge> mstEdges;
        
        for (const Edge& edge : edges) {
            if (uf.find(edge.u) != uf.find(edge.v)) {
                uf.unionSets(edge.u, edge.v);  // Join sets
                mstWeight += edge.weight;      // Add edge weight to MST
                mstEdges.push_back(edge);
            }
        }
        
        // Output the MST
        cout << "Edges in the Minimum Spanning Tree:\n";
        for (const Edge& e : mstEdges) {
            cout << "(" << e.u << ", " << e.v << ") - Weight: " << e.weight << "\n";
        }
        return mstWeight;
    }
};

int main() {
    int V = 4;  // Number of vertices
    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    Kruskal kruskal;
    int mstWeight = kruskal.kruskalMST(V, edges);
    cout << "Total weight of MST: " << mstWeight << "\n";
    
    return 0;
}
