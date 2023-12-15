#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

string NORTH = "S|LJ";
string EAST = "S-LF";
string WEST = "S-J7";
string SOUTH = "S|7F";

// Define method for string to check whether a char is in it
bool in(string s, char c){
    for(int i = 0; i < s.size(); ++i){if(s[i] == c){return true;}}
    return false;
}

bool is_valid(vector<vector<char>> &input, pair<int, int> &coord1, pair<int, int> &coord2){
        int r1 = coord1.first, c1 = coord1.second, r2 = coord2.first, c2 = coord2.second;
        char v1 = input[r1][c1], v2 = input[r2][c2];

        if (r1 == r2){
            if (c2 - c1 == 1 && in(EAST, v1) && in(WEST, v2)){return true;}
            if (c1 - c2 == 1 && in(WEST, v1) && in(EAST, v2)){return true;}
        }

        if (c1 == c2){
            if (r2 - r1 == 1 && in(SOUTH, v1) && in(NORTH, v2)){return true;}
            if (r1 - r2 == 1 && in(NORTH, v1) && in(SOUTH, v2)){return true;}
        }

        return false;
}

vector<pair<int, int>> get_adjacent(pair<int, int> &coord, vector<vector<char>> &input){
    vector<pair<int, int>> res;
    // Check if all 4 neighbors are within range and then add them to res if so
    if(coord.first + 1 < input.size()){res.push_back(make_pair(coord.first + 1, coord.second));}
    if(coord.first - 1 >= 0){res.push_back(make_pair(coord.first - 1, coord.second));}
    if(coord.second + 1 < input[0].size()){res.push_back(make_pair(coord.first, coord.second + 1));}
    if(coord.second - 1 >= 0){res.push_back(make_pair(coord.first, coord.second - 1));}
    return res;
}

vector<pair<int, int>> get_connected(pair<int, int> &coord, vector<vector<char>> &input){
    vector<pair<int, int>> res;
    // Return everything in get_adjacent that is valid
    vector<pair<int, int>> adjacent = get_adjacent(coord, input);
    for(auto adj: adjacent){
        if(is_valid(input, coord, adj)){res.push_back(adj);}
    }
    return res;
}

int P1(vector<vector<char>> input, pair<int, int> start){
    set<pair<int, int>> loop;
    set<pair<int, int>> to_explore = {start};

    while(to_explore.size() > 0){
        auto coord = *to_explore.begin();
        to_explore.erase(to_explore.begin());
        loop.insert(coord);
        for(auto connected: get_connected(coord, input)){
            if(!loop.count(connected)){
                to_explore.insert(connected);
            }
        }
    }
    return (int)(loop.size() + 1)/2;

}

int P2(vector<vector<char>> input, pair<int, int> start){

    // First we do literally the same thing as P1
    set<pair<int, int>> loop;
    set<pair<int, int>> to_explore = {start};

    while(to_explore.size() > 0){
        auto coord = *to_explore.begin();
        to_explore.erase(to_explore.begin());
        loop.insert(coord);
        for(auto connected: get_connected(coord, input)){
            if(!loop.count(connected)){
                to_explore.insert(connected);
            }
        }
    }
}

pair<int, int> findStart(vector<vector<char>> input){
    for(int i = 0; i < input.size(); ++i){
        for(int j = 0; j < input[i].size(); ++j){
            if(input[i][j] == 'S'){return make_pair(i, j);}
        }
    }
    return make_pair(-1, -1);
}

vector<vector<char>> parseInput(string filename) {
    vector<vector<char>> res;
    ifstream in(filename); // Take in the first argument (Assuming it's right) and open the input text file
    if(!in.is_open()){cout << "Error: File not found. Try again?";}
    
    string line;
    while(getline(in, line)){
        vector<char> temp;
        stringstream ss(line);
        char num;
        while(ss >> num){temp.push_back(num);}
        res.push_back(temp);
    }

    return res;
}

int main(int argc, char* argv[])
{
    if(argc != 2){
        cout << "USAGE: Enter the address to the input file." << endl;
        return -1;
    }

    vector<vector<char>> input = parseInput(argv[1]);
    pair<int, int> start = findStart(input);

    int P1Answer = P1(input, start);
    cout << "P1: " << P1Answer << endl;

    return 0;
}