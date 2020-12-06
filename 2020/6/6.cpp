//https://adventofcode.com/2020/day/5

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

int main() {

    std::ifstream input("2020/6/6.input");
    std::string currentLine;
    std::vector<int> anwserCount;
    int result1 = 0, result2 = 0;
    std::getline(input, currentLine);

    do {
        std::map<char, int> groupAnswers;
        int groupSize = 0;
        do {
            for (int i = 0; i < currentLine.size(); ++i) {
                if (groupAnswers.count(currentLine.at(i)) == 0) {
                    groupAnswers.insert(std::pair<char, bool>(currentLine.at(i), 1));
                } else {
                    groupAnswers[currentLine.at(i)]++;
                }
            }
            groupSize++;
        } while (std::getline(input, currentLine) && !currentLine.empty());
        result1 += groupAnswers.size();
        std::map<char, int>::iterator it;
        int count = 0;
        for (it = groupAnswers.begin(); it != groupAnswers.end(); it++) {
            if (it->second == groupSize) {
                count++;
            }
        }
        result2 += count;
    } while (std::getline(input, currentLine));

    std::cout << result1 << " " << result2;
    return 0;
}