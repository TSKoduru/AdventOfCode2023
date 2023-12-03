#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>

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

int P1(std::vector<std::string> &lines){
    int answer = 0;

    for(auto line: lines){
        int firstDigit = -1, lastDigit = -1;
        for(auto c: line){
            if(isdigit(c)){
                if(firstDigit == -1){firstDigit = c - '0';}
                lastDigit = c - '0';
            }
        }
        answer += firstDigit * 10 + lastDigit;
    }

    return answer;
}

int P2(std::vector<std::string> &lines){

    std::map<std::string, std::string> subStrtoDigits = {{"one", "on1ne"}, {"two", "tw2wo"}, {"three", "thr3ree"}, {"four", "fou4our"}, {"five", "fiv5ive"}, {"six", "si6ix"}, {"seven", "sev7ven"}, {"eight", "eig8ght"}, {"nine", "nin9ine"}};
    std::vector<int> indices;

    for(auto &line: lines){
        for(auto &pair: subStrtoDigits){
            std::string subStr = pair.first;
            std::string digits = pair.second;
            std::string::size_type n = 0;
            while((n = line.find(subStr, n)) != std::string::npos){
                line.replace(n, subStr.size(), digits);
                n += digits.size();
            }
        }


    }
    return P1(lines);
}


std::vector<std::string> parseFile(std::string filename){
    std::ifstream in(filename); // Take in the first argument (Assuming it's right) and open the input text file
    if(!in.is_open()){std::cout << "Error: File not found. Try again?";}

    std::vector<std::string> lines; // Go line by line and parse each line individually
    std::string line;

    while(getline(in, line)){
        lines.push_back(line);
    }

    return lines;
}

int main(int argc, char* argv[])
{
    if(argc != 2){
        std::cout << "USAGE: Enter the address to the input file." << std::endl;
        return -1;
    }

    std::vector<std::string> lines = parseFile(argv[1]);
    std::cout << "Part 1: " << P1(lines) << std::endl;
    std::cout << "Part 2: " << P2(lines) << std::endl;
    return 0;

}