#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

vector<vector<int>> parseInput(string filename) {
    vector<vector<int>> res;
    ifstream in(filename); // Take in the first argument (Assuming it's right) and open the input text file
    if(!in.is_open()){cout << "Error: File not found. Try again?";}
    
    // Read in first line, get rid of everything up to the first integer, then push back all integers separated by commas
    string line;
    in >> line;
    line = line.substr(line.find_first_of("0123456789"));
    vector<int> seeds;
    while(line.find_first_of(" ") != string::npos){
        seeds.push_back(stoi(line.substr(0, line.find_first_of(" "))));
        line = line.substr(line.find_first_of(" ") + 1);
    }

    // Now we need to read in the maps
    vector<vector<int>> maps;
    while(!in.eof()){
        vector<int> map;
        in >> line;
        line = line.substr(line.find_first_of("0123456789"));
        while(line.find_first_of(" ") != string::npos){
            map.push_back(stoi(line.substr(0, line.find_first_of(" "))));
            line = line.substr(line.find_first_of(" ") + 1);
        }
        maps.push_back(map);
    }
}

int main(int argc, char* argv[])
{
    if(argc != 2){
        cout << "USAGE: Enter the address to the input file." << endl;
        return -1;
    }

    vector<vector<int>> input = parseInput(argv[1]);


    return 0;
}