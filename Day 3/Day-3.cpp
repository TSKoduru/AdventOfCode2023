#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>
using namespace std;

bool isSymbol(char &ch){
    return (!std::isalnum(ch) && !std::isspace(ch) && ch != '.');
}

int findGears(vector<vector<char>> &input, int i, int j){
    // Check the 8 adjacent cells for digits
    vector<pair<int, int>> seenIndices;
    vector<int> adjacentNums;
    int sum = 0;
    for(int x = i - 1; x <= i + 1; x++){
        for(int y = j - 1; y <= j + 1; y++){
            if(x >= 0 && x < input.size() && y >= 0 && y < input[x].size()){
                if(isdigit(input[x][y]) && find(seenIndices.begin(), seenIndices.end(), make_pair(x, y)) == seenIndices.end()){
                    vector<int> nums;

                    int k = y;
                    // Iterate backwards till you hit a symbol then go forwards, adding all numbers to the vector
                    while(k >= 0 && isdigit(input[x][k])){k--;}
                    k++;
                    while(k < input[x].size() && isdigit(input[x][k])){
                        nums.push_back(input[x][k] - '0');
                        seenIndices.push_back(make_pair(x, k));
                        k++;
                    }
                    
                    // Add the numbers to the sum
                    int tempSum = 0;
                    for(int l = 0; l < nums.size(); l++){tempSum += nums[l] * pow(10, nums.size() - l - 1);}
                    adjacentNums.push_back(tempSum);

                }
            }
        }
    }

    // If there are only two adjacent numbers, multiply them together and return that. Otherwise, return 0
    if(adjacentNums.size() == 2){sum = adjacentNums[0] * adjacentNums[1];}
    return sum;
}

int findParts(vector<vector<char>> &input, int i, int j){
    // Check the 8 adjacent cells for digits
    vector<pair<int, int>> seenIndices;
    int sum = 0;
    for(int x = i - 1; x <= i + 1; x++){
        for(int y = j - 1; y <= j + 1; y++){
            if(x >= 0 && x < input.size() && y >= 0 && y < input[x].size()){
                if(isdigit(input[x][y]) && find(seenIndices.begin(), seenIndices.end(), make_pair(x, y)) == seenIndices.end()){
                    vector<int> nums;

                    int k = y;
                    // Iterate backwards till you hit a symbol then go forwards, adding all numbers to the vector
                    while(k >= 0 && isdigit(input[x][k])){k--;}
                    k++;
                    while(k < input[x].size() && isdigit(input[x][k])){
                        nums.push_back(input[x][k] - '0');
                        seenIndices.push_back(make_pair(x, k));
                        k++;
                    }
                    
                    // Add the numbers to the sum
                    for(int l = 0; l < nums.size(); l++){
                        sum += nums[l] * pow(10, nums.size() - l - 1);
                    }

                }
            }
        }
    }
    return sum;
}

vector<vector<char>>* inputTo2dArr(string &inputFile){
    ifstream file(inputFile);
    char c;
    vector<vector<char>> *input = new vector<vector<char>>;

    if(file.is_open()){
        vector<char> line;

        while(file.get(c)){

            if(c == '\n'){
                input->push_back(line);
                line.clear();
            }

            else{
                line.push_back(c);
            }

        }

        input->push_back(line);
    }

    return input;
}

int P1(vector<vector<char>> &input){
    int answer = 0;
    for(int i = 0; i < input.size(); i++){
        for(int j = 0; j < input[i].size(); j++){
            if(isSymbol(input[i][j])){
                answer += findParts(input, i, j);
            }
        }
    }

    return answer;
}

int P2(vector<vector<char>> &input){
    int answer = 0;
    for(int i = 0; i < input.size(); i++){
        for(int j = 0; j < input[i].size(); j++){
            if(isSymbol(input[i][j])){
                answer += findGears(input, i, j);
            }
        }
    }

    return answer;
}

int main(int argc, char** argv){

    if(argc != 2){
        cout << "USAGE: Enter the address to the input file." << endl;
        return -1;
    }

    string inputFile = argv[1];
    vector<vector<char>> *input = inputTo2dArr(inputFile);
    int answer = P1(*input);
    cout << answer << endl;
    answer = P2(*input);
    cout << answer << endl;


    delete input;

    return 0;
}

