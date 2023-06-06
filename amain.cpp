#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct Resource {
    int x;
    int y;
    int index;

    Resource(int x_, int y_, int index_) : x(x_), y(y_), index(index_) {}
};

struct CompareResources {
    bool operator()(const Resource& a, const Resource& b) {
        return a.x < b.x;
    }
};

int distance(const Resource& a, const Resource& b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    int distance = std::abs(dx);
    distance += std::max(0, std::abs(dx + (dy - (dy & 1)) / 2));
    return distance;
}

void sortPaths(std::vector<std::vector<int> >& paths) {
    std::vector<Resource> resources;

    for (int i = 0; i < paths.size(); ++i) {
        resources.push_back(Resource(paths[i][0], paths[i][1], i));
    }

    std::sort(resources.begin() + 1, resources.end(), CompareResources());

    std::vector<std::vector<int> > sortedPaths;
    sortedPaths.reserve(paths.size());

    sortedPaths.push_back(paths[0]);

    for (int i = 1; i < resources.size(); ++i) {
        const Resource& currentResource = resources[i];
        int minDistance = std::numeric_limits<int>::max();
        int closestPathIndex = -1;

        for (int j = 0; j < paths.size(); ++j) {
            int d = distance(currentResource, Resource(paths[j][0], paths[j][1], j));
            if (d < minDistance) {
                minDistance = d;
                closestPathIndex = j;
            }
        }

        sortedPaths.push_back(paths[closestPathIndex]);
    }

    sortedPaths.push_back(paths[0]);  // Connect last element to the first element

    paths = sortedPaths;
}

void printTree(const std::vector<std::vector<int> >& paths, int current, int level) {
    if (current >= paths.size()) {
        return;
    }

    for (int i = 0; i < level; ++i) {
        std::cout << "  ";
    }

    std::cout << "(" << paths[current][0] << ", " << paths[current][1] << ")" << std::endl;

    printTree(paths, current * 2 + 1, level + 1);
    printTree(paths, current * 2 + 2, level + 1);
}

int main() {
    std::vector<std::vector<int> > paths;
    std::vector<int> path1, path2, path3, path4, path5;
    path1.push_back(39);
    path1.push_back(72);
    paths.push_back(path1);
    path2.push_back(41);
    path2.push_back(43);
    paths.push_back(path2);
    path3.push_back(41);
    path3.push_back(39);
    paths.push_back(path3);
    path4.push_back(42);
    path4.push_back(40);
    paths.push_back(path4);
    path5.push_back(44);
    path5.push_back(42);
    paths.push_back(path5);
    sortPaths(paths);
    printTree(paths, 0, 0);
    return 0;
}



// MESSAGE  (15, 31),  (10, 4),  (4, 3),  (15, 34),  (10, 32),  (32, 33), ;


