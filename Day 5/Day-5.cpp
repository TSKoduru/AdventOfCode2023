#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

int64_t x_to_y(int64_t step, vector<vector<int64_t>> inputMap){
    for(vector<int64_t> m : inputMap){
        int64_t destStart = m[0], sourceStart = m[1], rangeLength = m[2];
        if(step >= sourceStart && step < sourceStart + rangeLength){
            step = destStart + (step - sourceStart);
            break;
        }
    }
    return step;
}

int64_t P1(vector<int64_t> seeds, vector<vector<vector<int64_t>>> maps){
    int64_t res = 1000000000000;
    for(int64_t seed : seeds){
        for(vector<vector<int64_t>> map : maps){
            seed = x_to_y(seed, map);
        }
        res = min(res, seed);
    }
    return res;
}

pair<vector<int64_t>, vector<vector<vector<int64_t>>>> parseInput(string filename) {
    vector<vector<int>> res;
    ifstream in(filename); // Take in the first argument (Assuming it's right) and open the input text file
    if(!in.is_open()){cout << "Error: File not found. Try again?";}
    
    // STEP 1: Read in the seeds
    string line; getline(in, line);
    vector<int64_t> seeds; int64_t seed; stringstream ss(line);
    while(ss >> seed){seeds.push_back(seed);}

    // STEP 2: Read in maps
    // OUTPUT FORMAT: [[[1, 2, 3], [4, 5, 6]], [[7, 8, 9], [10, 11, 12]]]

    vector<vector<vector<int64_t>>> maps; vector<vector<int64_t>> map;
    getline(in, line); // Skip the empty line
    while(getline(in, line)){
        vector<int64_t> lineNums; 

        // If the line is empty, we've reached the end of the map and need to add it to the list of maps
        if(line.empty()){
            maps.push_back(map);
            map.clear(); 
            continue;
        }

        // Otherwise, we need to parse the line
        stringstream ss(line); int64_t num;
        while(ss >> num){lineNums.push_back(num);}
        map.push_back(lineNums); 
    }

    // Push back the last map
    maps.push_back(map);

    // STEP 4: Return the seeds and the maps
    pair<vector<int64_t>, vector<vector<vector<int64_t>>>> resPair(seeds, maps);
    return resPair;
}

int main(int argc, char* argv[])
{
    if(argc != 2){
        cout << "USAGE: Enter the address to the input file." << endl;
        return -1;
    }

    pair<vector<int64_t>, vector<vector<vector<int64_t>>>> input = parseInput(argv[1]);
    vector<int64_t> seeds = input.first;
    vector<vector<vector<int64_t>>> maps = input.second;

    cout << "Part 1: " << P1(seeds, maps) << endl;
    
}