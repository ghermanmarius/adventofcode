//https://adventofcode.com/2020/day/1

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    std::ifstream input("2020/1/1.input");
    
    std::string currentNum;
    std::vector<int> values;
    while (std::getline(input, currentNum))
    {
        values.push_back(std::stoi(currentNum));
    }
    
    for (int i = 0; i < values.size(); ++i) {
            for (int j = i + 1; j < values.size(); ++j) {
                for (int k = j + 1; k < values.size(); ++k)
                if (values[i] + values[j] + values[k] == 2020) {
                    std::cout << values[i] * values[j] * values[k];
                    break;
            }
        }
    }
    return 0;
}