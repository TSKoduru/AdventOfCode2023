#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

int P1(vector<vector<int>> input){
    int ans = 0;
    for(auto nums: input){
        int i = nums.size() - 1;
            
            vector<int> solution;
            solution.push_back(nums.back());
            while (nums.size() > 0) {
                for(int i = 0; i < nums.size() - 1; ++i) {nums[i] = nums[i + 1] - nums[i];}
                nums.resize(nums.size() - 1);
                solution.push_back(nums.back());
                if (all_of(nums.begin(), nums.end(), [](int i) {return i == 0;})) {break;}

            }

            ans += accumulate(solution.begin(), solution.end(), 0);
        }

    return ans;
}

int P2(vector<vector<int>> input){
    int ans = 0;
    for(auto nums: input){
        // Reverse the vector
        reverse(nums.begin(), nums.end()); // This is literally the only change we make

        int i = nums.size() - 1;
            
            vector<int> solution;
            solution.push_back(nums.back());
            while (nums.size() > 0) {
                for(int i = 0; i < nums.size() - 1; ++i) {nums[i] = nums[i + 1] - nums[i];}
                nums.resize(nums.size() - 1);
                solution.push_back(nums.back());
                if (all_of(nums.begin(), nums.end(), [](int i) {return i == 0;})) {break;}

            }

            ans += accumulate(solution.begin(), solution.end(), 0);
        }

    return ans;
}

vector<vector<int>> parseInput(string filename) {
    vector<vector<int>> res;
    ifstream in(filename); // Take in the first argument (Assuming it's right) and open the input text file
    if(!in.is_open()){cout << "Error: File not found. Try again?";}
    
    string line;
    while(getline(in, line)){
        vector<int> temp;
        stringstream ss(line);
        int num;
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

    vector<vector<int>> input = parseInput(argv[1]);
    int P1Answer = P1(input);
    cout << "P1: " << P1Answer << "\n";

    int P2Answer = P2(input);
    cout << "P2: " << P2Answer << "\n";


    return 0;
}