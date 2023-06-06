#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

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


typedef struct InitialRessources
{
	int type; // 0 for empty, 1
    int initial_resources; // t
    int neigh_0; // the index o
    int neigh_1;
    int neigh_2;
    int neigh_3;
    int neigh_4;
    int neigh_5;
}	t_ir;

typedef struct CurrentRessources
{
	int resources; 
	int my_ants;
	int opp_ants;
}	t_cr;

typedef struct ressources
{
	int				index;
	vector<t_ir>	ir;
	t_cr			cr;
}	t_ressources;

irc read_initial_data(int *number_of_cells, int *my_base_index, int *opp_base_index, int *number_of_bases)
{
    irc a;
    cin >> *number_of_cells; cin.ignore();
    // cout << " initial_data_start ";
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
        // cout << "  | " << type << " " << initial_resources << " " << neigh_0 << " " << neigh_1<< " "  << neigh_2 << " " << neigh_3 << " " << neigh_4 << " " << neigh_5 << "| ";
        a.push_back(InitialRessourcesClass(type, initial_resources, neigh_0, neigh_1, neigh_2, neigh_3, neigh_4, neigh_5));
    }
    // cout << " initial_data_end ";
    cin >> *number_of_bases; cin.ignore();
    for (int i = 0; i < *number_of_bases; i++) {
        cin >> *my_base_index; cin.ignore();
        cout << "MESSAGE : " << *my_base_index << " ;";
    }
    for (int i = 0; i < *number_of_bases; i++) {
        cin >> *opp_base_index; cin.ignore();
    }
    return (a);
}

crc read_current_data(int number_of_cells, irc a, int *eggs, int *crystals)
{
    crc b;    

    // cout << " current_data_start ";
    for (int i = 0; i < number_of_cells; i++) {
        int resources; // the current amount of eggs/crystals on this cell
        int my_ants; // the amount of your ants on this cell
        int opp_ants; // the amount of opponent ants on this cell
        cin >> resources >> my_ants >> opp_ants; cin.ignore();
        if (a[i].type == 1)
            *eggs += resources;
        else if (a[i].type == 2)
            *crystals += resources;
        // cout << " | " << resources << " " << my_ants << " " << opp_ants << " | ";
        b.push_back(CurrentRessourcesClass(resources, my_ants, opp_ants));
    }
    // cout << " current_data_end ";
    return (b);
}

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

    if (a[index].neigh_0)
        neighbors.push_back(a[index].neigh_0);
    if (a[index].neigh_1)
        neighbors.push_back(a[index].neigh_1);
    if (a[index].neigh_2)
        neighbors.push_back(a[index].neigh_2);
    if (a[index].neigh_3)
        neighbors.push_back(a[index].neigh_3);
    if (a[index].neigh_4)
        neighbors.push_back(a[index].neigh_4);
    if (a[index].neigh_5)
        neighbors.push_back(a[index].neigh_5);
    return (neighbors);
}

typedef struct s_bfs
{
	int             index;
    bool            locked;
    struct s_bfs    *neigh_0;
    struct s_bfs    *neigh_1;
    struct s_bfs    *neigh_2;
    struct s_bfs    *neigh_3;
    struct s_bfs    *neigh_4;
    struct s_bfs    *neigh_5;
}	t_bfs;

t_bfs   *new_bfs(int index, bool locked)
{
    t_bfs       *bfs;

    bfs = (t_bfs *)malloc(sizeof(t_bfs));
    memset(bfs, 0, sizeof(t_bfs));
    bfs->index = index;
    bfs->locked = locked;
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
    if (ret)    
        return (ret);
    return (NULL);
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

void    bfs(int number_of_cells, irc a, int start_index, t_bfs **bfs)
{
    queue<int> queue;
    vector<int> visited;
    bool        locked = false;
    t_bfs       *bfs_head;

    queue.push(start_index);
    visited.push_back(start_index);
    *bfs = new_bfs(queue.front(), locked);
    bfs_head = *bfs;
    while (!queue.empty()){
        vector<int> tmp = get_neighbors(a, queue.front());
        *bfs = go_to_addr(bfs_head, queue.front());
        for (int i = 0; i < tmp.size(); i++){
            if (!is_in(visited, tmp[i]) && tmp[i] != -1) {
                queue.push(tmp[i]);
                visited.push_back(tmp[i]);
                if (!i && tmp[i] != -1)
                    (*bfs)->neigh_0 = new_bfs(tmp[i], locked);
                else if (i == 1 && tmp[i] != -1)
                    (*bfs)->neigh_1 = new_bfs(tmp[i], locked);
                else if (i == 2 && tmp[i] != -1)
                    (*bfs)->neigh_2 = new_bfs(tmp[i], locked);
                else if (i == 3 && tmp[i] != -1)
                    (*bfs)->neigh_3 = new_bfs(tmp[i], locked);
                else if (i == 4 && tmp[i] != -1)
                    (*bfs)->neigh_4 = new_bfs(tmp[i], locked);
                else if (i == 5 && tmp[i] != -1)
                    (*bfs)->neigh_5 = new_bfs(tmp[i], locked);
            }

        }
        tmp.clear();
        queue.pop();
    }
}

// map<int, vector<int> >   matrix_init(int number_of_cells, irc a)
// {
// 	map<int, vector<int> >	_map;

// 	for (int i = 0; i < number_of_cells; i++){
//         vector <int> tmp;
// 		if (a[i].neigh_0 != -1) {
//             tmp.push_back(a[i].neigh_0);
// 		}
//         if (a[i].neigh_1 != -1)
//         {
//             tmp.push_back(a[i].neigh_1);
//         }
//         if (a[i].neigh_2 != -1)
//         {
//             tmp.push_back(a[i].neigh_2);
//         }
//         if (a[i].neigh_3 != -1)
//         {
//             tmp.push_back(a[i].neigh_3);
//         }
//         if (a[i].neigh_4 != -1)
//         {
//             tmp.push_back(a[i].neigh_4);
//         }
//         if (a[i].neigh_5 != -1)
//         {
//             tmp.push_back(a[i].neigh_5);
//         }
//         _map.insert(pair(i, tmp));
// 	}
//     return (_map);
// }

// <int,
//  vector<t_ir>> read_initial_data(int *number_of_cells)
// {
// 	map	<int, vector<t_ir> > map_;
//     cin >> *number_of_cells; cin.ignore();
//     for (int i = 0; i < *number_of_cells; i++) {
// 		t_ir ir;
//         int type; // 0 for empty, 1 for eggs, 2 for crystal
//         int initial_resources; // the initial amount of eggs/crystals on this cell
//         int neigh_0; // the index of the neighbouring cell for each direction
//         int neigh_1;
//         int neigh_2;
//         int neigh_3;
//         int neigh_4;
//         int neigh_5;
//         cin >> type >> initial_resources >> neigh_0 >> neigh_1 >> neigh_2 >> neigh_3 >> neigh_4 >> neigh_5; cin.ignore();
// 		map_.insert(pair(i, (t_ir){type, initial_resources, neigh_0, neigh_1, neigh_2, neigh_3, neigh_4, neigh_5}));
//     }
//     return (map_);
// }

// <int, vector<t_cr>> read_current_data(int number_of_cells, irc a, int *eggs, int *crystals)
// {
// 	map	<int, vector<t_cr> > map_;
//     for (int i = 0; i < number_of_cells; i++) {
//         int resources; // the current amount of eggs/crystals on this cell
//         int my_ants; // the amount of your ants on this cell
//         int opp_ants; // the amount of opponent ants on this cell
//         cin >> resources >> my_ants >> opp_ants; cin.ignore();
//         if (a[i].type == 1)
//             *eggs += resources;
//         else if (a[i].type == 2)
//             *crystals += resources;
// 		map_.insert(pair(i, (t_ir){resources, my_ants, opp_ants}));
//     }
//     return (map_);
// }