#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef struct s_bfs
{
    int             index;
    struct s_bfs    *neigh_0;
    struct s_bfs    *neigh_1;
    struct s_bfs    *neigh_2;
    struct s_bfs    *neigh_3;
    struct s_bfs    *neigh_4;
    struct s_bfs    *neigh_5;
} t_bfs;

t_bfs *new_bfs(int index)
{
    t_bfs *bfs = (t_bfs *)malloc(sizeof(t_bfs));
    memset(bfs, 0, sizeof(t_bfs));
    bfs->index = index;
    return bfs;
}

t_bfs *go_to_addr(t_bfs *graph, int target)
{
    if (!graph)
        return NULL;
    if (graph->index == target)
        return graph;
    t_bfs *ret = go_to_addr(graph->neigh_0, target);
    if (ret)
        return ret;
    ret = go_to_addr(graph->neigh_1, target);
    if (ret)
        return ret;
    ret = go_to_addr(graph->neigh_2, target);
    if (ret)
        return ret;
    ret = go_to_addr(graph->neigh_3, target);
    if (ret)
        return ret;
    ret = go_to_addr(graph->neigh_4, target);
    if (ret)
        return ret;
    ret = go_to_addr(graph->neigh_5, target);
    return ret;
}

vector<int> get_neighbors(int index)
{
    // Implement your own logic to get the neighbors of a given index
    // and return them as a vector.
    // For example:
    vector<int> neighbors;
    // Fill the neighbors vector with the neighboring indices of the given index.
    // ...
    return neighbors;
}

vector<int> get_neighbors(irc a, int index)
{
    vector<int> neighbors;

    neighbors.push_back(a[index].neigh_0);
    neighbors.push_back(a[index].neigh_1);
    neighbors.push_back(a[index].neigh_2);
    neighbors.push_back(a[index].neigh_3);
    neighbors.push_back(a[index].neigh_4);
    neighbors.push_back(a[index].neigh_5);
    return (neighbors);
}


vector<vector<int>> bfs(int number_of_cells, int start_index, bool (*hasResource)(int))
{
    queue<vector<int>> queue;
    vector<int> visited;
    vector<vector<int>> paths;

    vector<int> initial_path;
    initial_path.push_back(start_index);
    queue.push(initial_path);
    visited.push_back(start_index);

    while (!queue.empty())
    {
        vector<int> current_path = queue.front();
        queue.pop();

        int current_index = current_path.back();

        vector<int> neighbors = get_neighbors(current_index);
        for (int i = 0; i < neighbors.size(); i++)
        {
            int neighbor_index = neighbors[i];
            if (!count(visited.begin(), visited.end(), neighbor_index) && neighbor_index != -1)
            {
                visited.push_back(neighbor_index);

                if (hasResource(neighbor_index))
                {
                    vector<int> new_path = current_path;
                    new_path.push_back(neighbor_index);
                    paths.push_back(new_path);
                }
                else
                {
                    vector<int> new_path = current_path;
                    new_path.push_back(neighbor_index);
                    queue.push(new_path);
                }
            }
        }
    }

    return paths;
}

bool hasResource(int index, crc b)
{
		// Implement your own logic to determine if a given index has a resource.
		// Return true if the index has a resource, false otherwise.
		// For example:
		// return (index % 2 == 0);
    return false;
}

int main()
{
    int number_of_cells = 10; // Example number of cells
    int start_index = 0;      // Example start index

    vector<vector<int>> paths = bfs_path(a, b, number_of_cells, start_index, hasResource);

    // Print the paths
    for (int i = 0; i < paths.size(); i++)
    {
        cout << "Path " << i + 1 << ": ";
        for (int j = 0; j < paths[i].size(); j++)
        {
            cout << paths[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}