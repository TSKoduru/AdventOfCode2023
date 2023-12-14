#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

vector<int> P2(string directions, map<string, pair<string, string>> mappings){
    int steps = 0;
    vector<string> startingNodes;
    vector<int> pathLengths;
    int done = 0;

    // Find all starting nodes, defined by keys that end in 'A'
    for(auto it = mappings.begin(); it != mappings.end(); it++){
        if(it->first[it->first.length() - 1] == 'A'){
            startingNodes.push_back(it->first);
        }
    }

    for(int i = 0; i < startingNodes.size(); i++){
        string current = startingNodes[i];
        int pathLength = 0;
        while(current[current.length() - 1] != 'Z'){
            string next = mappings[current].first;
            if(directions[pathLength % directions.length()] == 'R'){next = mappings[current].second;}
            current = next;
            pathLength++;
        }
        pathLengths.push_back(pathLength);
    }

    return pathLengths;

}

int P1(string directions, map<string, pair<string, string>> mappings){
    int steps = 0;
    string current = "AAA";
    while(current != "ZZZ"){
        string next = mappings[current].first;
        if(directions[steps % directions.length()] == 'R'){next = mappings[current].second;}
        current = next;
        steps++;
    }

    return steps;
}


pair<string, map<string, pair<string, string>>> parseFile(string filename){
    ifstream in(filename); // Take in the first argument (Assuming it's right) and open the input text file
    if(!in.is_open()){cout << "Error: File not found. Try again?";}

    string directions; in >> directions; // Get the first line of the file
    map<string, pair<string, string>> coords; // Go line by line and parse each game individually
    string key; string equalSign; string valueL; string valueR;

    while(in >> key >> equalSign >> valueL >> valueR){
        // Strip off first and last char from valueL
        valueL = valueL.substr(1, valueL.length() - 2);
        valueR = valueR.substr(0, valueR.length() - 1);
        coords[key] = make_pair(valueL, valueR);
    }

    pair<string, map<string, pair<string, string>>> output = make_pair(directions, coords);
    return output;
}

int main(int argc, char* argv[])
{
     if(argc != 2){
        cout << "USAGE: Enter the address to the input file." << endl;
        return -1;
    }

    
    pair<string, map<string, pair<string, string>>> docs = parseFile(argv[1]);
    int P1answer = P1(docs.first, docs.second);
    cout << "Part 1: " << P1answer << endl;

    vector<int> P2answer = P2(docs.first, docs.second); // NOTE: Plug these numbers into an online LCM calculator and that's the answer.
    cout << "Part 2: ";
    for(int i = 0; i < P2answer.size(); i++){
        cout << P2answer[i] << " ";
    }

    return 0;

}