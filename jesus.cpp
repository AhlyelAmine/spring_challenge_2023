#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

bool egg = false;

typedef struct t_stock {
     int resources;
     int my_ants;
     int opp_ants;
} s_stock;

typedef struct s_data {
    int type;
    int initial_recour;
    int neigh_0;
    int neigh_1;
    int neigh_2;
    int neigh_3;
    int neigh_4;
    int neigh_5;
} t_data;

typedef struct s_turns {
    int times;
    int index;
} t_turns;

class cells {
    public :
        t_stock stock;
        t_data  data;
        cells() {;}
        void    set_stock(int resources, int my_ants, int opp_ants) {
            this->stock.resources = resources;
            this->stock.opp_ants = my_ants;
            this->stock.opp_ants = opp_ants;
        }
};

cells *creat_cell_data(int _type, int _initial_recour, int _neigh_0,int _neigh_1,int _neigh_2,int _neigh_3,int _neigh_4,int _neigh_5) {
            cells*obj = new cells;
            obj->data.type = _type;
            obj->data.initial_recour = _initial_recour;
            obj->data.neigh_0 = _neigh_0;
            obj->data.neigh_1 = _neigh_1;
            obj->data.neigh_2 = _neigh_2;
            obj->data.neigh_3 = _neigh_3;
            obj->data.neigh_4 = _neigh_4;
            obj->data.neigh_5 = _neigh_5;
            return (obj);
}

void    super_print(vector<int> lines, vector<int> bases, map<int, cells *> _map) {
    for (vector<int>::iterator _it = lines.begin() ; _it != lines.end(); _it++) {
        for (vector<int>::iterator it = bases.begin(); it != bases.end(); it++)
        cout << "LINE " << *_it << " " << *it << " 4;";
    }
}

void    print_line(int base, int index) {
    if (index != -1) {
        cout << "LINE " << index << " " << base << " 1;";
    }
        // cout << "MESSAGE " << index << " " << base << " 1;";
}

void    print_line_two(int base, int index) {
    if (index != -1) {
        cout << "LINE " << index << " " << base << " 2;";
    }
        // cout << "MESSAGE " << index << " " << base << " 1;";
}

void    print_all_lines(vector<int> lines, vector<int> bases, map<int, cells *> _map) {
    for (vector<int>::iterator _it = lines.begin() ; _it != lines.end(); _it++) {
        for (vector<int>::iterator it = bases.begin(); it != bases.end(); it++){
        if (_map[*it]->data.type == 1)
            print_line(*it, *_it);
        else
            print_line_two(*it, *_it);

        }
    }
}

void check_base_n(int base, map<int, cells *> _map) {
    if (_map[base]->data.neigh_0 != -1 && _map[_map[base]->data.neigh_0]->data.type == 1 && _map[_map[base]->data.neigh_0]->stock.resources > 0)
    {
        cout << "LINE " << _map[base]->data.neigh_0 << " " << base << " 2;";
        egg = true;
    }
    if (_map[base]->data.neigh_1 != -1 && _map[_map[base]->data.neigh_1]->data.type == 1&& _map[_map[base]->data.neigh_1]->stock.resources > 0)
    {
        cout << "LINE " << _map[base]->data.neigh_1 << " " << base << " 2;";
        egg = true;
    }
    if (_map[base]->data.neigh_2 != -1 && _map[_map[base]->data.neigh_2]->data.type == 1&& _map[_map[base]->data.neigh_2]->stock.resources > 0)
    {
        cout << "LINE " << _map[base]->data.neigh_2 << " " << base << " 2;";
        egg = true;
    }
    if (_map[base]->data.neigh_3 != -1 && _map[_map[base]->data.neigh_3]->data.type == 1&& _map[_map[base]->data.neigh_3]->stock.resources > 0)
    {
        cout << "LINE " << _map[base]->data.neigh_3 << " " << base << " 2;";
        egg = true;
    }
    if (_map[base]->data.neigh_4 != -1 && _map[_map[base]->data.neigh_4]->data.type == 1&& _map[_map[base]->data.neigh_4]->stock.resources > 0)
    {
        cout << "LINE " << _map[base]->data.neigh_4 << " " << base << " 2;";
        egg = true;
    }
    if (_map[base]->data.neigh_5 != -1 && _map[_map[base]->data.neigh_5]->data.type == 1&& _map[_map[base]->data.neigh_5]->stock.resources > 0)
    {
        cout << "LINE " << _map[base]->data.neigh_5 << " " << base << " 2;";
        egg = true;
    }
}

int main()
{
    std::map<int, cells *> _map;
    std::map<int, bool> hash;
    int number_of_cells; // amount of hexagonal cells in this map
    cin >> number_of_cells; cin.ignore();
    vector<int> bases;
    for (int i = 0; i < number_of_cells; i++) {
        int type; // 0 for empty, 1 for eggs, 2 for crystal
        int initial_resources; // the initial amount of eggs/crystals on this cell
        int neigh_0; // the index of the neighbouring cell for each direction
        int neigh_1;
        int neigh_2;
        int neigh_3;
        int neigh_4;
        int neigh_5;
        cin >> type >> initial_resources >> neigh_0 >> neigh_1 >> neigh_2 >> neigh_3 >> neigh_4 >> neigh_5; cin.ignore();
        _map.insert(pair<int, cells *>( i, creat_cell_data(type , initial_resources , neigh_0 , neigh_1 , neigh_2 , neigh_3 , neigh_4 , neigh_5)));
    }
    int number_of_bases;
    cin >> number_of_bases; cin.ignore();
        int my_base_index;
    for (int i = 0; i < number_of_bases; i++) {
        cin >> my_base_index; cin.ignore();
        bases.push_back(my_base_index);
    }
        int opp_base_index;
    for (int i = 0; i < number_of_bases; i++) {
        cin >> opp_base_index; cin.ignore();
    }

    vector<int> lines;
    int next_hop = -1;
    int best_egg;
    int a = 0;
    // game loop
    while (1) {
        for (int i = 0; i < number_of_cells; i++) {
            int resources; // the current amount of eggs/crystals on this cell
            int my_ants; // the amount of your ants on this cell
            int opp_ants; // the amount of opponent ants on this cell
            cin >> resources >> my_ants >> opp_ants; cin.ignore();
            _map[i]->set_stock(resources, my_ants, opp_ants);
        }
        if (a <= 4){
            if (!egg)
            {
                check_base_n(my_base_index, _map);
            }
            if (!egg)
            {
                for (map<int, cells *>::iterator it = _map.begin(); it != _map.end(); it++) {
                    if (it->second->data.type == 1 && it->second->stock.resources > 0) {
                        lines.push_back(it->first);
                    }
                }
            }
        }
        else if (a > 8)
        {
              for (map<int, cells *>::iterator it = _map.begin(); it != _map.end(); it++) {
                if (it->second->stock.resources > 0 && it->second->data.type == 2) {
                    lines.push_back(it->first);
                }
            }
        }
        else if (a > 4) {
            for (map<int, cells *>::iterator it = _map.begin(); it != _map.end(); it++) {
                if (it->second->stock.resources > 0) {
                    lines.push_back(it->first);
                }
            }
        }
        if (a < 10)
            print_all_lines(lines, bases, _map);
        else
            super_print(lines, bases, _map);
        a++;
        lines.clear();
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cout << endl;
        // WAIT | LINE <sourceIdx> <targetIdx> <strength> | BEACON <cellIdx> <strength> | MESSAGE <text>
        // cout << "WAIT" << endl;
        egg = false;
    }
}
