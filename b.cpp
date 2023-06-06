# include <iostream>
# include <string>
# include <vector>
# include <bits/stdc++.h>
# include <cstdlib>
# include <algorithm>
#include <cmath>
using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
bool couted = false;


class Cell {
    public:
        int index, cellType, resources, myAnts, oppAnts;
        vector<int> neighbors;

        Cell(int index, int cellType, int resources, vector<int> neighbors, int myAnts = 0, int oppAnts = 0) {
            this->index = index;
            this->cellType = cellType;
            this->resources = resources;
            this->neighbors = neighbors;
            this->myAnts = myAnts;
            this->oppAnts = oppAnts;
        }
};

vector<int> findShortestPath(int a, int b, vector<Cell> &g) {
    queue<int> q;
    vector<int> prev(g.size(), -1);
    vector<bool> vis(g.size());

    q.push(a);
    vis[a]=1;

    while (!q.empty()) {
        if (prev[b] != -1) break ;
        int head = q.front(); q.pop();

        vector<int> neigh;
        for (auto &i : g[head].neighbors)
            if(i!=-1) neigh.push_back(i);

        sort(neigh.begin(), neigh.end(), [&](int &a, int &b) {
            return g[a].myAnts > g[b].myAnts;
        });


        for (int u: neigh) {
            if (vis[u]) continue;
            prev[u] = head;
            vis[u] = 1;
            q.push(u);
        }
    }

    if (!vis[b]) return {};

    int curr = b;
    vector<int> path;
    while (curr != -1) {
        path.push_back(curr);
        curr = prev[curr];
    }

    return reverse(path.begin(), path.end()), path;
}
int main()
{
    int init_eggs = 0;
    int eggs;
    int init_crystals = 0;
    int crystals;
    vector<Cell> _map;
    int number_of_cells; // amount of hexagonal cells in this map
    cin >> number_of_cells; cin.ignore();
    for (int i = 0; i < number_of_cells; i++) {
        int type; // 0 for empty, 1 for eggs, 2 for crystal
        int initial_resources; // the initial amount of eggs/crystals on this cell
        int neigh_0; // the index of the neighbouring cell for each direction
        int neigh_1;
        int neigh_2;
        int neigh_3;
        int neigh_4;
        int neigh_5;
        if (type == 1)
            init_eggs += initial_resources;
        if(type == 2)
            init_crystals += initial_resources;
        cin >> type >> initial_resources >> neigh_0 >> neigh_1 >> neigh_2 >> neigh_3 >> neigh_4 >> neigh_5; cin.ignore();
        Cell tmp(i, type, initial_resources, {neigh_0,neigh_1,neigh_2,neigh_3,neigh_4,neigh_5});
        _map.push_back(tmp);
    }
    int number_of_bases;
    cin >> number_of_bases; cin.ignore();
    vector<int>my_base_index;

    for (int i = 0; i < number_of_bases; i++) {
        int a;
        cin >> a; cin.ignore();
        my_base_index.push_back(a);
    }
    vector<int> opp_base_index;
    for (int i = 0; i < number_of_bases; i++) {
        int a;
        cin >> a; cin.ignore();
        opp_base_index.push_back(a);
    }

    // game loop
    while (1) {
        int my_score;
        int opp_score;
        eggs = 0;
        crystals = 0;
        cin >> my_score >> opp_score; cin.ignore();
        for (int i = 0; i < number_of_cells; i++) {
            int resources; // the current amount of eggs/crystals on this cell
            int my_ants; // the amount of your ants on this cell
            int opp_ants; // the amount of opponent ants on this cell
            _map[i].resources = resources;
            _map[i].myAnts = my_ants;
            _map[i].oppAnts = opp_ants;
            cin >> resources >> my_ants >> opp_ants; cin.ignore();
            if (_map[i].cellType == 1)
                eggs += resources;
            if(_map[i].cellType == 2)
                crystals += resources;
        }
        int my_ants = 0;
        for (int i = 0; i < number_of_cells; i++){
            my_ants += _map[i].myAnts;
        }
        int size = 0;
        cout << "MESSAGE " << (crystals * 100) /  init_crystals << ";";
        if (eggs && (crystals * 100) /  init_crystals > 70){
            size = 0;
            cout << "MESSAGE a;";
            for (int i = 0; i < number_of_cells; i++){
                if (_map[i].cellType == 1 && _map[i].resources > 0){
                    vector<vector <int>> path;
                    vector<vector <int>> opp_path;
                    for (int b = 0; b < number_of_bases; b++){
                        path.push_back(findShortestPath(my_base_index[b], i, _map));
                        opp_path.push_back(findShortestPath(opp_base_index[b], i, _map));
                    }
                    vector<int> final_path = path[0];
                    for (int i = 0; i < number_of_bases; i++){
                        if (path[i].size() < final_path.size()){
                            final_path = path[i];
                        }
                    }
                    bool valid = true;
                    for (int i = 0; i < number_of_bases; i++){
                        if (opp_path[i].size() + 4 < final_path.size()){
                            valid = false;
                        }
                    }
                    if (valid){
                        size += final_path.size();
                        if (my_ants / 2 < size)
                            break;
                        cout << "MESSAGE " << size << " " << my_ants << ";";
                        for (int i = 0; i < final_path.size(); i++){
                            cout << "BEACON " << final_path[i] << " 1;";
                            couted = true;
                        }
                    }
                }
            }
        }
        else if (eggs && (((crystals * 100) /  init_crystals <= 70 && (crystals * 100) /  init_crystals > 45) || (eggs * 100) /  init_eggs <= 70)){
            size = 0;
            cout << "MESSAGE b;";

            for (int i = 0; i < number_of_cells; i++){
                if (_map[i].cellType == 1 && _map[i].resources > 0){
                    vector<vector <int>> path;
                    vector<vector <int>> opp_path;
                    for (int b = 0; b < number_of_bases; b++){
                        path.push_back(findShortestPath(my_base_index[b], i, _map));
                        opp_path.push_back(findShortestPath(opp_base_index[b], i, _map));
                    }
                    vector<int> final_path = path[0];
                    for (int i = 0; i < number_of_bases; i++){
                        if (path[i].size() < final_path.size()){
                            final_path = path[i];
                        }
                    }
                    bool valid = true;
                    for (int i = 0; i < number_of_bases; i++){
                        if (opp_path[i].size() + 4 < final_path.size()){
                            valid = false;
                        }
                    }
                    if (valid){
                        size += final_path.size();
                        if (my_ants / 2 < size)
                            break;
                        cout << "MESSAGE " << size << " " << my_ants << ";";
                        for (int i = 0; i < final_path.size(); i++){
                            cout << "BEACON " << final_path[i] << " 2;";
                            couted = true;
                        }
                    }
                }
            }
            size = 0;
            for (int i = 0; i < number_of_cells; i++){
                if (_map[i].cellType == 2 && _map[i].resources > 0){
                    vector<vector <int>> path;
                    vector<vector <int>> opp_path;
                    for (int b = 0; b < number_of_bases; b++){
                        path.push_back(findShortestPath(my_base_index[b], i, _map));
                        opp_path.push_back(findShortestPath(opp_base_index[b], i, _map));
                    }
                    vector<int> final_path = path[0];
                    for (int i = 0; i < number_of_bases; i++){
                        if (path[i].size() < final_path.size()){
                            final_path = path[i];
                        }
                    }
                    bool valid = true;
                    for (int i = 0; i < number_of_bases; i++){
                        if (opp_path[i].size() + 4 < final_path.size()){
                            valid = false;
                        }
                    }
                    cout<< "MESSAGE "<< valid << " yo;";
                    if (valid){
                        size += final_path.size();
                        if (my_ants / 2 < size)
                            break;
                        for (int i = 0; i < final_path.size(); i++){
                            cout << "BEACON " << final_path[i] << " 1;";
                            couted = true;
                        }
                    }
                }
            }
        }
        else{
            cout << "MESSAGE c;";
            size = 0;
            for (int i = 0; i < number_of_cells; i++){
                if (_map[i].cellType == 2 && _map[i].resources > 0){
                    vector<vector <int>> path;
                    vector<vector <int>> opp_path;
                    for (int b = 0; b < number_of_bases; b++){
                        path.push_back(findShortestPath(my_base_index[b], i, _map));
                        opp_path.push_back(findShortestPath(opp_base_index[b], i, _map));
                    }
                    vector<int> final_path = path[0];
                    for (int i = 0; i < number_of_bases; i++){
                        if (path[i].size() < final_path.size()){
                            final_path = path[i];
                        }
                    }
                    bool valid = true;
                    for (int i = 0; i < number_of_bases; i++){
                        if (opp_path[i].size() + 4 < final_path.size()){
                            valid = false;
                        }
                    }
                    if (valid){
                        size += final_path.size();
                        if (my_ants < size)
                            break;
                        for (int i = 0; i < final_path.size(); i++){
                            
                            cout << "BEACON " << final_path[i] << " 1;";
                            couted = true;
                        }
                        size += final_path.size();
                    }
                }
            }
        }
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;


        // WAIT | LINE <sourceIdx> <targetIdx> <strength> | BEACON <cellIdx> <strength> | MESSAGE <text>
        cout << endl;
    }
}