//https://adventofcode.com/2020/day/14

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <map>
#include <bitset>

void readMask(const std::string& mask, std::vector<std::pair<size_t, size_t>>& overrides, std::vector<size_t>& fluctuating) {
    for (int i = 0; i < 36;  ++i) {
        if (mask.at(i) != 'X') {
            overrides.push_back(std::make_pair(35 - i, mask.at(i) == '0' ? 0 : 1));
        } else {
            fluctuating.push_back(35 - i);
        }
    }
}

void readMem(const std::string& memLine, size_t& address, size_t& value) {
    size_t pos = memLine.find("]");
    address = std::stoull(memLine.substr(4, pos - 4));
    pos = memLine.find("=") + 2;
    value = std::stoull(memLine.substr(pos, memLine.size() - pos));
}

void process1(std::map<size_t, size_t>& data, const std::vector<std::pair<size_t, size_t>>& overrides, const std::vector<std::pair<size_t, size_t>>& mem)
{
    if (mem.size() == 0) return ;
    for (const auto& op : mem)
    {
        std::bitset<36> bits{op.second};
        for (const auto& override : overrides) {
            bits.set(override.first, override.second);
        }
        size_t result = bits.to_ullong();
        data[op.first] = result;
    }
}

void GetAffectedAdresses(size_t address, std::vector<size_t> fluctuating, std::vector<size_t>& result) {
    if (fluctuating.size() == 0) {
        result.push_back(address);
    } else {
        std::bitset<36> bits{address};
        size_t pos = *(fluctuating.end() - 1);
        fluctuating.pop_back();
        GetAffectedAdresses(bits.set(pos, 1).to_ullong(), fluctuating, result);
        GetAffectedAdresses(bits.set(pos, 0).to_ullong(), fluctuating, result);
    }
}

void process2(std::map<size_t, size_t>& data, const std::vector<std::pair<size_t, size_t>>& overrides, const std::vector<size_t>& fluctuating, const std::vector<std::pair<size_t, size_t>>& mem)
{
    if (mem.size() == 0) return ;
    for (const auto& op : mem)
    {
        std::bitset<36> bits{op.first};
        for (const auto& override : overrides) {
            if (override.second == 0) continue;
            if (override.second == 1) bits.set(override.first, override.second);
        }
        std::vector<size_t> affectedAdresses;
        GetAffectedAdresses(bits.to_ullong(), fluctuating, affectedAdresses);
        for (int i = 0 ; i < affectedAdresses.size(); ++i) {
            data[affectedAdresses[i]] = op.second;
        }
    }
}

int main() {
    std::ifstream input("2020/14/14.input");
    std::string currentLine;
    
    std::vector<std::pair<size_t, size_t>> overrides;
    std::vector<size_t> fluctuating;
    std::vector<std::pair<size_t, size_t>> mem;
    std::map<size_t, size_t> data1;
    std::map<size_t, size_t> data2;

    while (std::getline(input, currentLine)) {
        if (currentLine.substr(0, 4) == "mask") {
            process1(data1, overrides, mem);
            process2(data2, overrides, fluctuating, mem);
            mem.clear();
            overrides.clear();
            fluctuating.clear();
            readMask(currentLine.substr(7, 36), overrides, fluctuating);
        }

        if (currentLine.substr(0, 3) == "mem") {
            size_t address;
            size_t value;
            readMem(currentLine, address, value);
            mem.push_back(std::make_pair(address, value));

        }
    }
    process1(data1, overrides, mem);
    process2(data2, overrides, fluctuating, mem);
    size_t sum1 = 0;
    for (const auto& value : data1) {
        sum1 += value.second;
    }
    size_t sum2 = 0;
    for (const auto& value : data2) {
        sum2 += value.second;
    }
    std::cout << sum1 << std::endl << sum2;;
    return 0;
}