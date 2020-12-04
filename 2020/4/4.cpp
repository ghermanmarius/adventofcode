//https://adventofcode.com/2020/day/4

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>

using namespace std;
//constants
const std::vector<string> PassportProperties{"byr",
                                              "iyr",
                                              "eyr",
                                              "hgt",
                                              "hcl",
                                              "ecl",
                                              "pid",
                                              "cid"};
const std::string optionalProperty = "cid";
const std::vector<string> eyeColors{"amb",
                                    "blu",
                                    "brn",
                                    "gry",
                                    "grn",
                                    "hzl",
                                    "oth"};
bool isNumber(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool yearValidator(std::string& value, int min, int max) {
    if (value.size() == 0) return false;
    if (!isNumber(value)) return false;
    int intVal = std::stoi(value);
    if (intVal < min) return false;
    if (intVal > max) return false;
    return true;
}

bool heightValidator(std::string& value, const std::string& unit, int min, int max) {
    if (value.size() == 0) return false;
    std::string::size_type pos;
    if (value.find(unit) != std::string::npos) {
        std::string height = value.substr(0, value.find(unit));
        return isNumber(height) && (std::stoi(height) >= min && std::stoi(height) <= max);
    } else {
        return false;
    }
}

bool hairColorValidator(std::string& value) {
    if (value.size() == 0) return false;
    if (value.at(0) != '#') return false;
    std::string colorValue = value.substr(1, value.size() - 1);
    if (colorValue.size() != 6) return false;
    for (int i = 0; i < colorValue.size(); ++i) {
        if (colorValue.at(i) == '0') continue;
        if (colorValue.at(i) == '1') continue;
        if (colorValue.at(i) == '2') continue;
        if (colorValue.at(i) == '3') continue;
        if (colorValue.at(i) == '4') continue;
        if (colorValue.at(i) == '5') continue;
        if (colorValue.at(i) == '6') continue;
        if (colorValue.at(i) == '7') continue;
        if (colorValue.at(i) == '8') continue;
        if (colorValue.at(i) == '9') continue;
        if (colorValue.at(i) == 'a') continue;
        if (colorValue.at(i) == 'b') continue;
        if (colorValue.at(i) == 'c') continue;
        if (colorValue.at(i) == 'd') continue;
        if (colorValue.at(i) == 'e') continue;
        if (colorValue.at(i) == 'f') continue;
        return false;
    }
    return true;
}


bool eyeColorValidator(std::string& value) {
    for (int i = 0; i < eyeColors.size(); ++i) {
        if (value == eyeColors[i]) return true;
    }
    return false;
}

bool passportIdValidator(std::string& value) {
    if (value.size() != 9) return false;
    return isNumber(value);
}

bool propertyValidator(std::string property, std::string value) {
    
    if (property == "byr") {
        return yearValidator(value, 1920, 2002);
    } else if (property == "iyr") {
        return yearValidator(value, 2010, 2020);
    } else if (property == "eyr") {
        return yearValidator(value, 2020, 2030);
    } else if (property == "hgt") {
        return (heightValidator(value, "cm", 150, 193) || heightValidator(value, "in", 59, 76));
    } else if (property == "hcl") {
        return hairColorValidator(value);
    } else if (property == "ecl") {
        return eyeColorValidator(value);
    } else if (property == "pid") {
        return passportIdValidator(value);
    }
    return true;
}

class Passport {
    std::map<string, bool> hasProperty;
    std::map<string, string> propertyValues;
    
    public:
    bool IsValid() {
        bool valid = true;
        for (int i = 0; i < PassportProperties.size(); ++i) {
            if (PassportProperties[i] == optionalProperty) continue;
            valid = valid && propertyValidator(PassportProperties[i], propertyValues[PassportProperties[i]]);   
         }
         return valid;
    }

    string ToString() {
        std::string serializedValue;
        for (int i = 0; i < PassportProperties.size(); ++i) {
            serializedValue.append(PassportProperties[i]);
            serializedValue.append(":");
            serializedValue.append(propertyValues[PassportProperties[i]]);
            serializedValue.append("\n");
        }
        return serializedValue;
    }

    void ParseLine(std::string line) {
        for (int i = 0; i < PassportProperties.size(); ++i) {
            std::string::size_type pos = 0;
            pos = line.find(PassportProperties[i], pos);
            if (pos != std::string::npos) {
                hasProperty.insert(std::pair<string, bool>(PassportProperties[i], true));
                std::string::size_type delimiterPos = line.find(":", pos);
                std::string::size_type spacePos = line.find(" ", pos);
                if (spacePos != std::string::npos) {
                    spacePos--;
                }
                std::string propertyValue = line.substr(delimiterPos + 1, spacePos - delimiterPos);
                propertyValues.insert(std::pair<string, string>(PassportProperties[i], propertyValue));
            }
        }
    }
};

int main()
{
    std::ifstream input("2020/4/4.input");
    std::vector<Passport> passports;

    std::string currentLine;
    std::getline(input, currentLine);
    int numValid = 0;
    
    do {
        Passport currentPassport;
        do {
             currentPassport.ParseLine(currentLine);     
        }
        while (std::getline(input, currentLine) && !currentLine.empty());
        passports.push_back(currentPassport);
        numValid += currentPassport.IsValid() ? 1 : 0;
    } while (std::getline(input, currentLine));
    
    std::cout << numValid;

    return 0;
}