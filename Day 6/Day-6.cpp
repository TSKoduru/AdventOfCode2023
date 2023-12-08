#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

int P1(){
    vector<int> times = {45, 97, 72, 95}; 
    vector<int> distances = {305, 1062, 1110, 1695};
    vector<int> possiblities;

    for(int race = 0; race < times.size(); race++){
        int raceTime = times[race], raceDistance = distances[race];
        int low = 0, high = 0;

        for(int i = 0; i < raceTime; i++){
            if((raceTime - i) * i > raceDistance){low = i; break;}      
        }

        for(int i = raceTime; i > 0; i--){
            if(i * (raceTime - i) > raceDistance){high = i; break;}      
        }

        possiblities.push_back(high - low + 1);
    }

    // Return the product of the possiblities
    int product = 1;
    for(int i = 0; i < possiblities.size(); i++){
        product *= possiblities[i];
    }

    return product;

    
}

int P2(){
    vector<long long int> times = {45977295};  // Need to switch to long longs because regular ints can't hold the numbers
    vector<long long int> distances = {305106211101695};
    vector<int> possiblities;

    for(int race = 0; race < times.size(); race++){
        long long int raceTime = times[race], raceDistance = distances[race];
        long long int low = 0, high = 0;

        for(long long int i = 0; i < raceTime; i++){
            if((raceTime - i) * i > raceDistance){low = i; break;}      
        }

        for(long long int i = raceTime; i > 0; i--){
            if(i * (raceTime - i) > raceDistance){high = i; break;}      
        }

        possiblities.push_back(high - low + 1);
    }

    // Return the product of the possiblities
    int product = 1;
    for(int i = 0; i < possiblities.size(); i++){
        product *= possiblities[i];
    }

    return product;

    
}

int main(int argc, char* argv[])
{
    int P1answer = P1(); // NOTE: Hardcoding inputs since there's only four of them
    cout << "The answer to part one is: " << P1answer << endl;

    int P2answer = P2(); // NOTE: Still hardcoding inputs since there's only one input
    cout << "The answer to part two is: " << P2answer << endl;

    return 0;

}