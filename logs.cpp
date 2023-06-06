#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/


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

// bool allready_checked(vector<int> checked, int index)
// {
//     for (int i = 0; i < checked.size(); i++){
//         if (checked[i] == index)
//             return (1);
//     }
//     return (0);
// }

int check_neghibors(irc a, crc b, int index, int base_index)
{
    if (a[index].neigh_0 == base_index)
        return (a[index].neigh_0);
    else if (a[index].neigh_1 == base_index)
        return (a[index].neigh_1);
    else if (a[index].neigh_2 == base_index)
        return (a[index].neigh_2);
    else if (a[index].neigh_3 == base_index)
        return (a[index].neigh_3);
    else if (a[index].neigh_4 == base_index)
        return (a[index].neigh_4);
    else if (a[index].neigh_5 == base_index)
        return (a[index].neigh_5);
    return (-1);
}

int check_neighbors_of_each_neighbor(irc a, crc b, int index, int base_index, int *tmp, vector<int> *beacons)
{
    *tmp = check_neghibors(a, b, a[index].neigh_0, base_index);
    if (*tmp != -1)
    {
        beacons->push_back(a[index].neigh_0);
        return (1);
    }
    *tmp = check_neghibors(a, b, a[index].neigh_1, base_index);
    if (*tmp != -1)
    {
        beacons->push_back(a[index].neigh_1);
        return (1);
    }
    *tmp = check_neghibors(a, b, a[index].neigh_2, base_index);
    if (*tmp != -1)
    {
        beacons->push_back(a[index].neigh_2);
        return (1);
    }
    *tmp = check_neghibors(a, b, a[index].neigh_3, base_index);
    if (*tmp != -1)
    {
        beacons->push_back(a[index].neigh_3);
        return (1);
    }
    *tmp = check_neghibors(a, b, a[index].neigh_4, base_index);
    if (*tmp != -1)
    {
        beacons->push_back(a[index].neigh_4);
        return (1);
    }
    *tmp = check_neghibors(a, b, a[index].neigh_5, base_index);
    if (*tmp != -1)
    {
        beacons->push_back(a[index].neigh_5);
        return (1);
    }
    return (0);
}

int    get_shortest_path(irc a, crc b, int index, int base_index, vector<int> *beacons)
{
    int tmp;
    beacons->push_back(index);
    tmp = check_neghibors(a, b, index, base_index);
    if (tmp != -1)
    {
        beacons->push_back(tmp);
        return (1);
    }
    else if (check_neighbors_of_each_neighbor(a, b, index, base_index, &tmp, beacons))
    {
        beacons->push_back(tmp);
        return (1);
    }
    else
    {
        beacons->pop_back();
        return (0);
    }
}

bool is_all_0(crc b, vector<vector<int>> a)
{
    for (int i = 0; i < a.size(); i++){
        if (b[a[i][0]].resources > 0)
            return (0);
    }
    return (1);
}
bool in_spawn(crc b, vector<vector<int>> spawn, int index)
{
    for (int i = 0; i < spawn.size(); i++){
        if (spawn[i].back() == index)
            return (1);
    }
    return (0);
}

bool get_line_left(irc a, crc b, int index, int my_base_index, vector<int> *beacons)
{
    beacons->push_back(index);
    if (index == my_base_index)
        return (1);
    if (index == -1)
        return (0);
    if (!get_line_left(a, b, a[index].neigh_3, my_base_index, beacons))
    {
        beacons->pop_back();
        return (0);
    }
    else
        return (1);
}

bool get_line_right(irc a, crc b, int index, int my_base_index, vector<int> *beacons)
{
    beacons->push_back(index);
    if (index == my_base_index)
        return (1);
    if (index == -1)
        return (0);
    if (!get_line_right(a, b, a[index].neigh_0, my_base_index, beacons))
    {
        beacons->pop_back();
        return (0);
    }
    else
        return (1);
}

bool get_line(irc a, crc b, int index, int my_base_index, vector<int> *beacons)
{
    if (get_line_left(a, b, index, my_base_index, beacons))
        return (1);
    beacons->clear();
    if (get_line_right(a, b, index, my_base_index, beacons))
        return (1);
    return (0);
}

int main()
{
    irc a;
    crc b;

    int number_of_cells; // amount of hexagonal cells in this map
    cin >> number_of_cells; cin.ignore();
    cout << ">>|" << number_of_cells << "|<< ";
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
        cout << " |" << neigh_0 << " " << neigh_1<< " "  << neigh_2 << " " << neigh_3 << " " << neigh_4 << " " << neigh_5 << "| ";
        a.push_back(InitialRessourcesClass(type, initial_resources, neigh_0, neigh_1, neigh_2, neigh_3, neigh_4, neigh_5));
    }
    int number_of_bases;
    int my_base_index;
    cin >> number_of_bases; cin.ignore();
    for (int i = 0; i < number_of_bases; i++) {
        cin >> my_base_index; cin.ignore();
    }
        int opp_base_index;
    for (int i = 0; i < number_of_bases; i++) {
        cin >> opp_base_index; cin.ignore();
    }
    // game loop

		// vector<pair<int,int>> opp_spawn;
		// vector<pair<pair<int,int>,int>> my_ants;
		// vector<pair<pair<int,int>,int>> opp_ants;
    vector<vector<int>> my_spawn;
    int loop = 0;
    int line = 0;
    while (1) {
            for (int i = 0; i < number_of_cells; i++) {
                int resources; // the current amount of eggs/crystals on this cell
                int my_ants; // the amount of your ants on this cell
                int opp_ants; // the amount of opponent ants on this cell
                cin >> resources >> my_ants >> opp_ants; cin.ignore();
                b.push_back(CurrentRessourcesClass(resources, my_ants, opp_ants));
            }

        int print = 0;
		crc b_copy = b;
		irc a_copy = a;
        vector<int> beacons_nei;
        vector<int> beacons_line;
        vector<int> logs;
        int in = 0;
        for (int i = 0; i < number_of_cells; i++){
            if (b[i].resources > 0 && a[i].type == 1){
                if (a[i].neigh_0 ==  my_base_index || a[i].neigh_1 ==  my_base_index || a[i].neigh_2 ==  my_base_index || a[i].neigh_3 ==  my_base_index || a[i].neigh_4 ==  my_base_index || a[i].neigh_5 ==  my_base_index) {
                    in = 1;
                    cout << "BEACON " << my_base_index << " 1;";
                    cout << "BEACON "  << i << " 2;";
                }
            }
        }
        if (!in){
            for (int i = 0; i < number_of_cells; i++){
                if (b[i].resources > 0 && a[i].type == 1){
                    if (get_shortest_path(a, b, i, my_base_index, &beacons_nei)){
                        for (int j = 0; j < beacons_nei.size(); j++){
                            in = 1;
                            if (beacons_nei[j] > 0 && beacons_nei[j] < number_of_cells)
                                cout << "BEACON " << beacons_nei[j] << " 1;";
                        }
                        if (in){
                            for (int z = i + 1; z < number_of_cells; z++){
                                if (b[z].resources > 0 && a[z].type == 1 && get_line(a, b, z, beacons_nei[0], &beacons_line)) {
                                    cout << "LINE " << beacons_line.back() << " " << i << " 1;";
                                }
                                beacons_line.clear();
                            }
                        }
                        beacons_nei.clear();
                    }
                    else if (get_line(a, b, i, my_base_index, &beacons_line)){
                        in = 1;
                        cout << "LINE " << beacons_line[0] << " " << my_base_index << " 1;";
                    }
                    beacons_nei.clear();
                    beacons_line.clear();
                }
            }
        }
        if (!in){
            for (int i = 0; i < number_of_cells; i++){
                if (b[i].resources > 0 && a[i].type == 2){
                    if (get_shortest_path(a, b, i, my_base_index, &beacons_nei)){
                        for (int j = 0; j < beacons_nei.size(); j++){
                            in = 1;
                            if (beacons_nei[j] > 0 && beacons_nei[j] < number_of_cells)
                                cout << "BEACON " << beacons_nei[j] << " 1;";
                        }
                        if (in){
                            for (int z = i + 1; z < number_of_cells; z++){
                                if (b[z].resources > 0 && get_shortest_path(a, b, z, beacons_nei[0], &beacons_line)){
                                      for (int u = 0; u < beacons_line.size(); u++){
                                            in = 1;
                                            if (beacons_line[u] >= 0 && beacons_line[u] <= number_of_cells)
                                                cout << "BEACON " << beacons_line[u] << " 1;";
                                        }
                                }
                                beacons_line.clear();
                                if (b[z].resources > 0 && get_line(a, b, z, beacons_nei[0], &beacons_line)) {
                                    cout << "LINE " << beacons_line.back() << " " << i << " 1;";
                                }
                                beacons_line.clear();
                            }
                        }
                        beacons_nei.clear();
                    }
                    else if (get_line(a, b, i, my_base_index, &beacons_line)){
                        in = 1;
                        cout << "LINE " << beacons_line[0] << " " << my_base_index << " 1;";
                    }
                    beacons_nei.clear();
                    beacons_line.clear();
                }
            }
        // }
        if (!in)
        {
            for (int i = 0; i < number_of_cells; i++){
                if (b[i].resources > 0)
                    cout << "LINE " << my_base_index << " " << i << " 1;";
            }
        }
        }
        // loop++;
        // if (loop == 1)
        // {
        //     for (int i = 0; i < number_of_cells; i++){
        //         if (b[i].resources > 0){
        //             if (get_shortest_path(a, b, i, my_base_index, &beacons, &checked)){
        //                 in = 1;
        //                 print = 1;
        //                 for (int z = 0; z < beacons.size(); z++){
        //                     cout << "BEACON " << beacons[z] << " 1;";
        //                 }
        //                 my_spawn.push_back(beacons);
        //                 checked.clear();
        //                 beacons.clear();
        //             }
        //         }
        //     }
        //     beacons.clear();
        // }
        // if (!print)
        // {
        //     if (line)
        //     {
        //         for (int i = 0; i < number_of_cells; i++){
        //             if (b[i].resources > 0)
        //             {
        //                 print = 1;
        //                 cout << "LINE " << i << " " << my_base_index << " 1;";
        //             }
        //         }
        //     }
        //     if ((!in && !line) || !print)
        //     {
        //         for (int i = 0; i < number_of_cells; i++){
        //             if (b[i].resources > 0){
        //                 if (get_shortest_path(a, b, i, my_base_index, &beacons, &checked)){
        //                     in = 1;
        //                     for (int z = 0; z < beacons.size(); z++){
        //                         print = 1;
        //                         cout << "BEACON " << beacons[z] << " 1;";
        //                     }
        //                     int tmp = beacons[0];
        //                     checked.clear();
        //                     beacons.clear();
        //                     for (int z = i + 1; z < number_of_cells; z++){
        //                         if (b[z].resources > 0 && get_shortest_path(a, b, z, tmp, &beacons, &checked)){
        //                             for (int z = 0; z < beacons.size(); z++){
        //                                 cout << "BEACON " << beacons[z] << " 1;";
        //                             }
        //                             my_spawn.push_back(beacons);
        //                             checked.clear();
        //                             beacons.clear();
        //                         }
        //                     }  
        //                     my_spawn.push_back(beacons);
        //                     checked.clear();
        //                     beacons.clear();
        //                 }
        //             }
        //         }
        //     }
        //     beacons.clear();
        //     if ((!in && !line) || !print)
        //     {
        //         line = 1;
        //         my_spawn.clear();
        //         for (int i = 0; i < number_of_cells; i++){
        //             if (b[i].resources > 0 && !in_spawn(b, my_spawn, i)){
        //                 cout << "LINE " <<  i << " " << my_base_index << " 1;";
        //                 for (int z = i + 1; z < number_of_cells; z++){
        //                     if (b[z].resources > 0 && get_shortest_path(a, b, i, z, &beacons, &checked)){
        //                         for (int z = 0; z < beacons.size(); z++){
        //                             cout << "BEACON " << beacons[z] << " 1;";
        //                         }
        //                         my_spawn.push_back(beacons);
        //                         checked.clear();
        //                         beacons.clear();
        //                     }
        //                 }
        //                 // if (in)
        //                 //     break;
        //             }
        //         }
        //     }
        //     beacons.clear();
        // }





            // for (int i = 0; i < number_of_cells; i++){
            //     for (int h = 0; h < my_spawn.size(); h++){
            //         if (my_spawn[h][0] != -1 && get_shortest_path(a, b, i, my_spawn[h][0], &beacons, &checked)){
            //             for (int z = 0; z < my_spawn[h].size(); z++){
            //                 cout << "LINE " <<  my_spawn[h][z] << " " << my_base_index << " 1;";
            //             }
            //             for (int z = 0; z < beacons.size(); z++){
            //                 cout << "LINE " << beacons[z]<< " " << my_base_index << " 1;";
            //             }
            //             my_spawn.push_back(beacons);
            //             checked.clear();
            //             beacons.clear();
            //         }
            //         else
            //             my_spawn[h][0] = -1;
            //     }
            // }
        cout << endl;
            b.clear();
        }
    //------------------------------------------------------------------------------------------------------------------------
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    // cout << "WAIT" << endl;
    // WAIT | LINE <sourceIdx> <targetIdx> <strength> | BEACON <cellIdx> <strength> | MESSAGE <text>
}


            // vector<pair<int, int>> ressources;
            // vector<int> logs;
            // if (!neighbors_got_eggs(a, &b, my_base_index))
            // {
            //     while (check_neigh(a, b, my_base_index, &tmp_beacons, &logs)) {
            //         pair<int, int> tmp;
            //         tmp.first = tmp_beacons.back();
            //         tmp.second = tmp_beacons.size();
            //         ressources.push_back(tmp);
            //         b[tmp.first].resources = 0;
            //         tmp_beacons.clear();
            //         logs.clear();
            //     }
            //     for (int i = 0; i < ressources.size(); i++){
            //         if (b[ressources[i].first].resources > 0)
            //             cout << "LINE " << my_base_index << " " << ressources[i].first << " 1;";
            //     }
            //     for (int i = 0; i < number_of_cells; i++){
            //         if (b[i].resources > 0) {
            //             cout << "LINE " << my_base_index << " " << i << " 1;";
            //         }
            //     }
            // }




        // cout << "   ||.    ";
		// for (int i = 0; i < number_of_cells; i++){
		// 	if (b[i].resources > 0){
		// 		while (check_neigh(&a_copy, b_copy, -1, i, &beacons, -1, my_base_index, checker_spawn))
		// 		{
        //             // cout << "found it";
        //             cout << "beggin ";
        //             for (int p = 0; p < beacons.size(); p++){
        //                 cout << beacons[p] << " | ";
        //             }
        //             cout << "end ";
		// 			pair <int,int> tmp;
		// 			tmp.first = beacons[0];
		// 			tmp.second = beacons.size();
		// 			add_it_in(&my_spawn, tmp);
		// 		}
        //         while (1);
		// 		beacons.clear();
        //         a_copy = a;
		// 		if (check_neigh(&a_copy, b, -1, i, &beacons, -1, opp_base_index, checker_spawn))
		// 		{
		// 			pair <int,int> tmp;
		// 			tmp.first = beacons[0];
		// 			tmp.second = beacons.size();
		// 			add_it_in(&opp_spawn, tmp);
		// 		}
        //         a_copy = a;
		// 		beacons.clear();
		// 		while (check_neigh(&a_copy, b_copy, -1, i, &beacons, -1, opp_base_index, checker_my_ants))
		// 		{
		// 			pair<pair<int,int>,int> tmp;
		// 			tmp.first.first = beacons[0];
		// 			tmp.first.second = beacons.back();
		// 			tmp.second = beacons.size();
		// 			b_copy[tmp.first.second].my_ants = 0;
		// 			add_it_in_dpair(&my_ants, tmp);
		// 			beacons.clear();
		// 		}
		// 		beacons.clear();
        //         a_copy = a;
		// 		b_copy = b;
		// 		while (check_neigh(&a_copy, b_copy, -1, i, &beacons, -1, opp_base_index, checker_opp_ants))
		// 		{
		// 			pair<pair<int,int>,int> tmp;
		// 			tmp.first.first = beacons[0];
		// 			tmp.first.second = beacons.back();
		// 			tmp.second = beacons.size();
		// 			b_copy[tmp.first.second].opp_ants = 0;
		// 			add_it_in_dpair(&opp_ants, tmp);
		// 			beacons.clear();
		// 		}
        //         a_copy = a;
		// 		beacons.clear();
		// 		b_copy = b;
		// 	}

		// }

// void    approache_spam(irc a, crc b, int number_of_cells, int my_base_index)
// {
//     // static int call;
//     // cout << "BEACON " << call << " 1;" << endl;
//     // call++;
//     // for (int i = 0; i < number_of_cells; i++)
//     // {
//         vector<int> tmp_beacons;
//         vector<int> old_beacons;
//         while (check_neigh_cry(a, b, my_base_index, &tmp_beacons, -1) && is_not_on_me(tmp_beacons, old_beacons))
//         {
//             // if (tmp_beacons.size() == 0)
//             //     break ;
//             old_beacons.push_back(tmp_beacons.back());
//             for (int i = 0; i < tmp_beacons.size(); i++)
//                 cout << "BEACON "<< tmp_beacons[i] << " 1;";
//             my_base_index = tmp_beacons[tmp_beacons.size() - 1];
//             tmp_beacons.clear();
//         }
//         // if (check_neigh_cry(a, b, my_base_index, &tmp_beacons, -1))
//         // {
//         //     for (int i = 0; i < tmp_beacons.size(); i++)
//         //         cout << "BEACON "<< tmp_beacons[i] << " 1;";
//         //     int tmp = tmp_beacons[tmp_beacons.size() - 1];
//         //         tmp_beacons.clear();
//         //     if (check_neigh_cry(a, b, tmp, &tmp_beacons, -1))
//         //     {
//         //         // tmp_beacons.clear();
//         //         for (int i = 0; i < tmp_beacons.size(); i++)
//         //                 cout << "BEACON "<< tmp_beacons[i] << " 1;";
//         //     }
//         // }
//         // tmp_beacons.clear();
//     // }
// }




// bool cell_allready_called(vector<int> logs, int i)
// {
//     if (logs.size() > 1)
//     {
//         for (int j = 0; j < logs.size() - 1; j++){
//             if (i == logs[j])
//                 return (1);
//         }
//     }
//     return (0);
// }

// int check_neigh(irc a, crc b, int i, vector<int> *beacons, vector<int> *logs)
// {
//     int tmp;
//     if (b[i].resources == 0)
//         (*logs).push_back(i); // save cell index in logs
//     if (a[i].neigh_0 != -1)
//     {
//         (*beacons).push_back(a[i].neigh_0); // add beacon neighbor to beacons list
//         if (b[a[i].neigh_0].resources > 0) // if this neighbor contain ressources keep it in the list
//             return (1);
//         if (!cell_allready_called(*logs, i)) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
//         {
//             tmp = check_neigh(a, b, a[i].neigh_0, beacons, logs); // check neighbor neighbors if got ressources
//             if (!tmp)
//                 (*beacons).pop_back(); // if no ressources remove the becon from the list
//             else
//                 return (1); // else if their is ressources keep the neighbor in the list
//         }
//         else
//             (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
//     }
//     if (a[i].neigh_1 != -1)
//     {
//         (*beacons).push_back(a[i].neigh_1);
//         if (b[a[i].neigh_1].resources > 0)
//             return (1);
//         if (!cell_allready_called(*logs, i)) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
//         {
//             tmp = check_neigh(a, b, a[i].neigh_1, beacons, logs);
//             if (!tmp)
//                 (*beacons).pop_back(); 
//             else
//                 return (1);
//         }
//         else
//             (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
//     }
//     if (a[i].neigh_2 != -1)
//     {
//         (*beacons).push_back(a[i].neigh_2);
//         if (b[a[i].neigh_2].resources > 0)
//             return (1);
//         if (!cell_allready_called(*logs, i)) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
//         {
//             tmp = check_neigh(a, b, a[i].neigh_2, beacons, logs);
//             if (!tmp)
//                 (*beacons).pop_back(); 
//             else
//                 return (1);
//         }
//         else
//             (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
//     }
//     if (a[i].neigh_3 != -1)
//     {
//         (*beacons).push_back(a[i].neigh_3);
//         if (b[a[i].neigh_3].resources > 0)
//             return (1);
//         if (!cell_allready_called(*logs, i)) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
//         {
//             tmp = check_neigh(a, b, a[i].neigh_3, beacons, logs);
//             if (!tmp)
//                 (*beacons).pop_back(); 
//             else
//                 return (1);
//          }
//         else
//             (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
//     }
//     if (a[i].neigh_4 != -1)
//     {
//         (*beacons).push_back(a[i].neigh_4);
//         if (b[a[i].neigh_4].resources > 0)
//             return (1);
//         if (!cell_allready_called(*logs, i)) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
//         {
//             tmp = check_neigh(a, b, a[i].neigh_4, beacons, logs);
//             if (!tmp)
//                 (*beacons).pop_back(); 
//             else
//                 return (1);
//         }
//         else
//             (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
//     }
//     if (a[i].neigh_5 != -1)
//     {
//         (*beacons).push_back(a[i].neigh_5);
//         if (b[a[i].neigh_5].resources > 0)
//             return (1);
//         if (!cell_allready_called(*logs, i)) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
//         {
//             tmp = check_neigh(a, b, a[i].neigh_5, beacons, logs);
//             if (!tmp)
//                 (*beacons).pop_back(); 
//             else
//                 return (1);
//         }
//         else
//             (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
//     }
//     return (0);
// }

// bool neighbors_got_eggs(irc a, crc *b, int my_base_index)
// {
//     int ret = 0;
//     if (a[a[my_base_index].neigh_0].type == 1 && (*b)[a[my_base_index].neigh_0].resources > 0)
//     {
//         cout << "LINE " << my_base_index << " " << a[my_base_index].neigh_0 << " 1;";
//         (*b)[a[my_base_index].neigh_0].resources = 0;
//         ret = 1;
//     }
//     if (a[a[my_base_index].neigh_1].type == 1 && (*b)[a[my_base_index].neigh_1].resources > 0)
//     {
//         cout << "LINE " << my_base_index << " " << a[my_base_index].neigh_1 << " 1;";
//         (*b)[a[my_base_index].neigh_1].resources = 0;
//         ret = 1;
//     }
//     if (a[a[my_base_index].neigh_2].type == 1 && (*b)[a[my_base_index].neigh_2].resources > 0)
//     {
//         cout << "LINE " << my_base_index << " " << a[my_base_index].neigh_2 << " 1;";
//         (*b)[a[my_base_index].neigh_2].resources = 0;
//         ret = 1;
//     }
//     if (a[a[my_base_index].neigh_3].type == 1 && (*b)[a[my_base_index].neigh_3].resources > 0)
//     {
//         cout << "LINE " << my_base_index << " " << a[my_base_index].neigh_3 << " 1;";
//         (*b)[a[my_base_index].neigh_3].resources = 0;
//         ret = 1;
//     }
//     if (a[a[my_base_index].neigh_4].type == 1 && (*b)[a[my_base_index].neigh_4].resources > 0)
//     {
//         cout << "LINE " << my_base_index << " " << a[my_base_index].neigh_4 << " 1;";
//         (*b)[a[my_base_index].neigh_4].resources = 0;
//         ret = 1;
//     }
//     if (a[a[my_base_index].neigh_5].type == 1 && (*b)[a[my_base_index].neigh_5].resources > 0)
//     {
//         cout << "LINE " << my_base_index << " " << a[my_base_index].neigh_5 << " 1;";
//         (*b)[a[my_base_index].neigh_5].resources = 0;
//         ret = 1;
//     }
//     return (ret);
// }






// bool	checker_spawn(crc b, int index, int spawn_index)
// {
// 	(void)b;
// 	return (index == spawn_index);
// }

// bool	checker_my_ants(crc b, int index, int spawn_index)
// {
// 	(void)spawn_index;
// 	return (b[index].my_ants > 0);
// }

// bool	checker_opp_ants(crc b, int index, int spawn_index)
// {
// 	(void)spawn_index;
// 	return (b[index].opp_ants > 0);
// }

// int check_neigh(irc *a, crc b, int lock, int i, vector<int> *beacons, int last_move, int spawn_index ,bool (*checker)(crc, int, int))
// {
//     int tmp;

//     if ((*a)[i].neigh_0 != -1)
//     {
//         (*beacons).push_back((*a)[i].neigh_0); // add beacon neighbor to beacons list
//         tmp = (*a)[i].neigh_0;
//         cout << "0 : " << tmp << " | ";
//         (*a)[i].neigh_0 = -1;
//         if (checker(b, tmp, spawn_index)) // if this neighbor contain ressources keep it in the list
//             return (1);
//         (*beacons).pop_back();
//         // if (tmp != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
//         // {
//         int given_lock = lock;
//         lock = 3;
//         if (given_lock != 0){
//         (*beacons).push_back(tmp); // add beacon neighbor to beacons list

//             tmp = check_neigh(a, b, lock, tmp, beacons, i, spawn_index, checker); // check neighbor neighbors if got ressources
//             if (!tmp)
//             {
//                 cout << "0 pop : " << (*beacons).back() << " | ";

//                 (*beacons).pop_back(); // if no ressources remove the becon from the list
//             }
//             else
//                 return (1); // else if their is ressources keep the neighbor in the list
//         }
//         // else
//         // {
//         //     cout << "0 pop lock : " << (*beacons).back() << " | ";
//         //     (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
//         // }
//     }
//     if ((*a)[i].neigh_1 != -1)
//     {
//         (*beacons).push_back((*a)[i].neigh_1);
//         tmp = (*a)[i].neigh_1;
//         cout << "1 : " << tmp << " | ";
//         (*a)[i].neigh_1 = -1;
//         if (checker(b, tmp, spawn_index)) // if this neighbor contain ressources keep it in the list
//             return (1);
//                 (*beacons).pop_back(); 
//         // if (tmp != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
//         // {
//         int given_lock = lock;
//         lock = 4;
//         if (given_lock != 1){
//         (*beacons).push_back(tmp); // add beacon neighbor to beacons list

//             tmp = check_neigh(a, b, lock, tmp, beacons, i, spawn_index, checker);
//             if (!tmp)
//             {
//                 cout << "1 pop : " << (*beacons).back() << " | ";
//                 (*beacons).pop_back(); 
//             }
//             else
//                 return (1);
//         }
//         // else
//         // {
//         //     cout << "1 pop lock : " << (*beacons).back() << " | ";
//         //     (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
//         // }
//     }
//     if ((*a)[i].neigh_2 != -1)
//     {
//         (*beacons).push_back((*a)[i].neigh_2);
//         tmp = (*a)[i].neigh_2;
//         cout << "2 : " << tmp << " | ";
//         (*a)[i].neigh_2 = -1;
//         if (checker(b, tmp, spawn_index)) // if this neighbor contain ressources keep it in the list
//             return (1);
//                 (*beacons).pop_back(); 
//         // if (tmp != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
//         // {
//         int given_lock = lock;
//         lock = 5;
//         if (given_lock != 2){
//         (*beacons).push_back(tmp); // add beacon neighbor to beacons list

//             tmp = check_neigh(a, b, lock, tmp, beacons, i, spawn_index, checker);
//             if (!tmp)
//             {
//                 cout << "2 pop : " << (*beacons).back() << " | ";
//                 (*beacons).pop_back(); 
//             }
//             else
//                 return (1);
//         }
//         // else
//         // {
//         //     cout << "2 pop lock : " << (*beacons).back() << " | ";
//         //     (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
//         // }
//     }
//     if ((*a)[i].neigh_3 != -1)
//     {
//         (*beacons).push_back((*a)[i].neigh_3);
//         tmp = (*a)[i].neigh_3;
//         cout << "3 : " << tmp << " | ";
//         (*a)[i].neigh_3 = -1;
//         if (checker(b, tmp, spawn_index)) // if this neighbor contain ressources keep it in the list
//             return (1);
//                 (*beacons).pop_back(); 
//         // if (tmp != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
//         // {
//         int given_lock = lock;
//         lock = 0;
//         if (given_lock != 3){
//         (*beacons).push_back(tmp); // add beacon neighbor to beacons list

//             tmp = check_neigh(a, b, lock, tmp, beacons, i, spawn_index, checker);
//             if (!tmp)
//             {
//             cout << "3 pop : " << (*beacons).back() << " | ";

//                 (*beacons).pop_back(); 
//             }
//             else
//                 return (1);
//          }
//         // else
//         // {
//         //     cout << "3 pop lock : " << (*beacons).back() << " | ";
//         //     (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
//         // }
//     }
//     if ((*a)[i].neigh_4 != -1)
//     {
//         (*beacons).push_back((*a)[i].neigh_4);
//         tmp = (*a)[i].neigh_4;
//         cout << "4 : " << tmp << " | ";
//         (*a)[i].neigh_4 = -1;
//         if (checker(b, tmp, spawn_index)) // if this neighbor contain ressources keep it in the list
//             return (1);
//                 (*beacons).pop_back(); 
//         // if (tmp != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
//         // {
//         int given_lock = lock;
//         lock = 1;
//         if (given_lock != 4){
//         (*beacons).push_back(tmp); // add beacon neighbor to beacons list

//             tmp = check_neigh(a, b, lock, tmp, beacons, i, spawn_index, checker);
//             if (!tmp)
//             {
//             cout << "4 pop : " << (*beacons).back() << " | ";
//                 (*beacons).pop_back(); 
//             }
//             else
//                 return (1);
//         }
//         // else
//         // {
//         //     cout << "4 pop lock : " << (*beacons).back() << " | ";
//         //     (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
//         // }
//     }
//     if ((*a)[i].neigh_5 != -1)
//     {
//         (*beacons).push_back((*a)[i].neigh_5);
//         tmp = (*a)[i].neigh_5;
//         cout << "5 : " << tmp << " | ";
//         (*a)[i].neigh_5 = -1;
//         if (checker(b, tmp, spawn_index)) // if this neighbor contain ressources keep it in the list
//             return (1);
//                 (*beacons).pop_back(); 
//         // if (tmp != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
//         // {
//         int given_lock = lock;
//         lock = 2;
//         if (given_lock != 5){
//         (*beacons).push_back(tmp); // add beacon neighbor to beacons list

//             tmp = check_neigh(a, b, lock, tmp, beacons, i, spawn_index, checker);
//             if (!tmp)
//             {
//             cout << "5 pop : " << (*beacons).back() << " | ";

//                 (*beacons).pop_back(); 
//             }
//             else
//                 return (1);
//         }
//         // else
//         // {
//         //     cout << "5 pop lock : " << (*beacons).back() << " | ";

//         //     (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
//         // }
//     }
//     return (0);
// }

// void	add_it_in(vector<pair<int,int>> *spawn, pair<int,int> new_)
// {
// 	bool ref = false;

// 	for (int i = 0; i < spawn->size(); i++){
// 		if (new_.first == (*spawn)[i].first)
// 		{
// 			ref = true;
// 			if (new_.second < (*spawn)[i].second)
// 				(*spawn)[i].second = new_.second;
// 		}
// 	}
// 	if (!ref)
// 		spawn->push_back(new_);
// }

// void	add_it_in_dpair(vector<pair<pair<int,int>,int>> *spawn, pair<pair<int,int>,int> new_)
// {
// 	bool ref = false;

// 	for (int i = 0; i < spawn->size(); i++){
// 		if (new_.first.first == (*spawn)[i].first.first && new_.first.second == (*spawn)[i].first.second)
// 		{
// 			ref = true;
// 			if (new_.second < (*spawn)[i].second)
// 				(*spawn)[i].second = new_.second;
// 		}
// 	}
// 	if (!ref)
// 		spawn->push_back(new_);
// }
