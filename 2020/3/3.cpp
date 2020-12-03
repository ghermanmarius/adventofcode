//https://adventofcode.com/2020/day/3

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

unsigned long long countTrees(const std::vector<std::vector<bool>>& map, const std::tuple<int, int> movement) {
    int posX = 0, posY = 0;
    unsigned long long count = 0;
    int height = map.size();
    int length = map[0].size();

    while (posY < height) {
        count += map[posY][posX] ? 1 : 0;
        posX += std::get<0>(movement);
        posY += std::get<1>(movement);
        posX %= length;  
    }
    return count;
}

int main()
{
    std::ifstream input("2020/3/3.input");
    std::string currentLine;
    
    std::getline(input, currentLine);
    
    int length = currentLine.size();
    int height = 0;
    std::vector<std::vector<bool>> map;
    
    do {
        std::vector<bool> row;
        for (int i = 0; i < length; ++i) {
            row.push_back(currentLine.at(i) == '.' ? false : true);
        }
        map.push_back(row);
        height++;
    } while (std::getline(input, currentLine));

    //std::cout << countTrees(map, std::make_tuple(3, 1));
    unsigned long long result = countTrees(map, std::make_tuple(1, 1)) *
                 countTrees(map, std::make_tuple(3, 1)) *
                 countTrees(map, std::make_tuple(5, 1)) *
                 countTrees(map, std::make_tuple(7, 1)) *
                 countTrees(map, std::make_tuple(1, 2));

    std::cout << result;

}