//https://adventofcode.com/2020/day/5

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    std::ifstream input("2020/5/5.input");
    std::string currentLine;
    std::vector<int> seats;
    int max = 0;
    while (std::getline(input, currentLine)) {
        int id = 0;
        for (int i = 0 ; i < 10; ++i) {
            id += ((currentLine.at(i) == 'B' || currentLine.at(i) == 'R') ? 1 : 0) *
                  (1 << (9 - i));
        }
        if (id > 7 && id < 1017) {
            seats.push_back(id);
        }
        if (id > max) {
            max = id;
        }
    }

    std::cout << max;
    
    std::sort(seats.begin(), seats.end());
    for (int i = 0; i < seats.size() - 1; ++i) {
        if (seats[i] + 1 != seats[i + 1]) {
            std::cout << seats[i] + 1 << std::endl;
        }
        break;
    }
    
    return 0;
}