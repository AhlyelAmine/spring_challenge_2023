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

crc read_current_data(int number_of_cells, irc a, int *eggs, int *crystals)
{
    crc b;    

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
    }
}

void    print_path_line(irc a, crc b, vector<int> vector, int strength)
{
    for (int i = 0; i < vector.size(); i++){
        if (a[vector[i]].type == 2 && b[vector[i]].resources > 0)
        cout << "LINE " << vector[i] << " " << vector.front() << " 1;";
    }
}

void    get_data(irc a, crc b, vector <t_bfs*> my_base, vector <t_bfs*> opp_base, int number_of_bases, int number_of_cells, vector<vector<pair<int,vector<int> > > > *eggs_container, vector<vector<pair<int,vector<int> > > > *crystals_container, vector<vector<pair<int,vector<int> > > > *opp_eggs_container, vector<vector<pair<int,vector<int> > > > *opp_crystals_container)
{
    for (int k = 0; k < number_of_bases; k++){
        vector<pair<int,vector<int> > > egg_container;
        vector<pair<int,vector<int> > > crystal_container;
        vector<pair<int,vector<int> > > opp_egg_container;
        vector<pair<int,vector<int> > > opp_crystal_container;
        for (int i = 0; i < number_of_cells; i++){
            if (a[i].type == 1 && b[i].resources > 0){
                vector<int> tmp1;
                vector<int> tmp2;
                find_path(my_base[k], &tmp1, i);
                find_path(opp_base[k], &tmp2, i);
                egg_container.push_back(pair(tmp1.size(), tmp1));
                opp_egg_container.push_back(pair(tmp2.size(), tmp2));
                tmp1.clear();
                tmp2.clear();
            }
            else if (a[i].type == 2 && b[i].resources > 0){
                vector<int> tmp1;
                vector<int> tmp2;
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
    if (number_of_bases == 2){
        for (int i = 0; i < (*eggs_container)[0].size(); i++){
            if ((*eggs_container)[0][i].first < (*eggs_container)[1][i].first){
                (*eggs_container)[1][i].first = -1;
            }
            else
                (*eggs_container)[0][i].first = -1;
        }
        for (int i = 0; i < (*crystals_container)[0].size(); i++){
            if ((*crystals_container)[0][i].first < (*crystals_container)[1][i].first){
                (*crystals_container)[1][i].first = -1;
            }
            else
                (*crystals_container)[0][i].first = -1;
        }
    }
}

typedef struct s_path
{
    int         eggs;
    int         crystals;
    int         nbr_cells_have_eggs;
    int         nbr_cells_have_crystals;
    int         avrg;
    int         avrg_eggs;
    int         avrg_crystals;
    vector<int> path;
}   t_path;

bool    neighbor_have_eggs(irc a, crc b, int index)
{
    if (a[index].neigh_0 != -1 && b[a[index].neigh_0].resources > 0)
        return (true);
    if (a[index].neigh_1 != -1 && b[a[index].neigh_1].resources > 0)
        return (true);
    if (a[index].neigh_2 != -1 && b[a[index].neigh_2].resources > 0)
        return (true);
    if (a[index].neigh_3 != -1 && b[a[index].neigh_3].resources > 0)
        return (true);
    if (a[index].neigh_4 != -1 && b[a[index].neigh_4].resources > 0)
        return (true);
    if (a[index].neigh_5 != -1 && b[a[index].neigh_5].resources > 0)
        return (true);
    return (false);
}
// vector::wich_base <vector :: pathes <pair :: single_path <int,vector<int> > > > crystals_container
vector<pair<int, t_path> >   manipulate_data(irc a, crc b, vector<int> my_base_index, vector<int> opp_base_index, int number_of_bases, int number_of_cells, vector<vector<pair<int,vector<int> > > > eggs_container, vector<vector<pair<int,vector<int> > > > crystals_container, vector<vector<pair<int,vector<int> > > > opp_eggs_container, vector<vector<pair<int,vector<int> > > > opp_crystals_container)
{
    vector<pair<int, t_path> > final_paths;
    for (int k = 0; k < number_of_bases; k++){
        for (int i = 0; i < crystals_container[k].size(); i++)
        {
            for (int j = 0; j < crystals_container[k][i].second.size(); j++){
                    if (a[crystals_container[k][i].second[j]].neigh_0 != -1 && b[a[crystals_container[k][i].second[j]].neigh_0].resources > 0 && !is_in(crystals_container[k][i].second, a[crystals_container[k][i].second[j]].neigh_0)){
                        crystals_container[k][i].second.push_back(a[crystals_container[k][i].second[j]].neigh_0);
                        crystals_container[k][i].first++;
                        j = 0;
                    }
                    if (a[crystals_container[k][i].second[j]].neigh_1 != -1 && b[a[crystals_container[k][i].second[j]].neigh_1].resources > 0 && !is_in(crystals_container[k][i].second, a[crystals_container[k][i].second[j]].neigh_1)){
                        crystals_container[k][i].second.push_back(a[crystals_container[k][i].second[j]].neigh_1);
                        crystals_container[k][i].first++;
                        j = 0;
                    }
                    if (a[crystals_container[k][i].second[j]].neigh_2 != -1 && b[a[crystals_container[k][i].second[j]].neigh_2].resources > 0 && !is_in(crystals_container[k][i].second, a[crystals_container[k][i].second[j]].neigh_2)){
                        crystals_container[k][i].second.push_back(a[crystals_container[k][i].second[j]].neigh_2);
                        crystals_container[k][i].first++;
                        j = 0;
                    }
                    if (a[crystals_container[k][i].second[j]].neigh_3 != -1 && b[a[crystals_container[k][i].second[j]].neigh_3].resources > 0 && !is_in(crystals_container[k][i].second, a[crystals_container[k][i].second[j]].neigh_3)){
                        crystals_container[k][i].second.push_back(a[crystals_container[k][i].second[j]].neigh_3);
                        crystals_container[k][i].first++;
                        j = 0;
                    }
                    if (a[crystals_container[k][i].second[j]].neigh_4 != -1 && b[a[crystals_container[k][i].second[j]].neigh_4].resources > 0 && !is_in(crystals_container[k][i].second, a[crystals_container[k][i].second[j]].neigh_4)){
                        crystals_container[k][i].second.push_back(a[crystals_container[k][i].second[j]].neigh_4);
                        crystals_container[k][i].first++;
                        j = 0;
                    }
                    if (a[crystals_container[k][i].second[j]].neigh_5 != -1 && b[a[crystals_container[k][i].second[j]].neigh_5].resources > 0 && !is_in(crystals_container[k][i].second, a[crystals_container[k][i].second[j]].neigh_5)){
                        crystals_container[k][i].second.push_back(a[crystals_container[k][i].second[j]].neigh_5);
                        crystals_container[k][i].first++;
                        j = 0;
                    }
				}
                int eggs = 0;
                int crystals = 0;
                int nbr_cells_have_eggs = 0;
                int nbr_cells_have_crystals = 0;
                for (int m = 0; m < crystals_container[k][i].first; m++){
                    if (b[crystals_container[k][i].second[m]].resources > 0 && a[crystals_container[k][i].second[m]].type == 1){
                        eggs += b[crystals_container[k][i].second[m]].resources;
                        nbr_cells_have_eggs++;
                    } 
                    else if (b[crystals_container[k][i].second[m]].resources > 0 && a[crystals_container[k][i].second[m]].type == 2){
                        crystals += b[crystals_container[k][i].second[m]].resources;
                        nbr_cells_have_crystals++;
                    }
                }
                int avrg = (eggs+crystals)/crystals_container[k][i].second.size();
                int avrg_eggs = eggs/crystals_container[k][i].second.size();
                int avrg_crystals = crystals/crystals_container[k][i].second.size();
                final_paths.push_back(pair(k, (t_path){eggs, crystals, nbr_cells_have_eggs, nbr_cells_have_crystals, avrg, avrg_eggs, avrg_crystals, crystals_container[k][i].second}));
        }
    }
    return (final_paths);
}

int chose_best_path(int key, vector<pair<int, t_path>> final_paths)
{
    vector<int>best_path;

    pair<int, int> max = pair(0, final_paths[0].second.avrg);
    pair<int, int> max_eggs = pair(0, final_paths[0].second.avrg_eggs);
    pair<int, int> max_crystals = pair(0, final_paths[0].second.avrg_crystals);
    for (int i = 0; i < final_paths.size(); i++){
        if (final_paths[i].first == key){
            if (max.second < final_paths[i].second.avrg)
                max = pair(i, final_paths[i].second.avrg);
            if (max_eggs.second < final_paths[i].second.avrg_eggs)
                max_eggs = pair(i, final_paths[i].second.avrg_eggs);
            if (max_crystals.second < final_paths[i].second.avrg_crystals)
                max_crystals = pair(i, final_paths[i].second.avrg_crystals);
        }
    }
    return (max_crystals.first);
}

int main()
{
    irc         a;
    crc         b;
    int         number_of_bases;
    vector<int>         my_base_index;
    vector<int>         opp_base_index;
    int         number_of_cells; // amount of hexagonal cells in this map
    int         loop = 0;
    a = read_initial_data(&number_of_cells, &my_base_index, &opp_base_index, &number_of_bases);
    vector <t_bfs*> my_base;
    vector <t_bfs*> opp_base;
    for (int i = 0; i < number_of_bases; i++){
        t_bfs* nul = NULL;
        bfs(number_of_cells, a, my_base_index[i], &nul);
        my_base.push_back(nul);
        nul = NULL;
        bfs(number_of_cells, a, opp_base_index[i], &nul);
        opp_base.push_back(nul);
    }
        int init_eggs = 0;
        int init_crystals = 0;
    while (1337) {
        int eggs = 0;
        int crystals = 0;
        bool couted = false;
        bool hold = false;
        if (!loop)
            b = read_current_data(number_of_cells, a, &init_eggs, &init_crystals);
        else
            b = read_current_data(number_of_cells, a, &eggs, &crystals);
        vector<vector<pair<int,vector<int> > > > eggs_container;
        vector<vector<pair<int,vector<int> > > > crystals_container;
        vector<vector<pair<int,vector<int> > > > opp_eggs_container;
        vector<vector<pair<int,vector<int> > > > opp_crystals_container;
        get_data(a, b, my_base, opp_base, number_of_bases, number_of_cells, &eggs_container, &crystals_container, &opp_eggs_container, &opp_crystals_container);
        if (number_of_bases == 2){
            for (int i = 0; i < eggs_container.size(); i++){
                if (eggs_container[0][i].first == -1)
                    eggs_container[0].erase(eggs_container[0].begin() + i);
                if (eggs_container[1][i].first == -1)
                    eggs_container[1].erase(eggs_container[0].begin() + i);
            }
            for (int i = 0; i < crystals_container.size(); i++){
                if (crystals_container[0][i].first == -1)
                    crystals_container[0].erase(crystals_container[0].begin() + i);
                if (crystals_container[1][i].first == -1)
                    crystals_container[1].erase(crystals_container[0].begin() + i);
            }
        }
        vector<pair<int, t_path>> final_paths = manipulate_data(a, b, my_base_index, opp_base_index, number_of_bases, number_of_cells, eggs_container, crystals_container, opp_eggs_container, opp_crystals_container);
        // cout << "MESSAGE "<< final_paths.size() << " am here;";
        //         print_path(final_paths[0].second.path, 1);
try{
        for (int k = 0; k < number_of_bases; k++){
            // if (loop < 4)
            // {
            //     for (int i = 0; i < eggs_container.size(); i++){
            //         if (eggs_container[k][i].first <= 3 && eggs_container[k][i].first != -1){
            //             couted = true;
            //             print_path(eggs_container[k][i].second, 1);
            //         }
            //     }
            // }
            // if (loop >= 4 || !couted){
                int lenght = 0;
                if (number_of_bases == 1)
                {
                    for (int i =0; i < crystals_container[k].size(); i++){
                        if (crystals_container[k][i].first == opp_crystals_container[k][i].first){
                            couted = true;
                            print_path(crystals_container[k][i].second, 1);
                        }
                    }
                    if (couted){
                        for (int i =0; i < eggs_container[k].size(); i++){
                            if (eggs_container[k][i].first <= 3){
                                print_path(eggs_container[k][i].second, 1);
                            }
                        }
                    }
                }
                else
                {
                    if (eggs * 100.0/ init_eggs < 60)
                    {
                        for (int i = 0; i< eggs_container[k].size(); i++){
                            for (int j = 0; j< eggs_container[k][i].size(); j++){

                            }
                        }
                    }
                }
                if (!couted){
                    while (1337){
                        int index = chose_best_path(k, final_paths);
                        if (final_paths.size() == 0)
                        {
                            couted = false;
                            break ;
                        }
                        cout << "MESSAGE " << crystals << " " << init_crystals << " " << (crystals * 100.0) /init_crystals << " ;";
                        if ((crystals * 100.0) /init_crystals > 10)
                            print_path(final_paths[index].second.path, 1);
                        else
                            print_path_line(a, b, final_paths[index].second.path, 1);


                        couted = true;
                        lenght += final_paths[index].second.path.size();
                        final_paths.erase(final_paths.begin() + index);
                        if (!final_paths.size() || ((lenght * 100.0) / number_of_cells >= 10))
                            break;
                        // if ((lenght * 100.0) / number_of_cells >= 10)
                        //     break;
                    }
                }
            // }
            if (!couted){
                for (int i = 0; i < number_of_cells; i++){
                    if (b[i].resources > 0 && a[i].type == 2){
                        cout << "LINE " << i << " " << my_base_index[k] << " ;";
                    }
                }
            }
        }
}catch(exception&e){
                cerr << "MESSAGE : " << loop << " ";
                            cerr<< e.what() ;

            cerr << " ;";
}
        loop++;
        cout << endl;
    }
}

        // for (int k = 0; k < number_of_bases; k++){
        //     for (int i = 0; i < eggs_container[k].size(); i++){
        //         if (eggs_container[k][i].first <= opp_eggs_container[k][i].first && \
        //             eggs_container[k][i].first <= opp_eggs_container[!k][i].first){
        //             couted = true;
        //             print_path(eggs_container[k][i].second, 1);
        //         }
        //     }
        //     if (!couted || loop >= 4)
        //     {
        //         for (int i = 0; i < crystals_container[k].size(); i++){
        //             int tmp = abs(crystals_container[k][i].first - opp_crystals_container[k][i].first);
        //             if ((crystals_container[k][i].first == opp_crystals_container[k][i].first) &&\
        //             crystals_container[k][i].first <= opp_crystals_container[!k][i].first && \
        //             crystals_container[k][i].first <= crystals_container[!k][i].first){
        //                 hold = true;
        //                 print_path(crystals_container[k][i].second, 3);
        //                 crystals_container[k].erase(crystals_container[k].begin() + i--);
        //             }
        //         }
        //         if (!hold) {
        //             for (int i = 0; loop < 10&&  i < eggs_container[k].size(); i++){
        //                 if (eggs_container[k][i].first <= opp_eggs_container[k][i].first && \
        //                 eggs_container[k][i].first <= opp_eggs_container[!k][i].first && \
        //                 eggs_container[k][i].first <= eggs_container[!k][i].first){
        //                     hold = true;
        //                     print_path(eggs_container[k][i].second, 1);
        //                     eggs_container[k].erase(eggs_container[k].begin() + i--);
        //                 }
        //             }
        //             for (int i = 0; i < crystals_container[k].size(); i++){
        //                 if (crystals_container[k][i].first <= opp_crystals_container[k][i].first && \
        //                 crystals_container[k][i].first <= opp_crystals_container[!k][i].first &&\
        //                 crystals_container[k][i].first <= crystals_container[!k][i].first){
        //                     hold = true;
        //                     print_path(crystals_container[k][i].second, 1);
        //                     crystals_container[k].erase(crystals_container[k].begin() + i--);
        //                 }
        //             }
        //         }
        //         if (!hold) {
        //             for (int i = 0; i < crystals_container[k].size(); i++){
        //                     print_path(crystals_container[k][i].second, 1);
        //                     crystals_container[k].erase(crystals_container[k].begin() + i--);
        //             }
        //         }
        //     }
        //     couted = false;
        //     hold = false;
        // }

//    try{
//         if (loop < 4)
//         {
//             for (int i = 0; i < eggs_container.size(); i++){
//                 if (eggs_container[i].first <= 3){
//                     couted = true;
//                     cout << "LINE " << my_base_index[k] << " " << eggs_container[i].second.back() << " 3;";
//                     // print_path(eggs_container[i].second, 1);
//                 }
//             }

//         }
//         if (loop >= 4 || !couted)
//         {
//             for (int i = 0; i < crystals_container.size(); i++){
//                 if (crystals_container[i].first == opp_crystals_container[i].first){
//                     cout << "LINE " << my_base_index[k] << " " << crystals_container[i].second.back() << " 1;";
//                     // print_path(crystals_container[i].second, 1);
//                     hold = true;
//                 }
//             }
//             for (int i = 0; i < eggs_container.size(); i++){
//                 if (eggs_container[i].first <= opp_eggs_container[i].first){
//                     cout << "LINE " << my_base_index[k]<< " "  << eggs_container[i].second.back() << " 1;";
//                     // print_path(eggs_container[i].second, 1);
//                 }
//             }
//             if (!hold){
//                 for (int i = 0; i < crystals_container.size(); i++){
//                     if (crystals_container[i].first < opp_crystals_container[i].first){
//                     cout << "LINE " << my_base_index[k]<< " "  << crystals_container[i].second.back() << " 1;";
//                         // print_path(crystals_container[i].second, 1);
//                         hold = true;
//                     }
//                 }
//             }
//             if (!hold){
//                 for (int i = 0; i < crystals_container.size(); i++){
//                     if (crystals_container[i].first > opp_crystals_container[i].first)
//                     cout << "LINE " << my_base_index[k] << " " << crystals_container[i].second.back() << " 1;";
//                         // print_path(crystals_container[i].second, 1);
//                 }
//             }
//         }
//         eggs_container.clear();
//         crystals_container.clear();
//         opp_eggs_container.clear();
//         opp_crystals_container.clear();
//                         }catch(exception&e){
//             cerr << "MESSAGE : " << loop << " ";
//                             cerr<< e.what() ;

//             cerr << " ;";

//             }


// bool decide = false;

