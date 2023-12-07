#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

// Trim function from https://stackoverflow.com/questions/25829143/trim-whitespace-from-a-string
string trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

vector<string> split(string &str, const char* delim){
    vector<string> splitStr;
    char* cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    char* token = strtok(cstr, delim);
    while(token != NULL){
        splitStr.push_back(token);
        token = strtok(NULL, delim);
    }
    delete[] cstr;
    return splitStr;
}

int P1(vector<vector<string>> &cards){
    int answer = 0;

    for(auto card: cards){
        int passedPipe = 0;
        vector<int> winningVals;
        vector<int> myVals;

        for(auto value: card){
            if(value == "|"){passedPipe = 1; continue;}
            if(passedPipe){myVals.push_back(stoi(value));}
            else{winningVals.push_back(stoi(value));}
        }

        int cardScore = 0;
        for(int i = 0; i < winningVals.size(); i++){
            for(int j = 0; j < myVals.size(); j++){
                if(winningVals[i] == myVals[j]){
                    if(cardScore == 0){cardScore = 1;}
                    else{cardScore *= 2;}
                }
            }
        }

        answer += cardScore;
    }


    return answer;
}

int P2(vector<vector<string>> &cards){

    map<int, int> cardCounts;
    for(int i = 0; i < cards.size(); i++){cardCounts[i] = 1;}

    for(int i = 0; i < cards.size(); i++){
        vector<string> card = cards[i];
        vector<int> winningVals;
        vector<int> myVals;
        int passedPipe = 0;

        for(auto value: card){
            if(value == "|"){passedPipe = 1; continue;}
            if(passedPipe){myVals.push_back(stoi(value));}
            else{winningVals.push_back(stoi(value));}
        }

        int winningCards = 0;
        for(int j = 0; j < winningVals.size(); j++){
            for(int k = 0; k < myVals.size(); k++){
                if(winningVals[j] == myVals[k]){winningCards++;}
            }
        }

        // 2, 3
        int futureCard = i + 1;
        for(int counter = 0; counter < winningCards; counter++){
            cardCounts[futureCard] += cardCounts[i];
            futureCard++;
        }
    }

    int answer = 0;
    for(auto card: cardCounts){
        answer += card.second;
    }
    return answer;
}


vector<vector<string>> parseFile(string filename){
    ifstream in(filename); // Take in the first argument (Assuming it's right) and open the input text file
    if(!in.is_open()){cout << "Error: File not found. Try again?";}

    vector<vector<string>> games; // Go line by line and parse each game individually
    string game;

    while(getline(in, game)){

        game = game.substr(game.find(":") + 1); // Get rid of the "Game: " part of the line
        vector<string> splitLine = split(game, " "); // Split the line by commas
        for(auto &s: splitLine){
            s = trim(s);
        }
        games.push_back(splitLine);
    }

    return games;
}

int main(int argc, char* argv[])
{
     if(argc != 2){
        cout << "USAGE: Enter the address to the input file." << endl;
        return -1;
    }

    vector<vector<string>> cards = parseFile(argv[1]);
    int P1answer = P1(cards);

    cout << "The answer to part one is: " << P1answer << endl;

    int P2answer = P2(cards);
    cout << "The answer to part two is: " << P2answer << endl;

    return 0;

}