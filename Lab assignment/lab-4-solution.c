#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

// Function to fill the adjacency matrix based on user input
void fillGraph(int vertices, int connections, int graph[][vertices])
{
    for (int i = 0; i < connections; i++)
    {
        int start, end;
        printf("Enter the connection between vertices (start, end): ");
        scanf("%d %d", &start, &end);

        // Validate and update adjacency matrix
        if (start >= 0 && start < vertices && end >= 0 && end < vertices)
        {
            graph[start][end] = 1;
        }
        else
        {
            printf("Invalid vertices. Please enter valid vertices.\n");
            i--; // Retry the current connection
        }
    }

    // Optionally, set non-connection cells to 0
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            if (graph[i][j] != 1)
            {
                graph[i][j] = 0;
            }
        }
    }
}

// Function to input weights for edges in the graph
void inputWeights(int vertices, int graph[][vertices])
{
    for (int i = 0; i < vertices; i++)
    {
        printf("Enter weights for edges adjacent to vertex %d (separated by space): ", i);
        for (int j = 0; j < vertices; j++)
        {
            if (graph[i][j] == 1)
            {
                printf("Weight of edge between %d %d: ", i, j);
                scanf("%d", &graph[i][j]);
            }
        }
    }
}

// Function to display the adjacency matrix
void displayGraph(int vertices, int graph[][vertices])
{
    printf("\nAdjacency Matrix:\n");

    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

// Function to find the vertex with minimum distance value
int minDistVertex(int vertices, int dist[], bool pathSet[])
{
    int min = INT_MAX, minVertex;

    for (int v = 0; v < vertices; v++)
    {
        if (!pathSet[v] && dist[v] <= min)
        {
            min = dist[v];
            minVertex = v;
        }
    }

    return minVertex;
}

// Function to print the shortest paths from the source using Dijkstra's algorithm
void printPaths(int vertices, int dist[])
{
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < vertices; i++)
    {
        printf("%d \t\t\t\t %d\n", i, dist[i]);
    }
}

// Function to implement Dijkstra's algorithm for single source shortest path
void dijkstra(int vertices, int graph[][vertices], int source)
{
    int dist[vertices];
    bool pathSet[vertices];

    // Initialize distances and path set
    for (int i = 0; i < vertices; i++)
    {
        dist[i] = INT_MAX;
        pathSet[i] = false;
    }

    dist[source] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < vertices - 1; count++)
    {
        int current = minDistVertex(vertices, dist, pathSet);
        pathSet[current] = true;

        for (int v = 0; v < vertices; v++)
        {
            // Update dist[v] only if it is not in the path set,
            // there is an edge from the current vertex to v,
            // and the total weight of the path from source to v through current
            // is smaller than the current value of dist[v]
            if (!pathSet[v] && graph[current][v] && dist[current] != INT_MAX &&
                dist[current] + graph[current][v] < dist[v])
            {
                dist[v] = dist[current] + graph[current][v];
            }
        }
    }

    // Print the constructed distance array
    printPaths(vertices, dist);
}

// Function to find the vertex with the minimum key value
int minKeyVertex(int vertices, int key[], bool set[])
{
    int min = INT_MAX, minVertex;

    for (int v = 0; v < vertices; v++)
    {
        if (!set[v] && key[v] < min)
        {
            min = key[v];
            minVertex = v;
        }
    }

    return minVertex;
}

// Function to print the edges of the minimum spanning tree (MST)
void printMST(int vertices, int parent[], int graph[][vertices])
{
    printf("Edge\n");
    for (int i = 1; i < vertices; i++)
    {
        printf("%d - %d \n", parent[i], i);
    }
}

// Function to construct and print MST for a graph using Prim's algorithm
void primMST(int vertices, int graph[][vertices])
{
    int parent[vertices];
    int key[vertices];
    bool set[vertices];

    // Initialize keys and set
    for (int i = 0; i < vertices; i++)
    {
        key[i] = INT_MAX;
        set[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    // The MST will have V vertices
    for (int count = 0; count < vertices - 1; count++)
    {
        int current = minKeyVertex(vertices, key, set);
        set[current] = true;

        for (int v = 0; v < vertices; v++)
        {
            // Update the key and parent index of the adjacent vertices of the picked vertex.
            // Consider only those vertices which are not yet included in MST
            if (graph[current][v] && !set[v] && graph[current][v] < key[v])
            {
                parent[v] = current;
                key[v] = graph[current][v];
            }
        }
    }

    // Print the constructed MST
    printMST(vertices, parent, graph);
}

int main()
{
    int V, E;

    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    printf("Enter the number of connections: ");
    scanf("%d", &E);

    int graph[V][V];

    // Initialize the adjacency matrix with zeros
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            graph[i][j] = 0;
        }
    }

    fillGraph(V, E, graph);
    inputWeights(V, graph);
    displayGraph(V, graph);

    int source;
    printf("Enter the source vertex (an integer from 0 to %d): ", V - 1);
    scanf("%d", &source);

    // Apply Dijkstra's algorithm
    dijkstra(V, graph, source);

    // Apply Prim's algorithm for MST
    primMST(V, graph);

    return 0;
}
