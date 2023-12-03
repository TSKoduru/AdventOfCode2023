#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>

std::vector<std::string> split(std::string &str, const char* delim){
    std::vector<std::string> splitStr;
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

int checkColors(std::vector<std::string> colors, int maxRed, int maxGreen, int maxBlue){
    int error = 0;
    for(std::vector<std::string>::iterator it = colors.begin(); it != colors.end(); ++it){

        if(*it == "green"){if(stoi(*(it - 1)) > maxGreen){error = 1; break;}}
        if(*it == "blue"){if(stoi(*(it - 1)) > maxBlue){error = 1; break;}}
        if(*it == "red"){if(stoi(*(it - 1)) > maxRed){error = 1; break;}}
    }
    return error;
}

std::vector<int> getProduct(std::string pull){
    std::vector<int> maxes = {0, 0, 0}; // Max for Red, Green, Blue

    std::vector<std::string> colors = split(pull, " ");
    for(std::vector<std::string>::iterator it = colors.begin(); it != colors.end(); ++it){
        if(*it == "green"){maxes[1] = std::max(maxes[1], stoi(*(it - 1)));}
        else if(*it == "blue"){ maxes[2] = std::max(maxes[2], stoi(*(it - 1)));}
        else if(*it == "red"){maxes[0] = std::max(maxes[0], stoi(*(it - 1)));}
    }
    return maxes;
}

int P2(std::vector<std::vector<std::string>> games){
    int answer = 0;
    
    for(auto game: games){
        std::vector<int> gameMaxes = {0, 0, 0};
         for(std::string &pull: game){
            pull.erase(std::remove(pull.begin(), pull.end(), ';'), pull.end());

            std::vector<int> pullMaxes = getProduct(pull);
            gameMaxes[0] = std::max(gameMaxes[0], pullMaxes[0]);
            gameMaxes[1] = std::max(gameMaxes[1], pullMaxes[1]);
            gameMaxes[2] = std::max(gameMaxes[2], pullMaxes[2]);
         }
            answer += gameMaxes[0] * gameMaxes[1] * gameMaxes[2];
    }

    return answer;
}

int P1(std::vector<std::vector<std::string>> games, int maxRed, int maxBlue, int maxGreen){
    int answer = 0;
    int gameCounter = 0;
    int flag = 0;

    for(auto game: games){
        gameCounter += 1;

        for(std::string &pull: game){
            pull.erase(std::remove(pull.begin(), pull.end(), ';'), pull.end());
            std::cout << pull << "\n";
            std::vector<std::string> colors = split(pull, " ");
            int error = checkColors(colors, maxRed, maxBlue, maxGreen);
            if(error){flag = 1; break;}                    
        }

        if (flag == 1){flag = 0;}
        else {answer += gameCounter;}
    }

    return answer;
}

std::vector<std::vector<std::string>> parseFile(std::string filename){
    std::ifstream in(filename); // Take in the first argument (Assuming it's right) and open the input text file
    if(!in.is_open()){std::cout << "Error: File not found. Try again?";}

    std::vector<std::vector<std::string>> games; // Go line by line and parse each game individually
    std::string game;

    while(getline(in, game)){

        game = game.substr(game.find(":") + 1); // Get rid of the "Game: " part of the line
        std::vector<std::string> splitLine = split(game, ","); // Split the line by commas
        games.push_back(splitLine);

    }

    return games;
}

int main(int argc, char* argv[])
{
    if(argc != 5){
        std::cout << "USAGE: Enter the address to the input file, followed by the number of red, green, and blue cubes." << std::endl;
        return -1;
    }

    int maxRed = atoi(argv[2]), maxBlue = atoi(argv[3]), maxGreen = atoi(argv[4]); // Getting total R, G, B cubes
    std::vector<std::vector<std::string>> games = parseFile(argv[1]);

    int P1answer = P1(games, 12, 13, 14);
    int P2answer = P2(games);

    std::cout << "The answer to part one is: " << P1answer << std::endl;
    std::cout << "The answer to part two is: " << P2answer << std::endl;
    return 0;

}