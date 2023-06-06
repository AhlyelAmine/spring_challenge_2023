
# include <iostream>
# include <string>
# include <vector>
#include <utility>
# include <algorithm>
# include <math>
using namespace std;

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

t_tree  *new_node(int index)
{
    t_tree  *new_;

    new_ = (t_tree *)malloc(sizeof(t_tree));
    new_->index = index;
    new_->n_0 = NULL;
    new_->n_1 = NULL;
    new_->n_2 = NULL;
    new_->n_3 = NULL; 
    new_->n_4 = NULL;
    new_->n_5 = NULL;
    return (new_);
}

bool    in_tree(vector<int> *map_inedxes, int index)
{
    for (int i = 0; i < map_inedxes->size(); i++){
        if ((*map_inedxes)[i] == index)
            return (1);
    }
    return (0);
}

t_tree  *build_tree_up(irc a, int index, vector<int> *map_inedxes)
{
    t_tree  *new_;

    if (index != -1 && !in_tree(map_inedxes, index))
    {
        map_inedxes->push_back(index);
        new_ = new_node(index);
        new_->n_1 = build_tree_up(a, a[index].neigh_1, map_inedxes);
        new_->n_2 = build_tree_up(a, a[index].neigh_2, map_inedxes);
        return (new_);
    }
    return (NULL);
}

t_tree  *build_tree_down(irc a, int index, vector<int> *map_inedxes)
{
    t_tree  *new_;

    if (index != -1 && !in_tree(map_inedxes, index))
    {
        map_inedxes->push_back(index);
        new_ = new_node(index);
        new_->n_4 = build_tree_down(a, a[index].neigh_4, map_inedxes);
        new_->n_5 = build_tree_down(a, a[index].neigh_5, map_inedxes);
        return (new_);
    }
    return (NULL);
}

t_tree  *build_tree_left(irc a, int index, vector<int> *map_inedxes)
{
    t_tree  *new_;

    if (index != -1 && !in_tree(map_inedxes, index))
    {
        map_inedxes->push_back(index);
        new_ = new_node(index);
        new_->n_0 = build_tree_left(a, a[index].neigh_0, map_inedxes);
        new_->n_1 = build_tree_left(a, a[index].neigh_1, map_inedxes);
        new_->n_5 = build_tree_left(a, a[index].neigh_5, map_inedxes);
        return (new_);
    }
    return (NULL);
}

t_tree  *build_tree_right(irc a, int index, vector<int> *map_inedxes)
{
    t_tree  *new_;

    if (index != -1 && !in_tree(map_inedxes, index))
    {
        map_inedxes->push_back(index);
        new_ = new_node(index);
        new_->n_2 = build_tree_right(a, a[index].neigh_2, map_inedxes);
        new_->n_3 = build_tree_right(a, a[index].neigh_3, map_inedxes);
        new_->n_4 = build_tree_right(a, a[index].neigh_4, map_inedxes);
        return (new_);
    }
    return (NULL);
}

t_tree  *build_tree(irc a, int index, vector<int> *map_inedxes)
{
    t_tree  *new_;

    if (index != -1 && !in_tree(map_inedxes, index))
    {
        map_inedxes->push_back(index);
        new_ = new_node(index);
        new_->n_0 = build_tree_left(a, a[index].neigh_0, map_inedxes);
        new_->n_1 = build_tree_up(a, a[index].neigh_1, map_inedxes);
        new_->n_2 = build_tree_up(a, a[index].neigh_2, map_inedxes);
        new_->n_3 = build_tree_right(a, a[index].neigh_3, map_inedxes);
        new_->n_4 = build_tree_down(a, a[index].neigh_4, map_inedxes);
        new_->n_5 = build_tree_down(a, a[index].neigh_5, map_inedxes);
        return (new_);
    }
    return (NULL);
}



int each_neighbor(irc a, int number_of_cells, int *neigh_indx, int target, vector<int> map_inedxes)
{
    for (int i = 0; i < number_of_cells; i++){
        if (in_tree(&map_inedxes, i))
        {
            if (a[i].neigh_0 == target){
                *neigh_indx = 0;
                return (i);
            }
            if (a[i].neigh_1 == target){
                *neigh_indx = 1;
                return (i);
            }
            if (a[i].neigh_2 == target){
                *neigh_indx = 2;
                return (i);
            }
            if (a[i].neigh_3 == target){
                *neigh_indx = 3;
                return (i);
            }
            if (a[i].neigh_4 == target){
                *neigh_indx = 4;
                return (i);
            }
            if (a[i].neigh_5 == target){
                *neigh_indx = 5;
                return (i);
            }
        }
    }
    return (-1);
}

void    add_in_map(t_tree *map,  t_tree *missing, int neigh_indx)
{
    if (neigh_indx == 0)
        map->n_0 = missing;
    else if (neigh_indx == 1)
        map->n_1 = missing;
    else if (neigh_indx == 2)
        map->n_2 = missing;
    else if (neigh_indx == 3)
        map->n_3 = missing;
    else if (neigh_indx == 4)
        map->n_4 = missing;
    else if (neigh_indx == 5)
        map->n_5 = missing;
}

bool    add_in_map_at(t_tree *map, t_tree *missing, int missing_neighbor, int neigh_indx)
{
    if (!map)
        return (0);
    else if (map->index == missing_neighbor)
        return (add_in_map(map, missing, neigh_indx), 1);
    else if (map->n_0 && add_in_map_at(map->n_0, missing, missing_neighbor, neigh_indx))
        return (1);
    else if (map->n_1 && add_in_map_at(map->n_1, missing, missing_neighbor, neigh_indx))
        return (1);
    else if (map->n_2 && add_in_map_at(map->n_2, missing, missing_neighbor, neigh_indx))
        return (1);
    else if (map->n_3 && add_in_map_at(map->n_3, missing, missing_neighbor, neigh_indx))
        return (1);
    else if (map->n_4 && add_in_map_at(map->n_4, missing, missing_neighbor, neigh_indx))
        return (1);
    else if (map->n_5 && add_in_map_at(map->n_5, missing, missing_neighbor, neigh_indx))
        return (1);
    return (0);
}

void    add_in_map2(t_tree *map,  int missing, int neigh_indx)
{
    if (neigh_indx == 0)
        map->n_0 = new_node(missing);
    else if (neigh_indx == 1)
        map->n_1 = new_node(missing);
    else if (neigh_indx == 2)
        map->n_2 = new_node(missing);
    else if (neigh_indx == 3)
        map->n_3 = new_node(missing);
    else if (neigh_indx == 4)
        map->n_4 = new_node(missing);
    else if (neigh_indx == 5)
        map->n_5 = new_node(missing);
}

bool    add_in_map_at2(t_tree *map, int missing, int missing_neighbor, int neigh_indx)
{
    if (!map)
        return (0);
    else if (map->index == missing_neighbor)
        return (add_in_map2(map, missing, neigh_indx), 1);
    else if (map->n_0 && add_in_map_at2(map->n_0, missing, missing_neighbor, neigh_indx))
        return (1);
    else if (map->n_1 && add_in_map_at2(map->n_1, missing, missing_neighbor, neigh_indx))
        return (1);
    else if (map->n_2 && add_in_map_at2(map->n_2, missing, missing_neighbor, neigh_indx))
        return (1);
    else if (map->n_3 && add_in_map_at2(map->n_3, missing, missing_neighbor, neigh_indx))
        return (1);
    else if (map->n_4 && add_in_map_at2(map->n_4, missing, missing_neighbor, neigh_indx))
        return (1);
    else if (map->n_5 && add_in_map_at2(map->n_5, missing, missing_neighbor, neigh_indx))
        return (1);
    return (0);
}
t_tree  *each_build(irc a, int index, int neigh, vector<int> *map_inedxes)
{
    t_tree *tmp;

    tmp = NULL;
    if (neigh == 0)
        tmp = build_tree_left(a, index, map_inedxes);
    else if (neigh == 3)
        tmp = build_tree_right(a, index, map_inedxes);
    else if (neigh == 1 || neigh == 2)
        tmp = build_tree_up(a, index, map_inedxes);
    else if (neigh == 4 || neigh == 5)
        tmp = build_tree_down(a, index, map_inedxes);
    return (tmp);
}

bool    find_path(t_tree *map, vector<int> *path, int target)
{
    path->push_back(map->index);
    if (map->index == target)
        return (1);
    if (map->n_0)
    {
        if (find_path(map->n_0, path, target))
            return (1);
        else
            path->pop_back();
    }
    if (map->n_1)
    {
        if (find_path(map->n_1, path, target))
            return (1);
        else
            path->pop_back();
    }
    if (map->n_2)
    {
        if (find_path(map->n_2, path, target))
            return (1);
        else
            path->pop_back();
    }
    if (map->n_3)
    {
        if (find_path(map->n_3, path, target))
            return (1);
        else
            path->pop_back();
    }
    if (map->n_4)
    {
        if (find_path(map->n_4, path, target))
            return (1);
        else
            path->pop_back();
    }
    if (map->n_5)
    {
        if (find_path(map->n_5, path, target))
            return (1);
        else
            path->pop_back();
    }
    return (0);
}

irc read_initial_data(int *number_of_cells)
{
    irc a;
    cin >> *number_of_cells; cin.ignore();
    for (int i = 0; i < *number_of_cells; i++) {
        // int type; // 0 for empty, 1 for eggs, 2 for crystal
        // int initial_resources; // the initial amount of eggs/crystals on this cell
        int neigh_0; // the index of the neighbouring cell for each direction
        int neigh_1;
        int neigh_2;
        int neigh_3;
        int neigh_4;
        int neigh_5;
        cin >> /*type >> initial_resources >> */neigh_0 >> neigh_1 >> neigh_2 >> neigh_3 >> neigh_4 >> neigh_5; cin.ignore();
        a.push_back(InitialRessourcesClass(0, 0, neigh_0, neigh_1, neigh_2, neigh_3, neigh_4, neigh_5));
    }
    return (a);
}

t_tree      *build_tree_at(irc a, vector<int> map_inedxes, int number_of_cells, int index)
{
    int         neigh_indx;
    int         missing_neighbor;
    t_tree      *map;
    
    map = build_tree(a, index, &map_inedxes);
    if (number_of_cells > map_inedxes.size())
    {
        t_tree *tmp;
        for (int missing = 0; missing < number_of_cells; missing++){
            if (!in_tree(&map_inedxes, missing)){
                missing_neighbor = each_neighbor(a, number_of_cells, &neigh_indx, missing, map_inedxes);
                if (missing_neighbor != -1)
                {
                    tmp = each_build(a, missing, neigh_indx, &map_inedxes);
                    if (tmp)
                        add_in_map_at(map, tmp, missing_neighbor, neigh_indx);
                    else
                        add_in_map_at2(map, missing, missing_neighbor, neigh_indx);
                    missing = 0;
                }
            }
        }
    }
    return (map);
}
bool is_shortest(vector<int> path_1, vector<int> path_2)
{
    if (abs(path_2.size() - path_1.size()) <= 3)
        return (1);
    else if (path_2.size() <= path_1.size())
        return (1);
    else if (path_2.size() >= path_1.size())
        return (0);
    return (0);
}

int main()
{
    irc         a;
    int         number_of_cells;
    crc         b;
    vector<int> path_1;
    vector<int> path_2;
    vector<int> map_inedxes;
    t_tree      *my_base;
    t_tree      *opp_base;

    a = read_initial_data(&number_of_cells);
    my_base = build_tree_at(a, map_inedxes, number_of_cells, 23);
    opp_base = build_tree_at(a, map_inedxes, number_of_cells, 24);
    find_path(my_base, &path_1, 3);
    for (int i = 0; i < number_of_cells; i++){
        if (b[i].resources > 0 && a[i].type == 1)
        {
            find_path(my_base, &path_1, i);
            find_path(opp_base, &path_1, i);
        }
        
    }
}


void    print_tree(t_tree *map)
{
    if (!map)
        return ;
    cout << map->index << endl;
    print_tree((t_tree *)map->n_0);
    print_tree((t_tree *)map->n_1);
    print_tree((t_tree *)map->n_2);
    print_tree((t_tree *)map->n_3);
    print_tree((t_tree *)map->n_4);
    print_tree((t_tree *)map->n_5);
}
















































// int check_neghibors(irc a, crc b, int index, int base_index)
// {
//     if (a[index].neigh_0 == base_index)
//         return (a[index].neigh_0);
//     else if (a[index].neigh_1 == base_index)
//         return (a[index].neigh_1);
//     else if (a[index].neigh_2 == base_index)
//         return (a[index].neigh_2);
//     else if (a[index].neigh_3 == base_index)
//         return (a[index].neigh_3);
//     else if (a[index].neigh_4 == base_index)
//         return (a[index].neigh_4);
//     else if (a[index].neigh_5 == base_index)
//         return (a[index].neigh_5);
//     return (-1);
// }

// int    get_shortest_path(irc a, crc b, int index, int base_index, vector<int> *beacons)
// {
//     int tmp;

//     beacons->push_back(index);
//     tmp = check_neghibors(a, b, index, base_index);
//     if (tmp != -1)
//     {
//         beacons->push_back(tmp);
//         return (1);
//     }
//     else if (get_shortest_path(a, b, a[index].neigh_0, base_index, beacons))
//         return (1);
//     else if (get_shortest_path(a, b, a[index].neigh_1, base_index, beacons))
//         return (1);
//     else if (get_shortest_path(a, b, a[index].neigh_2, base_index, beacons))
//         return (1);
//     else if (get_shortest_path(a, b, a[index].neigh_3, base_index, beacons))
//         return (1);
//     else if (get_shortest_path(a, b, a[index].neigh_4, base_index, beacons))
//         return (1);
//     else if (get_shortest_path(a, b, a[index].neigh_5, base_index, beacons))
//         return (1);
//     else
//     {
//         beacons->pop_back();
//         return (0);
//     }
// }

