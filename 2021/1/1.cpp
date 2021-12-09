//https://adventofcode.com/2021/day/1

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    std::ifstream input("input.txt");
    
    std::string currentNum;
    std::vector<int> values;
    
    while (std::getline(input, currentNum))
    {
        values.push_back(std::stoi(currentNum));
    }
    int total = 0;
    for (int i = 1; i < values.size(); ++i) {
        total += values[i] > values[i - 1] ? 1 : 0;        
    }
    std::cout << total << std::endl;
    total = 0;
    for (int i = 0; i < values.size() - 3; ++i) {
        total += values[i] < values[i + 3] ? 1 : 0;        
    }
    std::cout << total;
    return 0;
}