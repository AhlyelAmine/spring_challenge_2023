# include <iostream>
# include <string>
# include <vector>
# include <bits/stdc++.h>
# include <cstdlib>
# include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

typedef struct s_map_tree
{
    int index:8;
    struct s_map_tree  *n_0;
    struct s_map_tree  *n_1;
    struct s_map_tree  *n_2;
    struct s_map_tree  *n_3;
    struct s_map_tree  *n_4;
    struct s_map_tree  *n_5;
}   t_tree;

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

crc read_current_data(int number_of_cells, irc a, int *eggs, int *crystals, int &my_score, int &opp_score)
{
    crc b;    

	cin >> *my_score >> *opp_score; cin.ignore();
    for (int i = 0; i < number_of_cells; i++) {
        int resources; // the current amount of eggs/crystals on this cell
        int my_ants; // the amount of your ants on this cell
        int opp_ants; // the amount of opponent ants on this cell
        cin >> resources >> my_ants >> opp_ants; cin.ignore();
        if (a[i].type == 1)
            *eggs += resources;
        else if (a[i].type == 2)
            *crystals += resources;
        b.push_back(CurrentRessourcesClass(resources, my_ants, opp_ants));
    }
    return (b);
}

bool decide = false;

void    neighbor_have_eggs(irc a, crc b, int index)
{
    if (a[index].neigh_0 != -1 && b[a[index].neigh_0].resources > 0 && a[a[index].neigh_0].type == 1)
    {
        cout << "LINE " << a[index].neigh_0 << " " << index << " 2;";
        decide = true;
    }
    if (a[index].neigh_1 != -1 && b[a[index].neigh_1].resources > 0 && a[a[index].neigh_1].type == 1)
    {
        cout << "LINE " << a[index].neigh_1 << " " << index << " 2;";
        decide = true;
    }
    if (a[index].neigh_2 != -1 && b[a[index].neigh_2].resources > 0 && a[a[index].neigh_2].type == 1)
    {
        cout << "LINE " << a[index].neigh_2 << " " << index << " 2;";
        decide = true;
    }
    if (a[index].neigh_3 != -1 && b[a[index].neigh_3].resources > 0 && a[a[index].neigh_3].type == 1)
    {
        cout << "LINE " << a[index].neigh_3 << " " << index << " 2;";
        decide = true;
    }
    if (a[index].neigh_4 != -1 && b[a[index].neigh_4].resources > 0 && a[a[index].neigh_4].type == 1)
    {
        cout << "LINE " << a[index].neigh_4 << " " << index << " 2;";
        decide = true;
    }
    if (a[index].neigh_5 != -1 && b[a[index].neigh_5].resources > 0 && a[a[index].neigh_5].type == 1)
    {
        cout << "LINE " << a[index].neigh_5 << " " << index << " 2;";
        decide = true;
    }
}


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

void    print_tree(t_bfs *bfs)
{
    if (!bfs)
        return ;
    print_tree((t_bfs *)bfs->neigh_0);
    print_tree((t_bfs *)bfs->neigh_1);
    print_tree((t_bfs *)bfs->neigh_2);
    print_tree((t_bfs *)bfs->neigh_3);
    print_tree((t_bfs *)bfs->neigh_4);
    print_tree((t_bfs *)bfs->neigh_5);
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

void    print_path(vector<int> vector, int strength)
{
    for (int i = 0; i < vector.size(); i++){
        cout << "BEACON " << vector[i] << " " << strength << ";";
    }
}
typedef  /* vector on number_of_bases */vector< /* vector on how many paths*/vector< /* pair caontain the path and the size*/pair<int,vector<int> > > > vvp_path;
typedef vector<pair<int,vector<int> > > vp_p;
typedef vector<int>  v_int;
typedef vector <t_bfs*>  v_t_bfs;

void    clean_path(int number_of_bases, vvp_path *path)
{
    vector<pair<int, int> > remove;
    for (int i = 0; i < number_of_bases; i++){
        for (int j = 0; j <  (*path)[i].size(); j++){
            cout << "MESSAGE  data _START : ";
            for (int k = 0; k < (*path)[i][j].second.size(); k++){
                cout << " " << (*path)[i][j].second[k] << " ";
            }
            cout << " _END ; ";
        }
    }
    for (int i = 0; i < (*path)[0].size(); i++){
        if ((*path)[0][i].first < (*path)[1][i].first)
            remove.push_back(pair(1, i));
        else
            remove.push_back(pair(0, i));
    }
    for (int i = 0; i < remove.size(); i++){
        (*path)[remove[i].first].erase((*path)[remove[i].first].begin() + remove[i].second);
    }
    remove.clear();
}

void    clean_paths(int number_of_bases, vvp_path *eggs_container,vvp_path *crystals_container,vvp_path *opp_eggs_container,vvp_path *opp_crystals_container)
{
    clean_path(number_of_bases, eggs_container);
    clean_path(number_of_bases, crystals_container);
    clean_path(number_of_bases, opp_eggs_container);
    clean_path(number_of_bases, opp_crystals_container);
}

void    get_data(irc a, crc b, v_t_bfs my_base, v_t_bfs opp_base, int number_of_bases, int number_of_cells, vvp_path *eggs_container, vvp_path *crystals_container, vvp_path *opp_eggs_container, vvp_path *opp_crystals_container)
{

    for (int k = 0; k < number_of_bases; k++){
        vp_p egg_container;
        vp_p crystal_container;
        vp_p opp_egg_container;
        vp_p opp_crystal_container;
        for (int i = 0; i < number_of_cells; i++){
            if (a[i].type == 1 && b[i].resources > 0){
                v_int tmp1;
                v_int tmp2;
                find_path(my_base[k], &tmp1, i);
                find_path(opp_base[k], &tmp2, i);
                egg_container.push_back(pair(tmp1.size(), tmp1));
                opp_egg_container.push_back(pair(tmp2.size(), tmp2));
                tmp1.clear();
                tmp2.clear();
            }
            else if (a[i].type == 2 && b[i].resources > 0){
                v_int tmp1;
                v_int tmp2;
                find_path(my_base[k], &tmp1, i);
                find_path(opp_base[k], &tmp2, i);
                crystal_container.push_back(pair(tmp1.size(), tmp1));
                opp_crystal_container.push_back(pair(tmp2.size(), tmp2));
                tmp1.clear();
                tmp2.clear();
            }
        }
        eggs_container->push_back(egg_container);
        crystals_container->push_back(crystal_container);
        opp_eggs_container->push_back(opp_egg_container);
        opp_crystals_container->push_back(opp_crystal_container);
    }
    if (number_of_bases == 2)
        clean_paths(number_of_bases, eggs_container, crystals_container, opp_eggs_container, opp_crystals_container);
}

typedef struct s_path
{
    int         main_cell;
    int         eggs;
    int         crystals;
    int         nbr_cells_have_eggs;
    int         nbr_cells_have_crystals;
    double      avrg;
    double      avrg_eggs;
    double      avrg_crystals;
    vector<int> path;
}   t_path;

typedef struct s_data_path
{
    vector<t_path> eggs;
    vector<t_path> crystals;
    vector<t_path> opp_eggs;
    vector<t_path> opp_crystals;
}   t_data_path;

t_path   collect_path_neighbors(irc a, crc b, vp_p container)
{
    t_path path;

    for (int i = 0; i < container.size(); i++){
        path.main_cell = container[i].second.back();
        for (int j = 0; j < container[i].second.size(); j++){
            if (a[container[i].second[j]].neigh_0 != -1 && !is_in(container[i].second, a[container[i].second[j]].neigh_0) && b[a[container[i].second[j]].neigh_0].resources > 0)
                container[i].second.push_back(a[container[i].second[j]].neigh_0);
            if (a[container[i].second[j]].neigh_1 != -1 && !is_in(container[i].second, a[container[i].second[j]].neigh_1) && b[a[container[i].second[j]].neigh_1].resources > 0)
                container[i].second.push_back(a[container[i].second[j]].neigh_1);
            if (a[container[i].second[j]].neigh_2 != -1 && !is_in(container[i].second, a[container[i].second[j]].neigh_2) && b[a[container[i].second[j]].neigh_2].resources > 0)
                container[i].second.push_back(a[container[i].second[j]].neigh_2);
            if (a[container[i].second[j]].neigh_3 != -1 && !is_in(container[i].second, a[container[i].second[j]].neigh_3) && b[a[container[i].second[j]].neigh_3].resources > 0)
                container[i].second.push_back(a[container[i].second[j]].neigh_3);
            if (a[container[i].second[j]].neigh_4 != -1 && !is_in(container[i].second, a[container[i].second[j]].neigh_4) && b[a[container[i].second[j]].neigh_4].resources > 0)
                container[i].second.push_back(a[container[i].second[j]].neigh_4);
            if (a[container[i].second[j]].neigh_5 != -1 && !is_in(container[i].second, a[container[i].second[j]].neigh_5) && b[a[container[i].second[j]].neigh_5].resources > 0)
                container[i].second.push_back(a[container[i].second[j]].neigh_5);
        }
        path.eggs = 0;
        path.crystals = 0;
        path.nbr_cells_have_eggs = 0;
        path.nbr_cells_have_crystals = 0;
        for (int j = 0; j < container[i].second.size(); j++){
            if (b[container[i].second[j]].resources > 0 && a[container[i].second[j]].type == 1){
                path.eggs += b[container[i].second[j]].resources;
                path.nbr_cells_have_eggs++;
            }
            else if (b[container[i].second[j]].resources > 0 && a[container[i].second[j]].type == 2) {
                path.crystals += b[container[i].second[j]].resources;
                path.nbr_cells_have_crystals++;
            }
        }
        path.avrg = (path.eggs + path.crystals) / (double)container[i].second.size();
        path.avrg_eggs = path.eggs  / (double)container[i].second.size();
        path.avrg_crystals = path.crystals / (double)container[i].second.size();
        path.path = container[i].second;
    }
    return (path);
}

vector<t_data_path>   collect_paths_neighbors(irc a, crc b, int number_of_bases, vvp_path eggs_container, vvp_path crystals_container, vvp_path opp_eggs_container, vvp_path opp_crystals_container)
{
    vector<t_data_path> data;
    vector<t_path>      eggs;
    vector<t_path>      crystals;
    vector<t_path>      opp_eggs;
    vector<t_path>      opp_crystals;

    for (int i = 0; i < number_of_bases; i++){
        for (int j = 0; j < eggs_container[i].size(); j++){
        }
        for (int j = 0; j < crystals_container[i].size(); j++){
            crystals.push_back(collect_path_neighbors(a, b, crystals_container[i]));
        }
        for (int j = 0; j < opp_eggs_container[i].size(); j++){
            opp_eggs.push_back(collect_path_neighbors(a, b, opp_eggs_container[i]));
        }
        for (int j = 0; j < opp_crystals_container[i].size(); j++){
            opp_crystals.push_back(collect_path_neighbors(a, b, opp_crystals_container[i]));
        }
        data.push_back((t_data_path){eggs, crystals, opp_eggs, opp_crystals});
    }
    return (data);
}

vector<vector<int> > chose_best_paths(irc a, crc b, int number_of_bases, vector<t_data_path> paths)
{
    pair <int, double> max;
    vector<vector<int> > path;
    for (int i = 0; i < paths.size(); i++){
        max = pair(0, paths[i].crystals[0].avrg);
        for (int j = 0; j < paths[i].crystals.size(); j++){
            if (paths[i].crystals[j].avrg > max.second)
                max = pair(j, paths[i].crystals[j].avrg);
        }
        path.push_back(paths[i].crystals[max.first].path);
        max = pair(0, paths[i].eggs[0].avrg);
        for (int j = 0; j < paths[i].eggs.size(); j++){
            if (paths[i].eggs[j].avrg > max.second)
                max = pair(j, paths[i].eggs[j].avrg);
        }
        path.push_back(paths[i].eggs[max.first].path);
    }
    return(path);
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
    a = read_initial_data(&number_of_cells, &my_base_index, &opp_base_index, &number_of_bases);


    v_t_bfs my_base;
    v_t_bfs opp_base;
    for (int i = 0; i < number_of_bases; i++){
        t_bfs* nul = NULL;
        bfs(number_of_cells, a, my_base_index[i], &nul);
        my_base.push_back(nul);
        nul = NULL;
        bfs(number_of_cells, a, opp_base_index[i], &nul);
        opp_base.push_back(nul);
    }
    while (1) {
        int eggs = 0;
        int crystals = 0;
        b = read_current_data(number_of_cells, a, &eggs, &crystals);

        vvp_path eggs_container;
        vvp_path crystals_container;
        vvp_path opp_eggs_container;
        vvp_path opp_crystals_container;
        get_data(a, b, my_base, opp_base, number_of_bases, number_of_cells, &eggs_container, &crystals_container, &opp_eggs_container, &opp_crystals_container);
        vector<t_data_path> paths= collect_paths_neighbors(a, b, number_of_bases, eggs_container, crystals_container, opp_eggs_container, opp_crystals_container);
        cout << "MESSAGE START ;";
        for (int i = 0; i < number_of_bases; i++){
            for (int j = 0; j < paths[i].eggs.size(); j++){
                print_path(paths[i].eggs[j].path, 1);
            }
            for (int j = 0; j < paths[i].crystals.size(); j++){
                print_path(paths[i].crystals[j].path, 1);
            }
        }
        cout << "MESSAGE END ;";
        vector<vector<int> > path = chose_best_paths(a, b, number_of_bases, paths);
        for (int i = 0; i < number_of_bases; i++){
            print_path(path[i], 1);
        }
        loop++;
        cout << endl;
    }
}
