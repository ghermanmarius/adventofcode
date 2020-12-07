//https://adventofcode.com/2020/day/7

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

class Bag {
    public:
    std::tuple<std::string, std::string> colors;
    std::vector<std::tuple<int, std::string, std::string>> unparsedContents;
    std::vector<std::tuple<int, Bag*>> contents;
    bool hasGoldShiny;

    public:
    void ParseContents(std::vector<Bag*> bags) {
        for (int i = 0; i < unparsedContents.size(); ++i) {
            for (int j = 0; j < bags.size(); ++j) {
                if (std::get<0>(bags[j]->colors) == std::get<1>(unparsedContents[i]) &&
                    std::get<1>(bags[j]->colors) == std::get<2>(unparsedContents[i])) {
                        contents.push_back(std::make_tuple(std::get<0>(unparsedContents[i]), bags[j]));
                }
            }
        }
    }
    void Parse(std::string line) {
       std::string color1, color2;
       std::string::size_type pos1, pos2, pos3;
       pos1 = line.find(" ");
       color1 = line.substr(0, pos1);
       pos2 = line.find(" ", pos1 + 1);
       color2 = line.substr(pos1 + 1, pos2 - pos1 - 1);
       colors = std::make_tuple(color1, color2);
       pos3 = line.find("contain");
       pos3 = line.find(" ", pos3);
       std::string s = line.substr(pos3, line.size() - pos3);
       size_t pos = 0;
       std::string token;
       std::string delimiter = ",";
       while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            std::tuple<int, std::string, std::string> bag = GetBags(token);
            if (std::get<0>(bag) != 0) {
                unparsedContents.push_back(bag);
            }
            s.erase(0, pos + delimiter.length());
        }
        std::tuple<int, std::string, std::string> bag = GetBags(s);
            if (std::get<0>(bag) != 0) {
                unparsedContents.push_back(bag);
            }
    }

    void PrintUnparsed() {
         std::cout << std::get<0>(colors) << " " << std::get<1>(colors) << std::endl;
         std::cout << "contents" << std::endl;
         for (int i = 0; i < unparsedContents.size(); ++i) {
             std::cout << "     " << std::get<0>(unparsedContents[i]) << " " << std::get<1>(unparsedContents[i]) << " " << std::get<2>(unparsedContents[i]) << std::endl;
         }
    }

    void Print() {
         std::cout << std::get<0>(colors) << " " << std::get<1>(colors) << std::endl;
         std::cout << "contents" << std::endl;
         for (int i = 0; i < contents.size(); ++i) {
             Bag* bag = std::get<1>(contents[i]);
             std::cout << "     " << std::get<0>(contents[i]) << " " << std::get<0>(bag->colors) << " " << std::get<1>(bag->colors) << std::endl;
         }
    }

    private:
    std::tuple<int, std::string, std::string> GetBags(std::string token) {
        token.erase(0, 1);
        std::string::size_type pos1, pos2, pos3;
        int quantity = 0;
        std::string color1, color2;
        pos1 = token.find(" ");
        std::string q = token.substr(0, pos1);
        if (q == "no") {
            quantity = 0;
            return std::make_tuple(quantity, color1, color2);
        } else {
            quantity = std::stoi(q);
        }
        pos2 = token.find(" ", pos1 + 1);
        color1 = token.substr(pos1 + 1, pos2 - pos1 - 1);
        color2 = token.substr(pos2 + 1, token.find("bag") - pos2 - 2);
        return std::make_tuple(quantity, color1, color2);
    }
};

void dfs1(Bag* bag, std::map<Bag*, bool>& visited, bool& found){
    visited[bag] = true;
    if (bag->hasGoldShiny) {
        found = true;
        return;
    }

    if (std::get<0>(bag->colors) == "shiny" &&
        std::get<1>(bag->colors) == "gold") {
            found = true;
            bag->hasGoldShiny = true;
            return;
        }

    for (int i = 0; i < bag->contents.size() && !found; ++i) {
        if (!visited[std::get<1>(bag->contents[i])]) {
            dfs1(std::get<1>(bag->contents[i]), visited, found);
        }
    }
}

void dfs2(Bag* bag, std::map<Bag*, bool>& visited, int& sum){
    visited[bag] = true;
    sum += 1;
    for (int i = 0; i < bag->contents.size(); ++i) {
        if (!visited[std::get<1>(bag->contents[i])]) {
            dfs2(std::get<1>(bag->contents[i]), visited, sum);
        }
    }
}

int computeCost(Bag* bag, std::map<Bag*, int>& costs) {
    if (costs.find(bag) != costs.end()) {
        return costs[bag];
    }
    int sum = 1;
    for (int i = 0; i < bag->contents.size(); ++i) {
        sum += std::get<0>(bag->contents[i]) * computeCost(std::get<1>(bag->contents[i]), costs);
    } 
    costs.insert(std::pair<Bag*, int>(bag, sum));
    return sum;
}

bool searchForColor(Bag* startPoint, std::vector<Bag*> bags) {
    if (startPoint->hasGoldShiny) return true;
    std::map<Bag*, bool> visited;
    bool found = false;
    for (int i = 0; i < bags.size(); ++i) {
        visited.insert(std::pair<Bag*, bool>(bags[i], false));
    } 
    dfs1(startPoint, visited, found);
    startPoint->hasGoldShiny = found;
    return found;
}

int main() {

    std::ifstream input("2020/7/7.input");
    std::string currentLine;

    std::vector<Bag*> bags;

    while (std::getline(input, currentLine)) {
        Bag* currentBag = new Bag();
        currentBag->hasGoldShiny = false;
        currentBag->Parse(currentLine);
        bags.push_back(currentBag);
    }

    for (int i = 0; i < bags.size(); ++i) {
        bags[i]->ParseContents(bags);
    }

    std::map<Bag*, int> costs;
    int result = 0;
    for (int i = 0; i < bags.size(); ++i) {
        result += searchForColor(bags[i], bags);
        if (std::get<0>(bags[i]->colors) == "shiny" &&
            std::get<1>(bags[i]->colors) == "gold") {
            std::cout << computeCost(bags[i], costs) - 1 << std::endl;
        }
    }
    std::cout << result - 1;

    return 0;
}