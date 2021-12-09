//https://adventofcode.com/2021/day/1

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    std::ifstream input("input.txt");
    
    std::string currentLine;
    
    int posX = 0, depth = 0, depth2 = 0, aim = 0;
    while (std::getline(input, currentLine))
    {
        std::string command = currentLine.substr(0, currentLine.find(' '));
        int value = std::stoi(currentLine.substr(currentLine.find(' ') + 1, currentLine.size()));

        if (command.compare("forward") == 0) {
            posX += value;
            depth2 += aim * value;
            if (depth2 < 0) {
                depth2 = 0;
            }
            continue;
        }

        if (command.compare("up") == 0) {
            depth -= value;
            if (depth < 0) {
                depth = 0;
            }
            aim -= value;
        } else {
            depth += value;
            aim += value;
        }
    }
    std::cout << depth << " * " << posX << " = " << depth * posX << std::endl;
    std::cout << depth2 << " * " << posX << " = " << depth2 * posX << std::endl;
    
    return 0;
}