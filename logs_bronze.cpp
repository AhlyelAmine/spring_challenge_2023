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


t_tree      *build_tree_at(irc a, int number_of_cells, int index)
{
    int         neigh_indx;
    int         missing_neighbor;
    t_tree      *map;
    vector<int> map_inedxes;
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

bool is_shortest(vector<int> path_1, vector<int> path_2)
{
    // int tmp = path_2.size() - path_1.size();
    // if (abs(tmp) <= 2)
    //     return (1);
    if (path_1.size() <= path_2.size())
        return (1);
    else /*if (path_2.size() >= path_1.size())*/
        return (0);
    return (0);
}

bool crystals_amount_95(int initial_crystals, int crystals)
{
    if (crystals * 100 / initial_crystals > 95)
        return (1);
    return (0);
}

bool crystals_amount_80(int initial_crystals, int crystals)
{
    if (crystals * 100 / initial_crystals > 80)
        return (1);
    return (0);
}

bool crystals_amount_60(int initial_crystals, int crystals)
{
    if (crystals * 100 / initial_crystals > 60)
        return (1);
    return (0);
}

vector <int> get_min(vector<pair<int, int>> eggs)
{
    vector <int> ret;
    pair<int, int> min = eggs[0];
    for (int i = 0; i < eggs.size(); i++){
        if (eggs[i].first < min.first)
            min = eggs[i];
    }
    for (int i = 0; i < eggs.size(); i++){
        if (eggs[i].first == min.first)
            ret.push_back(eggs[i].second);
    }
    // return (min.second);
    return (ret);
}
int check_neghibors(irc a, crc b, int index, int base_index)
{
    if (a[a[index].neigh_0].type == 1)
        return (a[index].neigh_0);
    else if (a[a[index].neigh_1].type == 1)
        return (a[index].neigh_1);
    else if (a[a[index].neigh_2].type == 1)
        return (a[index].neigh_2);
    else if (a[a[index].neigh_3].type == 1)
        return (a[index].neigh_3);
    else if (a[a[index].neigh_4].type == 1)
        return (a[index].neigh_4);
    else if (a[a[index].neigh_5].type == 1)
        return (a[index].neigh_5);
    return (-1);
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

int main()
{
    irc         a;
    crc         b;
    int         number_of_bases;
    int         my_base_index;
    int         opp_base_index;
    int         number_of_cells; // amount of hexagonal cells in this map
    int         loop = 0;
    a = read_initial_data(&number_of_cells, &my_base_index, &opp_base_index, &number_of_bases);
  while (1) {
        int eggs = 0;
        int crystals = 0;
        b = read_current_data(number_of_cells, a, &eggs, &crystals);
        if (loop <= 4){
            if (!decide)
                neighbor_have_eggs(a, b, my_base_index);
            if (!decide)
                for (int i = 0; i < number_of_cells; i++) {
                if (b[i].resources > 0 && a[i].type == 1) {
                    cout << "LINE " << my_base_index << " " << i << " 1;";
                }
            }
        }
        else if (loop > 8)
        {
             for (int i = 0; i < number_of_cells; i++) {
                if (b[i].resources > 0 && a[i].type == 2) {
                    if (loop < 10)
                        cout << "LINE " << my_base_index << " " << i << " 2;";
                    else
                        cout << "LINE " << my_base_index << " " << i << " 4;";
                }
            }
        }
        else if (loop > 4) {
            for (int i = 0; i < number_of_cells; i++) {
                if (b[i].resources > 0) {
                    if (loop < 10)
                        cout << "LINE " << my_base_index << " " << i << " 2;";
                    else
                        cout << "LINE " << my_base_index << " " << i << " 4;";
                }
            }
        }
        loop++;
        cout << "MESSAGE : " << loop << " ;";
        cout << endl;
        decide = false;
  }
}
// int main()
// {
//     irc         a;
//     crc         b;
//     int         number_of_bases;
//     int         my_base_index;
//     int         opp_base_index;
//     int         number_of_cells; // amount of hexagonal cells in this map
//     vector<int> path_1;
//     vector<int> path_2;
//     t_tree      *my_base;
//     t_tree      *opp_base;
//     int         initial_eggs = 0;
//     int         initial_crystals = 0;
//     int         loop = 0;
//     int         block = 0;
//     a = read_initial_data(&number_of_cells, &my_base_index, &opp_base_index, &number_of_bases);
//     my_base = build_tree_at(a, number_of_cells, my_base_index);
//     opp_base = build_tree_at(a, number_of_cells, opp_base_index);
//     // game loop
//     while (1) {
//         vector<pair<int, int>> egg_index;
//         int eggs = 0;
//         int crystals = 0;
//         int couted = 0;
//         int eggs_saved = 0;
//         // if (!loop++)
//         //     b = read_current_data(number_of_cells, a, &initial_eggs, &initial_crystals);
//         // else
//         b = read_current_data(number_of_cells, a, &eggs, &crystals);
//         if (!block && check_neghibors(a, b, my_base_index, my_base_index))
//         {
//             block = 1;
//             if (b[a[my_base_index].neigh_0].resources > 0 && a[a[my_base_index].neigh_0].type == 1)
//             {
//                 block = 0;
//                 couted = 1;
//                 cout << "LINE " << my_base_index << " " << a[my_base_index].neigh_0 << " 1;";
//             }
//             if (b[a[my_base_index].neigh_1].resources > 0 && a[a[my_base_index].neigh_1].type == 1)
//             {
//                 block = 0;
//                 couted = 1;
//                 cout << "LINE " << my_base_index << " " << a[my_base_index].neigh_1 << " 1;";
//             }
//             if (b[a[my_base_index].neigh_2].resources > 0 && a[a[my_base_index].neigh_2].type == 1)
//             {
//                 block = 0;
//                 couted = 1;
//                 cout << "LINE " << my_base_index << " " << a[my_base_index].neigh_2 << " 1;";
//             }
//             if (b[a[my_base_index].neigh_3].resources > 0 && a[a[my_base_index].neigh_3].type == 1)
//             {
//                 block = 0;
//                 couted = 1;
//                 cout << "LINE " << my_base_index << " " << a[my_base_index].neigh_3 << " 1;";
//             }
//             if (b[a[my_base_index].neigh_4].resources > 0 && a[a[my_base_index].neigh_4].type == 1)
//             {
//                 block = 0;
//                 couted = 1;
//                 cout << "LINE " << my_base_index << " " << a[my_base_index].neigh_4 << " 1;";
//             }
//             if (b[a[my_base_index].neigh_5].resources > 0 && a[a[my_base_index].neigh_5].type == 1)
//             {
//                 block = 0;
//                 couted = 1;
//                 cout << "LINE " << my_base_index << " " << a[my_base_index].neigh_5 << " 1;";
//             }
//         }
//         if (block || ! couted)
//         {
//             if (loop <= 4){
//                 for (int i = 0; i < number_of_cells; i++) {
//                     if (b[i].resources > 0 && a[i].type == 1) {
//                         cout << "LINE " << my_base_index << " " << i << " 1;";
//                     }
//                 }
//             }
//             else if (loop > 10)
//             {
//                 for (int i = 0; i < number_of_cells; i++) {
//                     if (b[i].resources > 0 && a[i].type == 2) {
//                         cout << "LINE " << my_base_index << " " << i << " 2;";
//                     }
//                 }
//             }
//             else if (loop > 4) {
//                 for (int i = 0; i < number_of_cells; i++) {
//                     if (b[i].resources > 0) {
//                         cout << "LINE " << my_base_index << " " << i << " 2;";
//                     }
//                 }
//             }
//         }

//         loop++;
//         // if (block || ! couted)
//         // {
//         //     for (int i = 0; i < number_of_cells; i++){
//         //         if (b[i].resources > 0)
//         //         {
//         //                 find_path(my_base, &path_1, i);
//         //                 if (path_1.size() < 10)
//         //             cout << "MESSAGE 55 ; LINE " << my_base_index << " " << i << " 1;";
//         //     path_1.clear();

//         //         }
//         //     }
            
//         // }
//         // for (int i = 0; i < number_of_cells; i++){
//         //     if (loop == 1 || initial_crystals == crystals){
//         //         if (b[i].resources > 0 && a[i].type == 1){
//         //             find_path(my_base, &path_1, i);
//         //             find_path(opp_base, &path_2, i);
//         //             if (is_shortest(path_1, path_2))
//         //             {
//         //                 couted = 1;
//         //                 eggs_saved = 1;
//         //                 egg_index.push_back(pair(path_1.size(), i));
//         //                 // cout << "LINE " << i << " " << my_base_index << " 1;";
//         //             }
//         //             path_1.clear();
//         //             path_2.clear();
//         //         }
//         //     }
//         //     else if (crystals_amount_80(initial_crystals, crystals))
//         //     {
//         //          if (b[i].resources > 0 && a[i].type == 1){
//         //             find_path(my_base, &path_1, i);
//         //             find_path(opp_base, &path_2, i);
//         //             if (is_shortest(path_1, path_2))
//         //             {
//         //                 couted = 1;
//         //                 eggs_saved = 1;
//         //                 egg_index.push_back(pair(path_1.size(), i));
//         //                 // cout << "LINE " << i << " " << my_base_index << " 1;";
//         //             }
//         //             path_1.clear();
//         //             path_2.clear();
//         //         }
//         //          if (b[i].resources > 0 && a[i].type == 2){
//         //             find_path(my_base, &path_1, i);
//         //             find_path(opp_base, &path_2, i);
//         //             if (is_shortest(path_1, path_2))
//         //             {
//         //                 couted = 1;
//         //                 cout << "MESSAGE 1 ;LINE " << i << " " << my_base_index << " 1;";
//         //             }
//         //             path_1.clear();
//         //             path_2.clear();
//         //         }
//         //     }
//         //     else if (crystals_amount_60(initial_crystals, crystals)){
//         //         if (b[i].resources > 0 /*&& a[i].type == 2*/){
//         //             // find_path(my_base, &path_1, i);
//         //             // find_path(opp_base, &path_2, i);
//         //             // if (is_shortest(path_1, path_2))
//         //             // {
//         //                 couted = 1;
//         //                 cout << "MESSAGE 2 ;LINE " << i << " " << my_base_index << " 1;";
//         //             // }
//         //             // path_1.clear();
//         //             // path_2.clear();
//         //         }
//         //     }
//         //     else  {
//         //          if (b[i].resources > 0 && a[i].type == 2)
//         //         {
//         //             couted = 1;
//         //             cout << "MESSAGE 3 ;LINE " << i << " " << my_base_index << " 1;";
//         //         }
//         //     }
//         // }
//         // if (eggs_saved){
//         //     vector <int> eggg;
//         //     eggg = get_min(egg_index);
//         //     for (int k = 0; k < eggg.size(); k++)
//         //         cout << "MESSAGE 4 ;LINE " << eggg[k] << " " << my_base_index << " 1;";
//         //     eggg.clear();
//         //     egg_index.clear();
//         // }
//         // if (!couted){
//         //      for (int i = 0; i < number_of_cells; i++){
//         //         if (b[i].resources > 0 && a[i].type == 2)
//         //             cout << "MESSAGE 5 ;LINE " << i << " " << my_base_index << " 1;";
//         //     }
//         // }
//         path_1.clear();
//         path_2.clear();
//         cout << endl;
//         b.clear();
//     }
    //------------------------------------------------------------------------------------------------------------------------
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    // cout << "WAIT" << endl;
    // WAIT | LINE <sourceIdx> <targetIdx> <strength> | BEACON <cellIdx> <strength> | MESSAGE <text>
// }