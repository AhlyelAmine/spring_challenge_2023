#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;

void bfs(vector<vector<int> >& graph, int startVertex) {
    int numVertices = graph.size();
    vector<bool> visited(numVertices, false);  // Keep track of visited vertices

    // Create a queue for BFS
    queue<int> queue;

    // Mark the current vertex as visited and enqueue it
    visited[startVertex] = true;
    queue.push(startVertex);

    while (!queue.empty()) {
        // Dequeue a vertex from the queue and print it
        int currentVertex = queue.front();
        cout << currentVertex << " ";
        queue.pop();

        // Get all adjacent vertices of the dequeued vertex
        for (int neighbor : graph[currentVertex]) {
            // If a neighbor has not been visited, mark it as visited and enqueue it
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue.push(neighbor);
            }
        }
    }
}