#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

int houseOfP1(string card){ // Returns 0 for five of a kind, 1 for four of a kind, 2 for full house, 3 for three of a kind, 4 for two pair, 5 for one pair, and 6 for high card
    map<char, int> houses;
    for(auto c: card){houses[c]++;}

    int max = 0;
    for(auto house: houses){if(house.second > max){max = house.second;}}

    if(max == 5){return 0;}
    if(max == 4){return 1;}
    if(max == 3){
        for(auto house: houses){
            if(house.second == 2){return 2;}
        }
        return 3;
    }
    if(max == 2){
        int pairs = 0;
        for(auto house: houses){
            if(house.second == 2){pairs++;}
        }
        if(pairs == 2){return 4;}
        return 5;
    }
    return 6;
}

struct compareCardsP1{
    bool operator()(pair<string, int> &card1, pair<string, int> &card2){

        map<char, int> sample_map { {'A', 14}, {'K', 13}, {'Q', 12}, {'J', 11}, {'T', 10}, {'9', 9}, {'8', 8}, {'7', 7}, {'6', 6}, {'5', 5}, {'4', 4}, {'3', 3}, {'2', 2}};
        // First, find the houses of the cards and compare them
        int house1 = houseOfP1(card1.first), house2 = houseOfP1(card2.first);
        
        // If one is exclusively better than the other, return that
        if(house1 < house2){return true;}
        if(house1 > house2){return false;}

        // If they're the same, compare the hands by going through the hand from start to end and comparing each card
        for(int i = 0; i < card1.first.length(); i++){
            if(sample_map[card1.first[i]] < sample_map[card2.first[i]]){return false;}
            if(sample_map[card1.first[i]] > sample_map[card2.first[i]]){return true;}
        }

        return false; // Should never reach this point
    }
};

int houseOfP2(string card){ // Returns 0 for five of a kind, 1 for four of a kind, 2 for full house, 3 for three of a kind, 4 for two pair, 5 for one pair, and 6 for high card
    map<char, int> houses;
    for(auto c: card){houses[c]++;}
    int numJokers = houses['J'];
    houses['J'] = 0;

   // This time, Js are wildcards
    int max = 0; char maxChar = ' ';
    for(auto house: houses){
        if(house.second + numJokers> max){
            max = house.second + numJokers; 
            maxChar = house.first;
            }
    }

    houses[maxChar] = max;

    if(max == 5){return 0;}
    if(max == 4){return 1;}
    if(max == 3){
        for(auto house: houses){
            if(house.second == 2){return 2;}
        }
        return 3;
    }
    if(max == 2){
        int pairs = 0;
        for(auto house: houses){
            if(house.second == 2){pairs++;}
        }
        if(pairs == 2){return 4;}
        return 5;
    }
    return 6;
}

struct compareCardsP2{
    bool operator()(pair<string, int> &card1, pair<string, int> &card2){

        map<char, int> sample_map { {'A', 14}, {'K', 13}, {'Q', 12}, {'T', 10}, {'9', 9}, {'8', 8}, {'7', 7}, {'6', 6}, {'5', 5}, {'4', 4}, {'3', 3}, {'2', 2}, {'J', 1}};
        // First, find the houses of the cards and compare them
        int house1 = houseOfP2(card1.first), house2 = houseOfP2(card2.first);
        
        // If one is exclusively better than the other, return that
        if(house1 < house2){return true;}
        if(house1 > house2){return false;}

        // If they're the same, compare the hands by going through the hand from start to end and comparing each card
        for(int i = 0; i < card1.first.length(); i++){
            if(sample_map[card1.first[i]] < sample_map[card2.first[i]]){return false;}
            if(sample_map[card1.first[i]] > sample_map[card2.first[i]]){return true;}
        }

        return false; // Should never reach this point
    }
};


vector<pair<string, int>> parseFile(string filename){
    ifstream in(filename); // Take in the first argument (Assuming it's right) and open the input text file
    if(!in.is_open()){cout << "Error: File not found. Try again?";}

    vector<pair<string, int>> games; // Go line by line and parse each game individually
    string game; int value;

    while(in >> game >> value){games.push_back(make_pair(game, value));}

    return games;
}

int main(int argc, char* argv[])
{
     if(argc != 2){
        cout << "USAGE: Enter the address to the input file." << endl;
        return -1;
    }

    vector<pair<string, int>> cards = parseFile(argv[1]);
    sort(cards.begin(), cards.end(), compareCardsP1()); // This goes lowest to highest
    int P1 = 0;
    for(int i = 0; i < cards.size(); i++){P1 += cards[i].second * (cards.size() - i);}
    cout << "The answer to part one is: " << P1 << endl; 

    sort(cards.begin(), cards.end(), compareCardsP2()); // This goes lowest to highest
    int P2 = 0;
    for(int i = 0; i < cards.size(); i++){P2 += cards[i].second * (cards.size() - i);}
    cout << "The answer to part two is: " << P2 << endl;

    return 0;

}