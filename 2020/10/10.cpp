//https://adventofcode.com/2020/day/10

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::ifstream input("2020/10/10.input");
    std::string currentLine;
    std::vector<int> jolts;
    int maxValue = 0;
    while (std::getline(input, currentLine)) {
        jolts.push_back(std::stoi(currentLine));
    }
    jolts.push_back(0);
    std::sort(jolts.begin(), jolts.end());
    maxValue = jolts[jolts.size() - 1] + 3;
    jolts.push_back(maxValue);

    int diff1 = 0;
    int diff3 = 0;

    for (int i = 1 ; i < jolts.size(); ++i) {
        diff1 += (jolts[i] - jolts[i - 1] == 1) ? 1 : 0;
        diff3 += (jolts[i] - jolts[i - 1] == 3) ? 1 : 0;
    }
    std::cout << diff1 * diff3 << std::endl;;
    
    std::vector<unsigned long long> paths(maxValue + 1, 0); 
    paths[0] = 1;    
    for (int i = 1 ; i < jolts.size(); ++i){
        paths[jolts[i]] += (i - 1 >= 0) ? paths[jolts[i] - 1] : 0;
        paths[jolts[i]] += (i - 2 >= 0) ? paths[jolts[i] - 2] : 0;
        paths[jolts[i]] += (i - 3 >= 0) ? paths[jolts[i] - 3] : 0;
    }

    std::cout << paths[maxValue];

    return 0;
}
