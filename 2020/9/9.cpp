//https://adventofcode.com/2020/day/9

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>



int main() {
    std::ifstream input("2020/9/9.input");
    std::string currentLine;
    int length = 25, currentIndex= 0;
    std::vector<unsigned long long> values;
    unsigned long long invalidNumber = 0;
    while (std::getline(input, currentLine)){
        currentIndex++;
        unsigned long long num = std::stoull(currentLine);
        values.push_back(num);

        if (currentIndex > length) {

            bool isSum = false;
            for (int i = currentIndex - length - 1; i < currentIndex - 1; ++i) 
                for (int j = i + 1; j < currentIndex && j < values.size(); ++j) {
                    if (values[i] + values[j] == num) {
                        isSum = true;
                    }
                }
            if (!isSum) {
                invalidNumber = num;
                std::cout << num << std::endl;
            }
        }
    }
    for (int searchLength = 2; searchLength < values.size(); ++searchLength) {
        for (int i = 0; i < values.size() - searchLength; ++i) {
            unsigned long long currentSum = 0;
            unsigned long long min = values[i];
            unsigned long long max = values[i];
            for (int j = i; j < i + searchLength; ++j) {
                currentSum += values[j];
                if (min > values[j]) min = values[j];
                if (max < values[j]) max = values[j];
            }
            if (currentSum == invalidNumber) {
                std::cout << min + max;
            }
        }
    }

    return 0;
}
