//https://adventofcode.com/2020/day/2

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    std::ifstream input("2020/2/2.input");
    std::string currentLine;
    int min, max, count, result1 = 0, result2 = 0;
    string letter;
    string password;

    while (std::getline(input, currentLine))
    {
        //parse values
        std::string firstPart = currentLine.substr(0, currentLine.find("-"));
        min = std::stoi(firstPart);
        std::string secondPart = currentLine.substr(currentLine.find("-") + 1, currentLine.find(" "));
        max = std::stoi(secondPart);
        letter = currentLine.at(currentLine.find(":") - 1);
        password = currentLine.substr(currentLine.find(":") + 1, currentLine.size());

        //count number of occurences, part1    
        count = 0;    
        std::string::size_type pos = 0;
        while ((pos = password.find(letter, pos)) != std::string::npos) {
            ++count;
            pos += letter.length();
        }
        result1 += (min <= count && count <= max) ? 1 : 0;

        //count exactly one occurence, part2
        count = (password.at(min) == letter.at(0) ? 1 : 0) +
                (password.at(max) == letter.at(0) ? 1 : 0);
        
        result2 += (count == 1) ? 1 : 0;
        
    }

    std::cout << result1  << std::endl << result2;
    return 0;
}