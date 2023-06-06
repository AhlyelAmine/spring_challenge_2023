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
bool    couted = false;
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

crc read_current_data(int number_of_cells, irc a, int *eggs, int *crystals, int *my_score, int *opp_score)
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

void    print_path(vector<int> vector, int strength)
{
    for (int i = 0; i < vector.size(); i++){
        cout << "BEACON " << vector[i] << " " << strength << ";";
        couted = true;
    }
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
    vector<int> path;
}   t_path;

typedef struct s_data_path
{
    vector<t_path> eggs;
    vector<t_path> crystals;
    vector<t_path> opp_eggs;
    vector<t_path> opp_crystals;
}   t_data_path;

void    earse_index(vector<t_path> *vector, int main_cell)
{
    for (int i = 0; i < vector->size(); i++){
        if ((*vector)[i].main_cell == main_cell)
        {
            vector->erase(vector->begin() + i);
            break ;
        }
    }
}


bool    is_neghibor(irc a, int index, int neighbor)
{
    if (a[index].neigh_0 == neighbor)
        return (true);
    else if (a[index].neigh_1 == neighbor)
        return (true);
    else if (a[index].neigh_2 == neighbor)
        return (true);
    else if (a[index].neigh_3 == neighbor)
        return (true);
    else if (a[index].neigh_4 == neighbor)
        return (true);
    else if (a[index].neigh_5 == neighbor)
        return (true);
    return (false);
}

void    clean_crystals(vector<t_path> *crystals, vector<t_path> *s_crystals)
{
    queue <pair<int, int> > rm_queue;
    for (int i = 0; i < (*crystals).size(); i++){
        if ((*crystals)[i].path.size() <= (*s_crystals)[i].path.size())
            rm_queue.push(pair(1, (*s_crystals)[i].main_cell));
        else
            rm_queue.push(pair(0, (*crystals)[i].main_cell));
    }
    while (!rm_queue.empty()){
        if (rm_queue.front().first)
            earse_index(s_crystals, rm_queue.front().second);
        else if (!rm_queue.front().first)
            earse_index(crystals, rm_queue.front().second);
        rm_queue.pop();
    }
}

void    clean_eggs(vector<t_path> *eggs, vector<t_path> *s_eggs)
{
    queue <pair<int, int> > rm_queue;
    for (int i = 0; i < (*eggs).size(); i++){
        if ((*eggs)[i].path.size() <= (*s_eggs)[i].path.size())
            rm_queue.push(pair(1, (*s_eggs)[i].main_cell));
        else
            rm_queue.push(pair(0, (*eggs)[i].main_cell));
    }
    while (!rm_queue.empty()){
        if (rm_queue.front().first)
            earse_index(s_eggs, rm_queue.front().second);
        else if (!rm_queue.front().first)
            earse_index(eggs, rm_queue.front().second);
        rm_queue.pop();
    }
}

void    clean_path(irc a, vector<t_path> *vec, vector<t_path> *s_vec)
{
    queue <pair<int, int> > rm_queue;
    for (int i = 0; i < vec->size(); i++){
        for (int j = 0; j < s_vec->size(); j++){
            if (is_neghibor(a, (*vec)[i].main_cell, (*s_vec)[j].main_cell)){
                if ((*vec)[i].avrg < (*s_vec)[i].avrg)
                    rm_queue.push(pair(1, (*s_vec)[i].main_cell));
                else
                    rm_queue.push(pair(0, (*vec)[i].main_cell));
            }
        }
    }
    while (!rm_queue.empty()){
        if (rm_queue.front().first)
            earse_index(s_vec, rm_queue.front().second);
        else if (!rm_queue.front().first)
            earse_index(vec, rm_queue.front().second);
        rm_queue.pop();
    }
}

vector<t_data_path>    clean_paths(irc a, vector<t_data_path> data)
{
    clean_eggs(&data[0].eggs, &data[1].eggs);
    clean_eggs(&data[0].opp_eggs, &data[1].opp_eggs);
    clean_crystals(&data[0].crystals, &data[1].crystals);
    clean_crystals(&data[0].opp_crystals, &data[1].opp_crystals);
    clean_path(a, &data[0].eggs, &data[1].eggs);
    clean_path(a, &data[0].opp_eggs, &data[1].opp_eggs);
    clean_path(a, &data[0].crystals, &data[1].crystals);
    clean_path(a, &data[0].opp_crystals, &data[1].opp_crystals);
    return (data);
}

t_path count_data(irc a, crc b, v_int vec)
{
    t_path path;
    path.nbr_cells_have_eggs = 0;
    path.nbr_cells_have_crystals = 0;
    path.eggs = 0;
    path.crystals = 0;
    path.main_cell = vec.back();
    for (int i = 0; i < vec.size(); i++){
        if (a[i].type == 1 && b[i].resources > 0){
            path.eggs += b[i].resources;
            path.nbr_cells_have_eggs++;
        }
        else if (a[i].type == 2 && b[i].resources > 0){
            path.crystals += b[i].resources;
            path.nbr_cells_have_crystals++;
        }
    }
    path.path = vec;
    path.avrg = (path.crystals + path.eggs) / vec.size();
    path.avrg_eggs = path.eggs / vec.size();
    path.avrg_crystals = path.crystals / vec.size();
    return (path);
}

vector<t_data_path>    get_data(irc a, crc b, v_t_bfs my_base, v_t_bfs opp_base, int number_of_bases, int number_of_cells)
{
    vector<t_data_path> data;
    for (int k = 0; k < number_of_bases; k++){
        vector<t_path> eggs;
        vector<t_path> crystals;
        vector<t_path> opp_eggs;
        vector<t_path> opp_crystals;
        for (int i = 0; i < number_of_cells; i++){
            if (a[i].type == 1 && b[i].resources > 0){
                v_int tmp1;
                v_int tmp2;
                find_path(my_base[k], &tmp1, i);
                find_path(opp_base[k], &tmp2, i);
                eggs.push_back(count_data(a, b, tmp1));
                opp_eggs.push_back(count_data(a, b, tmp2));
            }
            else if (a[i].type == 2 && b[i].resources > 0){
                v_int tmp1;
                v_int tmp2;
                find_path(my_base[k], &tmp1, i);
                find_path(opp_base[k], &tmp2, i);
                crystals.push_back(count_data(a, b, tmp1));
                opp_crystals.push_back(count_data(a, b, tmp2));
            }
        }
        data.push_back((t_data_path){eggs, crystals, opp_eggs, opp_crystals});
    }
    if (number_of_bases == 2)
        return (clean_paths(a, data));
    return (data);
}

t_path   collect_path_neighbors(irc a, crc b, t_path container, int type)
{
    bool    change = false;
    for (int j = 0; j < container.path.size(); j++){
        if (a[container.path[j]].neigh_0 != -1 && !is_in(container.path, a[container.path[j]].neigh_0) && b[a[container.path[j]].neigh_0].resources > 0 /*&& (a[a[container.path[j]].neigh_0].type == 1 || type)*/)
        {
            container.path.push_back(a[container.path[j]].neigh_0);
            j = -1;
            change = true;
            continue ;
        }
        if (a[container.path[j]].neigh_1 != -1 && !is_in(container.path, a[container.path[j]].neigh_1) && b[a[container.path[j]].neigh_1].resources > 0 /*&& (a[a[container.path[j]].neigh_1].type == 1 || type)*/)
        {
            container.path.push_back(a[container.path[j]].neigh_1);
            j = -1;
            change = true;
            continue ;
        }
        if (a[container.path[j]].neigh_2 != -1 && !is_in(container.path, a[container.path[j]].neigh_2) && b[a[container.path[j]].neigh_2].resources > 0 /*&& (a[a[container.path[j]].neigh_2].type == 1 || type)*/)
        {
            container.path.push_back(a[container.path[j]].neigh_2);
            j = -1;
            change = true;
            continue ;
        }
        if (a[container.path[j]].neigh_3 != -1 && !is_in(container.path, a[container.path[j]].neigh_3) && b[a[container.path[j]].neigh_3].resources > 0 /*&& (a[a[container.path[j]].neigh_3].type == 1 || type)*/)
        {
            container.path.push_back(a[container.path[j]].neigh_3);
            j = -1;
            change = true;
            continue ;
        }
        if (a[container.path[j]].neigh_4 != -1 && !is_in(container.path, a[container.path[j]].neigh_4) && b[a[container.path[j]].neigh_4].resources > 0 /*&& (a[a[container.path[j]].neigh_4].type == 1 || type)*/)
        {
            container.path.push_back(a[container.path[j]].neigh_4);
            j = -1;
            change = true;
            continue ;
        }
        if (a[container.path[j]].neigh_5 != -1 && !is_in(container.path, a[container.path[j]].neigh_5) && b[a[container.path[j]].neigh_5].resources > 0 /*&& (a[a[container.path[j]].neigh_5].type == 1 || type)*/)
        {
            container.path.push_back(a[container.path[j]].neigh_5);
            j = -1;
            change = true;
            continue ;
        }
    }
    if (change){
        container.eggs = 0;
        container.crystals = 0;
        container.nbr_cells_have_eggs = 0;
        container.nbr_cells_have_crystals = 0;
        for (int j = 0; j < container.path.size(); j++){
            if (b[container.path[j]].resources > 0 && a[container.path[j]].type == 1){
                container.eggs += b[container.path[j]].resources;
                container.nbr_cells_have_eggs++;
            }
            else if (b[container.path[j]].resources > 0 && a[container.path[j]].type == 2) {
                container.crystals += b[container.path[j]].resources;
                container.nbr_cells_have_crystals++;
            }
        }
        container.avrg = (container.eggs + container.crystals) / (double)container.path.size();
        container.avrg_eggs = container.eggs  / (double)container.path.size();
        container.avrg_crystals = container.crystals / (double)container.path.size();
        container.path = container.path;
    }
    return (container);
}

vector<t_data_path>   collect_paths_neighbors(irc a, crc b, int number_of_bases, vector<t_data_path> paths)
{
    for (int i = 0; i < number_of_bases; i++){
        for (int j = 0; j < paths[i].eggs.size(); j++){
            paths[i].eggs[j] = collect_path_neighbors(a, b, paths[i].eggs[j], 1); // 1 to take resources or 0
        }
        for (int j = 0; j < paths[i].crystals.size(); j++){
            paths[i].crystals[j] = collect_path_neighbors(a, b, paths[i].crystals[j], 2);  // 1 or 0
        }
        for (int j = 0; j < paths[i].opp_eggs.size(); j++){
            paths[i].opp_eggs[j] = collect_path_neighbors(a, b, paths[i].opp_eggs[j], 1);
        }
        for (int j = 0; j < paths[i].opp_crystals.size(); j++){
            paths[i].opp_crystals[j] = collect_path_neighbors(a, b, paths[i].opp_crystals[j], 2);
        }
    }
    return (paths);
}

vector<t_path>  chose_best_paths(irc a, crc b, int number_of_bases, vector<t_data_path> paths)
{
    pair <int, int> max;
    vector<t_path> path;

    for (int i = 0; i < paths.size(); i++){
        if (paths[i].eggs.size()){
            max.first = 0;
            max.second = paths[i].eggs[0].fca.fca;
            for (int j = 0; j < paths[i].eggs.size(); j++){
                if (paths[i].eggs[j].fca.fca > max.second){
                    max.first = j;
                    max.second = paths[i].eggs[j].fca.fca;
                }
            }
            path.push_back(paths[i].eggs[max.first]);
        }
        if (paths[i].crystals.size()){
            max.first = 0;
            max.second = paths[i].crystals[0].fca.fca;
            for (int j = 0; j < paths[i].crystals.size(); j++){
                if (paths[i].crystals[j].fca.fca > max.second)
                {
                    max.first = j;
                    max.second = paths[i].crystals[j].fca.fca;
                }
            }
            path.push_back(paths[i].crystals[max.first]);
        }
    }
    return (path);
}

vector<t_path>  chose_best_crystals(irc a, crc b, int number_of_bases, vector<t_data_path> paths)
{
    pair <int, int> max;
    vector<t_path> path;

    for (int i = 0; i < paths.size(); i++){
        if (paths[i].crystals.size()){
            max.first = 0;
            max.second = paths[i].crystals[0].fca.cfca;
            for (int j = 0; j < paths[i].crystals.size(); j++){
                if (paths[i].crystals[j].fca.cfca > max.second)
                {
                    max.first = j;
                    max.second = paths[i].crystals[j].fca.cfca;
                }
            }
            path.push_back(paths[i].crystals[max.first]);
        }
    }
    return (path);
}

vector<t_path>  chose_best_eggs(irc a, crc b, int number_of_bases, vector<t_data_path> paths)
{
    pair <int, int> max;
    vector<t_path> path;

    for (int i = 0; i < paths.size(); i++){
        if (paths[i].eggs.size()){
            max.first = 0;
            max.second = paths[i].eggs[0].fca.efca;
            for (int j = 0; j < paths[i].eggs.size(); j++){
                if (paths[i].eggs[j].fca.efca > max.second){
                    max.first = j;
                    max.second = paths[i].eggs[j].fca.efca;
                }
            }
            path.push_back(paths[i].eggs[max.first]);
        }
    }
    return (path);
}

vector<t_path>    checkout_path_contain_same_resources(crc b,  vector<t_path> path)
{
    for (int i = 0; i < path.size(); i++){
        for (int j = i + 1; j < path.size(); j++){
            int amount = 0;
            for (int k = 0; k < path[i].path.size(); k++){
                if (b[path[i].path[k]].resources > 0 && is_in(path[j].path, path[i].path[k]))
                    amount++;
            }
            if (amount >= (path[i].nbr_cells_have_crystals + path[i].nbr_cells_have_eggs) / 3)
            {
                if (path[i].fca.fca >= path[j].fca.fca)
                    path.erase(path.begin() + j);
                else
                    path.erase(path.begin() + i);
                i--;
                break ;
            }
        }
    }
    return (path);
}

vector<t_path>    compute_fca(crc b,  vector<t_path> path)
{
    for (int i = 0; i < path.size(); i++){
        path[i].fca.my_ants = 0;
        path[i].fca.opp_ants = 0;
        for (int j = 0; j < path[i].path.size(); j++){
            path[i].fca.my_ants += b[path[i].path[j]].my_ants;
            path[i].fca.opp_ants += b[path[i].path[j]].opp_ants;
        }
        path[i].fca.res_avrg = path[i].avrg;
        path[i].fca.my_ants_avrg = path[i].fca.my_ants / path[i].path.size();
        path[i].fca.opp_ants_avrg = path[i].fca.opp_ants / path[i].path.size();
        path[i].fca.efca =(path[i].avrg_eggs * 25) / 100 + (path[i].fca.my_ants * 75 ) / 100;
        path[i].fca.cfca = (path[i].avrg_crystals * 25) /100+ (path[i].fca.my_ants * 75 ) / 100;
        path[i].fca.fca = (path[i].fca.res_avrg *25) / 100+ (path[i].fca.my_ants * 75 ) / 100;
        path[i].fca.fca = (path[i].path.size() * -1) + ((path[i].crystals + path[i].eggs) * 2) + ((path[i].crystals + path[i].eggs) * 2);
    // am here
        Score = (Weight1 * Number of Cases) + (Weight2 * Number of Resources) + (Weight3 * Number of Your Ants) - (Weight4 * Number of Opposite Ants)
    }
    return (path);
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
    int initial_eggs = 0;
    int initial_crystals = 0;
    while (1337) {
        int eggs = 0;
        int crystals = 0;
        if (!loop)
            b = read_current_data(number_of_cells, a, &initial_eggs, &initial_crystals, &my_score, &opp_score);
        else
            b = read_current_data(number_of_cells, a, &eggs, &crystals, &my_score, &opp_score);
        vector<t_data_path> paths;
        vector<t_data_path> new_paths;
        paths = get_data(a, b, my_base, opp_base, number_of_bases, number_of_cells);
        new_paths = collect_paths_neighbors(a, b, number_of_bases, paths);
        vector<t_path> path;
        vector<t_path> path_2;
        cout << "MESSAGE " << (crystals * 100.0) / initial_crystals << " ;";
        // if ((crystals * 100.0) / initial_crystals > 50){
        // cout << "MESSAGE here  ;";
            for (int base = 0; base < number_of_bases; base++){
                new_paths[base].eggs =  compute_fca(b, new_paths[base].eggs);
                new_paths[base].eggs =  checkout_path_contain_same_resources(b, new_paths[base].eggs);
                new_paths[base].crystals =  compute_fca(b, new_paths[base].crystals);
                new_paths[base].crystals =  checkout_path_contain_same_resources(b, new_paths[base].crystals);
                new_paths[base].opp_eggs =  compute_fca(b, new_paths[base].opp_eggs);
                new_paths[base].opp_eggs =  checkout_path_contain_same_resources(b, new_paths[base].opp_eggs);
                new_paths[base].opp_crystals =  compute_fca(b, new_paths[base].opp_crystals);
                new_paths[base].opp_crystals =  checkout_path_contain_same_resources(b, new_paths[base].opp_crystals);
            }
        // }
        if (initial_eggs > initial_crystals || number_of_cells > 32){
            if ((crystals * 100.0) / initial_crystals > 80){
                path = chose_best_eggs(a, b, number_of_bases, new_paths);
            }
            // else
            // {
            //     cout << "MESSAGE HAHAHHAHA!;";
            //     // if ((crystals * 100.0) / initial_crystals > 40)
            //     // {
            //     cout << "MESSAGE HAHAHHAHA!_;";
            //         path = chose_best_crystals(a, b, number_of_bases, new_paths);
            //         // path_2 = chose_best_eggs(a, b, number_of_bases, new_paths);
            //     // }
            //     // else
            //     // {
            //     // cout << "MESSAGE HAHAHHAHA!__;";
            //     //     path = chose_best_crystals(a, b, number_of_bases, new_paths);
            //     //     path_2 = chose_best_eggs(a, b, number_of_bases, new_paths);
            //     // }
            // }
        }
        loop++;

        for (int i = 0; i < path.size(); i++){
            print_path(path[i].path, loop + 1);
        }
        for (int i = 0; i < path_2.size(); i++){
            print_path(path_2[i].path, loop);
        }
        if (!couted)
        {
            cout << "MESSAGE no way O_o :P ;";
            if ((crystals * 100.0) / initial_crystals > 70)
            {
                path_2 = chose_best_paths(a, b, number_of_bases, new_paths);
                path = chose_best_eggs(a, b, number_of_bases, new_paths);
            }
            else
            {
                path = chose_best_paths(a, b, number_of_bases, new_paths);
                if (my_score >= opp_score)
                path_2 = chose_best_eggs(a, b, number_of_bases, new_paths);
            }
        }
        for (int i = 0; i < path.size(); i++){
            print_path(path[i].path,  loop + 1);
        }
        if (!couted){
            for (int i = 0; i < number_of_cells; i++){
                if (b[i].resources > 0)
                    cout << "LINE " << my_base_index[0] << " " << i << " 1;";
            }
        }
        // vector<t_path>  path;
        // // vector<t_path>  path = chose_best_paths(a, b, number_of_bases, paths);
        couted = false;
        cout << endl;
    }
}
