//https://adventofcode.com/2020/day/13

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <numeric>

std::vector<std::string> split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

size_t gcd(size_t a, size_t b)
{
  if (b == 0)
    return a;
  return gcd(b, a % b);
}
 
size_t lcm(size_t a, size_t b)
{
    return (a / gcd(a, b)) * b;
}

int main() {
    std::ifstream input("2020/13/13.input");
    std::string currentLine;
    std::getline(input, currentLine);
    long estimate = std::stol(currentLine);
    std::vector<long> ids;
    std::vector<std::pair<size_t, size_t>> departures;
    std::getline(input, currentLine);
    long min = estimate - 1;
    long minId;

    std::vector<std::string> tokens = split(currentLine, ",");
    for (int i = 0; i < tokens.size(); ++i) {
        if (tokens[i] == "x") continue;
        size_t id = std::stoull(tokens[i]);
        if (id - (estimate % id) < min) {

            min = id - (estimate % id);
            minId = id;
        }
        departures.push_back(std::make_pair(id, i));
    }
    std::cout << minId * min << std::endl;

    unsigned long long result = 0;
    unsigned long long step = departures[0].first;
    bool found = false;
    while (!found) {
        found = true;
        result += step;
        for (const auto& nr : departures) {
            if ((result + nr.second) % nr.first != 0) {
                found = false;
            } else {
                step = lcm(step, nr.first);
            }
        }
    }
    std::cout << result;
    return 0;
}