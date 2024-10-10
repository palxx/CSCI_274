# A recursive function to traverse the graph without
# considering the ith vertex and its associated edges
def dfs(adj, V, vis, i, curr):
    vis[curr] = 1
    for x in adj[curr]:
        if x != i and not vis[x]:
            dfs(adj, V, vis, i, x)

# Function to find Articulation Points in the graph
def AP(adj, V):
    for i in range(1, V + 1):

        # To keep track of number of components of graph
        components = 0

        # To keep track of visited vertices
        vis = [0] * (V + 1)

        # Iterating over the graph after removing vertex i
        # and its associated edges
        for j in range(1, V + 1):
            if j != i:

                # If the jth vertex is not visited, it will
                # form a new component.
                if not vis[j]:

                    # Increasing the number of components.
                    components += 1

                    # dfs call for the jth vertex
                    dfs(adj, V, vis, i, j)

        # If number of components is more than 1 after
        # removing the ith vertex then vertex i is an
        # articulation point.
        if components > 1:
            print(i)

# Utility function to add an edge
def addEdge(adj, u, v):
    adj[u].append(v)
    adj[v].append(u)

# Driver Code
if __name__ == "__main__":
    # Create graphs given in above diagrams
    print("Articulation points in the graph")
    V = 5
    adj1 = [[] for _ in range(V + 1)]
    addEdge(adj1, 1, 2)
    addEdge(adj1, 2, 3)
    addEdge(adj1, 1, 3)
    addEdge(adj1, 3, 4)
    addEdge(adj1, 4, 5)
    AP(adj1, V)

 # This code is contributed by shivamgupta310570
