//https://adventofcode.com/2020/day/12

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>

#define PI 3.14159265

struct Point {
    float x;
    float y;
    void Rotate(float angle) {
        float s = sin(angle * PI / 180);
        float c = cos(angle * PI / 180);

        float _x = x * c - y * s;
        float _y = x * s + y * c;
        x = _x;
        y = _y;
    }
    void Print() {
        std::cout << "(" << x << "," << y << ")";
    }

    void Forward(float dirX, float dirY, long val) {
        x += dirX * val;
        y += dirY * val;
    }

    void Move(char command, int val) {
        if (command == 'N') {
            y += val;
        }
        if (command == 'S') {
            y -= val;
        }
        if (command == 'E') {
            x += val;
        }
        if (command == 'W') {
            x -= val;
        }
    }
};

int main() {
    std::ifstream input("2020/12/12.input");
    std::string currentLine;

    Point pos1 = {0, 0};
    Point dir = {1, 0};
    Point pos2 = {0, 0};
    Point waypoint = {10, 1};

    while (std::getline(input, currentLine)) {
        char command = currentLine.at(0);
        int val = std::stoi(currentLine.substr(1, currentLine.size()));

        if (command == 'N' || command == 'S' || command == 'E' || command == 'W') {
            pos1.Move(command, val);
            waypoint.Move(command, val);
        }
        if (command == 'F') {
            pos1.Forward(dir.x, dir.y, val);
            pos2.Forward(waypoint.x, waypoint.y, val);
        }
        if (command == 'R') {
            dir.Rotate(360 - val);
            waypoint.Rotate(360 - val);
        }
        if (command == 'L') {
            dir.Rotate(val);
            waypoint.Rotate(val);
        }
    }

    std::cout << pos1.x << " " << pos1.y << std::endl;
    std::cout << abs(pos1.x) + abs(pos1.y) << std::endl;

    std::cout << pos2.x << " " << pos2.y << std::endl;
    std::cout << abs(pos2.x) + abs(pos2.y) << std::endl;


    return 0;
}
