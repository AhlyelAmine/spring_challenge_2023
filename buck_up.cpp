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
bool    couted = false;

class   InitialRessourcesClass
{
    public :
    InitialRessourcesClass(int type_, int initial_resources_, int neigh_0_, int neigh_1_, int neigh_2_, int neigh_3_, int neigh_4_, int neigh_5_){
        this->type = type_;
        this->initial_resources = initial_resources_;
        this->neigh_0 = neigh_0_; 
        this->neigh_1 = neigh_1_;
        this->neigh_2 = neigh_2_;
        this->neigh_3 = neigh_3_;
        this->neigh_4 = neigh_4_;
        this->neigh_5 = neigh_5_;
    }
    int type; // 0 for empty, 1 for eggs, 2 for crystal
    int initial_resources; // the initial amount of eggs/crystals on this cell
    int neigh_0; // the index of the neighbouring cell for each direction
    int neigh_1;
    int neigh_2;
    int neigh_3;
    int neigh_4;
    int neigh_5;
    ~InitialRessourcesClass(){ };
};

class   CurrentRessourcesClass
{
    public :
    CurrentRessourcesClass(int resources_, int my_ants_, int opp_ants_){
        this->resources = resources_;
        this->my_ants = my_ants_;
        this->opp_ants = opp_ants_;
    }
        int resources; // the current amount of eggs/crystals on this cell
        int my_ants; // the amount of your ants on this cell
        int opp_ants; // the amount of opponent ants on this cell
    ~CurrentRessourcesClass(){};
};

#define irc vector<InitialRessourcesClass> 
#define crc vector<CurrentRessourcesClass>

irc read_initial_data(int *number_of_cells, vector<int> *my_base_index, vector<int> *opp_base_index, int *number_of_bases)
{
    irc a;

    cin >> *number_of_cells; cin.ignore();
    for (int i = 0; i < *number_of_cells; i++) {
        int type; // 0 for empty, 1 for eggs, 2 for crystal
        int initial_resources; // the initial amount of eggs/crystals on this cell
        int neigh_0; // the index of the neighbouring cell for each direction
        int neigh_1;
        int neigh_2;
        int neigh_3;
        int neigh_4;
        int neigh_5;
        cin >> type >> initial_resources >> neigh_0 >> neigh_1 >> neigh_2 >> neigh_3 >> neigh_4 >> neigh_5; cin.ignore();
        a.push_back(InitialRessourcesClass(type, initial_resources, neigh_0, neigh_1, neigh_2, neigh_3, neigh_4, neigh_5));
    }
    cin >> *number_of_bases; cin.ignore();
    for (int i = 0; i < *number_of_bases; i++) {
        int index;
        cin >> index; cin.ignore();
        my_base_index->push_back(index);
    }
    for (int i = 0; i < *number_of_bases; i++) {
        int index;
        cin >> index; cin.ignore();
        opp_base_index->push_back(index);
    }
    return (a);
}

crc read_current_data(int number_of_cells, irc a, int *eggs, int *crystals, int *my_score, int *opp_score, int *eggs_cells, int *crystals_cells)
{
    crc b;    

    *eggs_cells = 0;
    *crystals_cells = 0;

	cin >> *my_score >> *opp_score; cin.ignore();
    for (int i = 0; i < number_of_cells; i++) {
        int resources; // the current amount of eggs/crystals on this cell
        int my_ants; // the amount of your ants on this cell
        int opp_ants; // the amount of opponent ants on this cell
        cin >> resources >> my_ants >> opp_ants; cin.ignore();
        if (a[i].type == 1)
        {
            *eggs += resources;
            if (resources > 0)
                (*eggs_cells)++;
        }
        else if (a[i].type == 2){
            if (resources > 0)
                (*crystals_cells)++;
            *crystals += resources;
        }
        b.push_back(CurrentRessourcesClass(resources, my_ants, opp_ants));
    }
    return (b);
}

bool decide = false;

/*--------*/

bool    is_in(vector<int> vec, int index)
{
    for (int i = 0; i < vec.size(); i++){
        if (vec[i] == index)
            return (true);
    }
    return (false);
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

typedef struct s_bfs
{
	int             index;
    struct s_bfs    *neigh_0;
    struct s_bfs    *neigh_1;
    struct s_bfs    *neigh_2;
    struct s_bfs    *neigh_3;
    struct s_bfs    *neigh_4;
    struct s_bfs    *neigh_5;
}	t_bfs;

t_bfs   *new_bfs(int index)
{
    t_bfs       *bfs;

    bfs = (t_bfs *)malloc(sizeof(t_bfs));
    memset(bfs, 0, sizeof(t_bfs));
    bfs->index = index;
    return (bfs);
}

t_bfs   *go_to_addr(t_bfs *graph, int target)
{
    if (!graph)
        return (NULL);
    if (graph->index == target)
        return (graph);
    t_bfs *ret = go_to_addr(graph->neigh_0, target);
    if (ret)
        return (ret);
    ret = go_to_addr(graph->neigh_1, target);
    if (ret)
        return (ret);
    ret = go_to_addr(graph->neigh_2, target);
    if (ret)
        return (ret);
    ret = go_to_addr(graph->neigh_3, target);
    if (ret)
        return (ret);
    ret = go_to_addr(graph->neigh_4, target);
    if (ret)    
        return (ret);
    ret = go_to_addr(graph->neigh_5, target);
    return (ret);
}

void    bfs(int number_of_cells, irc a, int start_index, t_bfs **bfs)
{
    queue<int> queue;
    vector<int> visited;
    t_bfs       *bfs_head;

    queue.push(start_index);
    visited.push_back(start_index);
    *bfs = new_bfs(queue.front());
    bfs_head = *bfs;
    while (!queue.empty()){
        vector<int> tmp = get_neighbors(a, queue.front());
        *bfs = go_to_addr(bfs_head, queue.front());
        for (int i = 0; i < tmp.size(); i++){
            if (!is_in(visited, tmp[i]) && tmp[i] != -1) {
                queue.push(tmp[i]);
                visited.push_back(tmp[i]);
                if (!i && tmp[i] != -1)
                    (*bfs)->neigh_0 = new_bfs(tmp[i]);
                else if (i == 1 && tmp[i] != -1)
                    (*bfs)->neigh_1 = new_bfs(tmp[i]);
                else if (i == 2 && tmp[i] != -1)
                    (*bfs)->neigh_2 = new_bfs(tmp[i]);
                else if (i == 3 && tmp[i] != -1)
                    (*bfs)->neigh_3 = new_bfs(tmp[i]);
                else if (i == 4 && tmp[i] != -1)
                    (*bfs)->neigh_4 = new_bfs(tmp[i]);
                else if (i == 5 && tmp[i] != -1)
                    (*bfs)->neigh_5 = new_bfs(tmp[i]);
            }
        }
        tmp.clear();
        queue.pop();
    }
    *bfs = bfs_head;
}

bool    find_path(t_bfs *map, vector<int> *path, int target)
{
    path->push_back(map->index);
    if (map->index == target)
        return (1);
    if (map->neigh_0)
    {
        if (find_path(map->neigh_0, path, target))
            return (1);
        else
            path->pop_back();
    }
    if (map->neigh_1)
    {
        if (find_path(map->neigh_1, path, target))
            return (1);
        else
            path->pop_back();
    }
    if (map->neigh_2)
    {
        if (find_path(map->neigh_2, path, target))
            return (1);
        else
            path->pop_back();
    }
    if (map->neigh_3)
    {
        if (find_path(map->neigh_3, path, target))
            return (1);
        else
            path->pop_back();
    }
    if (map->neigh_4)
    {
        if (find_path(map->neigh_4, path, target))
            return (1);
        else
            path->pop_back();
    }
    if (map->neigh_5)
    {
        if (find_path(map->neigh_5, path, target))
            return (1);
        else
            path->pop_back();
    }
    return (0);
}

void    print_path(crc b, vector<int> vector, int strength)
{
    int broken = 0;

    for (int i = 0; i < vector.size(); i++){
        if (b[vector[i]].opp_ants > b[vector[i]].my_ants)
            broken++;
    }
    // if (broken > 5)
    // {
        for (int i = 0; i < vector.size(); i++){
            if (b[vector[i]].opp_ants > b[vector[i]].my_ants)
            {
                cout << "BEACON " << vector[i] << " " << strength * 2 << ";";
                couted = true;
            }
            else
            {
                cout << "BEACON " << vector[i] << " " << strength << ";";
                couted = true;
            }
        }
    // }
}
typedef  /* vector on number_of_bases */vector< /* vector on how many paths*/vector< /* pair caontain the path and the size*/pair<int,vector<int> > > > vvp_path;
typedef vector<pair<int,vector<int> > > vp_p;
typedef vector<int>  v_int;
typedef vector <t_bfs*>  v_t_bfs;

typedef struct s_general_avrg
{
    int my_ants;
    int opp_ants;
    int res_avrg;
    int my_ants_avrg;
    int opp_ants_avrg;
    int fca; // final_computed_avrg
    int cfca; // final_computed_avrg
    int efca; // final_computed_avrg
}   t_avrg;

typedef struct s_path
{
    int         main_cell;
    int         eggs;
    int         crystals;
    int         nbr_cells_have_eggs;
    int         nbr_cells_have_crystals;
    int         avrg;
    int         avrg_eggs;
    int         avrg_crystals;
    t_avrg      fca;
    t_bfs       *camera;
    vector<int> path;
}   t_path;

typedef struct s_data_path
{
    vector<t_path> eggs;
    vector<t_path> crystals;
    vector<t_path> opp_eggs;
    vector<t_path> opp_crystals;
}   t_data_path;


bool hasCrystals(int index, crc b, irc a)
{
    if (b[index].resources > 0 && a[index].type == 2)
        return (true);
    return (false);
}

bool hasEggs(int index, crc b, irc a)
{
    if (b[index].resources > 0 && a[index].type == 1)
        return (true);
    return (false);
}

vector<vector<int>> bfs_path(irc a, crc b, int number_of_cells, int start_index, bool (*hasResource)(int, crc, irc))
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

        vector<int> neighbors = get_neighbors(a, current_index);
        for (int i = 0; i < neighbors.size(); i++)
        {
            int neighbor_index = neighbors[i];
            if (!count(visited.begin(), visited.end(), neighbor_index) && neighbor_index != -1)
            {
                visited.push_back(neighbor_index);

                if (hasResource(neighbor_index, b, a))
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

vector<int> find_shortest(vector<vector<int>> paths, vector<int> visited)
{
    vector<int> short_ = paths[0];
    if (visited.size()){
        for (int i = 0; i < paths.size(); i++){
            short_ = paths[i];
            if (!count(visited.begin(), visited.end(), paths[i].back()))
                break;
        }
    }
    for (int i = 0; i < paths.size(); i++){
        if (paths[i].size() < short_.size() && !count(visited.begin(), visited.end(), paths[i].back()))
            short_ = paths[i];
    }
    return (short_);
}

bool is_connected(int index, vector<vector<int>> paths)
{
    for (int i = 0; i < paths.size(); i++){
        if (paths[i].back() == index || paths[i].front() == index)
            return (true);
    }
    return (false);
}



vector<vector<int>> create_efecient_paths(irc a, crc b, vector<int> my_base_index, int cells, int number_of_cells, int number_of_bases, int is_egg)
{
    vector<int>         visited;
    vector<vector<int>> path;
    map<int, vector<vector<int> > > bfsPath;

    for (int i = 0; i < number_of_bases; i++){
        if (is_egg)
            bfsPath.insert(make_pair(my_base_index[i], bfs_path(a, b, number_of_cells, my_base_index[i], hasEggs))); // take all paths have eggs from base in a map
        else
            bfsPath.insert(make_pair(my_base_index[i], bfs_path(a, b, number_of_cells, my_base_index[i], hasCrystals))); // take all paths have eggs from base in a map
        path.push_back(find_shortest(bfsPath.at(my_base_index[i]), visited));
    }
        vector<int> tmp;
    for (int i = 0; i < number_of_cells; i++){
        if (is_egg && a[i].type == 1){
            bfsPath.insert(make_pair(i, bfs_path(a, b, number_of_cells, i, hasEggs))); // take all paths have eggs from base in a map
        }
        else if (!is_egg && a[i].type == 2){
            bfsPath.insert(make_pair(i, bfs_path(a, b, number_of_cells, i, hasCrystals))); // take all paths have eggs from base in a map
        }
    }
    for (int i = 0; i < cells; i++){
        visited.push_back(path.back().back());
        tmp = find_shortest(bfsPath.at(path.back().back()), visited);
        for (map<int, vector<vector<int>>>::iterator it = bfsPath.begin(); it != bfsPath.end(); it++){
            for (int i = 0; i < it->second.size(); i++){
                if (it->second[i].back() == tmp.back()){
                    if (it->second[i].size() < tmp.size() && is_connected(it->second[i].front(), path)){
                        tmp = it->second[i];
                    }
                    break ;
                }
            }
        }
        path.push_back(tmp);
    }
    return (path);
}

vector<vector<vector<int> > > remove_dup_and_sort_paths(vector<vector<int>> path, vector<int> my_base_index)
{
    vector<vector<vector<int> > > container;

    for (int i = 0; i < path.size(); i++){
        for (int j = i + 1; j < path.size(); j++){
            if ((path[i].front() == path[j].front() && path[i].back() == path[j].back()) || (path[i].front() == path[j].back() && path[i].back() == path[j].front()))
                path.erase(path.begin() + j);
        }
    }
    for (int i = 0; i < path.size(); i++){
        for (int j = i + 1; j < path.size(); j++){
            if (path[i].front() == path[j].front() && path[i].back() == path[j].back())
                path.erase(path.begin() + j);
        }
    }
    for (int j = 0; j < path.size(); j++){
        if (count(my_base_index.begin(), my_base_index.end(), path[j].front())){
            vector<vector <int>> push;
            push.push_back(path[j]);
            container.push_back(push);
            path.erase(path.begin() + j);
            j--;
        }
    }
    for (int i = 0; i < container.size(); i ++){
        vector<vector<int> > tmpe;
        for (int j = 0; j < path.size(); j++){
            if (path[j].front() == container[i].back().back()){
                tmpe.push_back(path[j]);
                path.erase(path.begin() + j);
                j--;
            }
        }
        if (tmpe.size())
            couted = true;
        while (tmpe.size()){
            container[i].push_back(tmpe.front());
            tmpe.erase(tmpe.begin());
        }
        if (couted)
            i--;
        couted = false;
    }
    return (container);
}

void    erase_empty_res(crc b, vector<vector<int> > *paths)
{
    for (int i = 0; i < paths->size(); i++){
        if (!(*paths)[i].size())
            continue ;
        for (int j = 0; j < paths->size(); j++){
            if (!(*paths)[j].size() || i == j){
                continue;
            }
            if ((*paths)[i].back() == (*paths)[j].front()){
                couted = true;
                break;
            }
        }
        if (!couted){
            if (b[(*paths)[i].back()].resources == 0){
                (*paths).erase((*paths).begin() + i);
                i--;
            }
        }
        if (i + 1 == paths->size() && paths->size())
        {
            if (b[(*paths)[i].back()].resources == 0){
                (*paths).erase((*paths).begin() + i);
            }
        }
        couted = false;
    }
}
vector<vector<vector<int> > >    select_print(vector<vector<vector<int> > > tmp_path, int sep)
{
    vector<vector<int> > tmp;
    vector<vector<vector<int> > > print;
    int size = 0;
    while (size <= sep && tmp_path.size()){
        print.resize(tmp_path.size());
        for (int i = 0; i < tmp_path.size(); i++){
            if (tmp_path[i].size())
                couted = true;
        }
        if (!couted)
            break ;
        couted = false;
        for (int i = 0; i < tmp_path.size(); i++){
            if (tmp_path[i].size())
                tmp.push_back(tmp_path[i].front());
            else
                tmp.push_back({-1});
        }
        pair<int, int> min = make_pair(0, tmp[0].size()); // should replace if equal - 1
        for (int i = 0; i < tmp.size(); i++){
            min = pair(i, tmp[i].size());
            if (tmp[0][0] != -1)
                break;
        }
        for (int i = 0; i < tmp.size(); i++){
            if (tmp[i].size() < min.second && tmp[i][0] != -1)
                min = pair(i, tmp[i].size());
        }
        size += min.second;
        if (tmp[min.first].size() && tmp[min.first][0] != -1){
        print[min.first].push_back(tmp_path[min.first].front());
        tmp_path[min.first].erase(tmp_path[min.first].begin());

        }
        tmp.clear();
    }
    return (print);
}
int main()
{
    irc         a;
    crc         b;
    int         number_of_bases;
    v_int       my_base_index;
    v_int       opp_base_index;
    int         number_of_cells; // amount of hexagonal cells in this map
    int         loop = 0;
    int         my_score; // amount of hexagonal cells in this map
    int         opp_score;
    vector<vector<int>> holder;
    vector<vector<int>> paths_egg;
    vector<vector<int>> paths_crystal;
    int cells_eggs;
    int nul;
    int cells_crystals;
    int initial_eggs = 0;
    int initial_crystals = 0;
    vector<vector<vector<int> > > container_egg;
    vector<vector<vector<int> > > container_crystal;
    a = read_initial_data(&number_of_cells, &my_base_index, &opp_base_index, &number_of_bases);
    while (1337) {
        int my_ants = 0;
        int eggs = 0;
        int crystals = 0;
        if (!loop)
        {
            b = read_current_data(number_of_cells, a, &initial_eggs, &initial_crystals, &my_score, &opp_score, &cells_eggs, &cells_crystals);
            eggs = initial_eggs;
            crystals = initial_crystals;
        }
        else
            b = read_current_data(number_of_cells, a, &eggs, &crystals, &my_score, &opp_score, &cells_eggs, &cells_crystals);
        try {
            if (cells_eggs){
                paths_egg = create_efecient_paths(a, b, my_base_index, cells_eggs, number_of_cells, number_of_bases, 1);
                container_egg = remove_dup_and_sort_paths(paths_egg, my_base_index);
            }
            if (cells_crystals){
                paths_crystal = create_efecient_paths(a, b, my_base_index, cells_crystals, number_of_cells, number_of_bases, 0);
                container_crystal = remove_dup_and_sort_paths(paths_crystal, my_base_index);
            }
            for (int i = 0; i < number_of_cells; i++){
                my_ants += b[i].my_ants;
            }
            vector<vector<vector<int> > > tmp_egg = container_egg;
            vector<vector<vector<int> > > tmp_crystal = container_crystal;
            vector<vector<vector<int> > > print_egg;
            vector<vector<vector<int> > > print_crystal;
            int sep;
            sep = my_ants / (2 * number_of_bases);
            if (cells_eggs){
                print_egg = select_print(tmp_egg, sep);
            }
            if (cells_crystals){
                print_crystal = select_print(tmp_crystal, sep);
            }
            if ((eggs * 100.0) / initial_eggs > 0){
                for (int i = 0; i < print_egg.size(); i++){
                    for (int j = 0; j < print_egg[i].size(); j++){
                        cout << "LINE " << print_egg[i][j].front() << " " << print_egg[i][j].back() << " 2;";
                        couted = true;
                    }
                }
            }
            if (((crystals * 100.0) / initial_crystals < 75.0 && (crystals * 100.0) / initial_crystals > 50.0)){
                for (int i = 0; i <  print_crystal.size(); i++){
                    for (int j = 0; j < print_crystal[i].size(); j++){
                        cout << "MESSAGE " << (crystals * 100.0) / initial_crystals <<"am here ;";
                        cout << "LINE " << print_crystal[i][j].front() << " " << print_crystal[i][j].back() << " 1;";
                        couted = true;
                    }
                }
            }
            if (!couted ||  (crystals * 100.0) / initial_crystals <= 50.0){
                for (int i = 0; i < container_crystal.size(); i++){
                    for (int j = 0; j < container_crystal[i].size(); j++){
                        cout << "LINE " << container_crystal[i][j].front() << " " << container_crystal[i][j].back() << " 1;";
                        couted = true;
                    }
                }
            }
            print_egg.clear();
            if (!couted){
                cout << "WAIT";
            }
            couted = false;
            loop++;
            cout << endl;

        } catch (exception&e) {
            cout << "WAIT;" << endl;
        }
    }
}
