//https://adventofcode.com/2020/day/8

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

enum Operation {
    Acc,
    Nop,
    Jmp
};

bool checkLoop(std::vector<Operation>& operations, std::vector<int>& values, int& result) {
    std::vector<bool> visited;
    result = 0;
    for (int i = 0; i < operations.size(); ++i) visited.push_back(false);
    int currentIndex = 0;
    while (!visited[currentIndex] && currentIndex != operations.size()) {
        visited[currentIndex] = true;
        switch (operations[currentIndex]){
            case (Acc) :
                result += values[currentIndex];
                currentIndex++;
                break;
            case (Nop) :
                currentIndex++;
                break;
            case (Jmp) :
                currentIndex += values[currentIndex];
                break;
        }
    }
    if (currentIndex == operations.size()) {
        return true;
    }
    return false;
}

int main() {
    std::ifstream input("2020/8/8.input");
    std::string currentLine;
    std::vector<Operation> operations;
    std::vector<int> values;
    while (std::getline(input, currentLine)){
        std::string operation = currentLine.substr(0, 3);
        operations.push_back(operation == "acc" ? Acc : (operation == "nop" ? Nop : Jmp));
        values.push_back(std::stoi(currentLine.substr(4, currentLine.size())));
    }
    int result1 = 0, result2 = 0;;
    checkLoop(operations, values, result1);

    for (int i = 0; i < operations.size(); ++i) {
        if (operations[i] == Acc) continue;
        int result = 0;
        std::vector<Operation> operations1 = operations;
        operations1[i] = operations[i] == Jmp ? Nop : Jmp;
        if (checkLoop(operations1, values, result)) {
            result2 = result;
            break;
        }
    }
    std::cout << result1 << " " << result2;;

    return 0;
}
