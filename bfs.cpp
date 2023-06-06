void BFS(std::vector<std::vector<int>>& graph, int startVertex) {
    int numVertices = graph.size();
    std::vector<bool> visited(numVertices, false);  // Keep track of visited vertices

    // Create a queue for BFS
    std::queue<int> queue;

    // Mark the current vertex as visited and enqueue it
    visited[startVertex] = true;
    queue.push(startVertex);

    while (!queue.empty()) {
        // Dequeue a vertex from the queue and print it
        int currentVertex = queue.front();
        std::cout << currentVertex << " ";
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

int main() {
    // Example graph represented as an adjacency list
    std::vector<std::vector<int>> graph = {
        {1, 2},     // Vertex 0 is connected to vertices 1 and 2
        {2, 3},     // Vertex 1 is connected to vertices 2 and 3
        {0, 3, 4},  // Vertex 2 is connected to vertices 0, 3, and 4
        {3, 4},     // Vertex 3 is connected to vertices 3 and 4
        {4}         // Vertex 4 is connected to vertex 4
    };

    std::cout << "BFS traversal starting from vertex 0: ";
    BFS(graph, 0);

    return 0;
}