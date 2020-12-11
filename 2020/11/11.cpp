//https://adventofcode.com/2020/day/11

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

typedef std::vector<std::vector<char>> Layout;


bool checkDir(int posX, int posY, int i, int j, const Layout& layout, bool onlyNeighbors) {
    if (posX + i < 0) return true;
    if (posX + i >= layout.size()) return true;
    if (posY + j < 0) return true;
    if (posY + j >= layout[0].size()) return true;
    if (layout[posX + i][posY + j] == '.') {
        if (onlyNeighbors) return true;
        return checkDir(posX + i, posY + j, i, j, layout, onlyNeighbors);
    }
    if (layout[posX + i][posY + j] == 'L') return true;
    if (layout[posX + i][posY + j] == '#') return false;
    return true;
}


int getNumFreeNeighbors(int posX, int posY, const Layout& layout, bool onlyNeighbors) {
    int numFreeNeighbors = 0;
    for (int i = -1; i <= 1 ; ++i) {
        for (int j = -1; j <= 1; ++j ){
            if (i == 0 && j == 0) continue;
            bool free = checkDir(posX, posY, i, j, layout, onlyNeighbors);
            numFreeNeighbors += free ? 1 : 0;
        }
    }
    return numFreeNeighbors;
}


Layout evolve(const Layout& current, bool& isDifferent, int& numOccupied, bool onlyNeighbors, int freeThreshold) {
    Layout newLayout;
    isDifferent = false;
    numOccupied = 0;
    for (int i = 0; i < current.size(); ++i) {
        std::vector<char> newRow;
        for (int j = 0; j < current[i].size(); ++j) {
            if (current[i][j] == '.') {
                newRow.push_back('.');
            } else if (current[i][j] == 'L' && getNumFreeNeighbors(i, j, current, onlyNeighbors) == 8) {
                newRow.push_back('#');
                isDifferent = true;
            } else if (current[i][j] == '#' && getNumFreeNeighbors(i,j, current, onlyNeighbors) <= freeThreshold) {
                newRow.push_back('L');
                isDifferent = true;
            } else {
                 newRow.push_back(current[i][j]);
            }
            if (newRow[j] == '#') numOccupied++;
            }
            newLayout.push_back(newRow);

        }
        return newLayout;
    }

void printLayout(const Layout& layout) {
     for (int i = 0; i < layout.size(); ++i) {
        for (int j = 0; j < layout[i].size(); ++j) {
            std::cout << layout[i][j];
        }
        std::cout << std::endl;
    }
}

int main() {
    std::ifstream input("2020/11/11.input");
    std::string currentLine;
    Layout layout;
    while (std::getline(input, currentLine)) {
        std::vector<char> row;
        for (int i = 0; i < currentLine.size(); ++i) {
            row.push_back(currentLine.at(i));
        }
        layout.push_back(row);
    }

    bool isDifferent = true;
    int numSeatsOccupied = 0;
    while (isDifferent) {
        //part1
        //layout = evolve(layout, isDifferent, numSeatsOccupied, true, 4);
        //part2
        layout = evolve(layout, isDifferent, numSeatsOccupied, false, 3);
    }

    std::cout << numSeatsOccupied << std::endl;
    return 0;
}
