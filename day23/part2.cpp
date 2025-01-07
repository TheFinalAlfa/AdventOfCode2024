#include <cstddef>
#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>

#define test true


#include <iostream>
#include <fstream>


struct SpecialHash {
    std::size_t operator() (const std::unordered_set<std::string> value) const {
        std::size_t result = 1;
        for (auto key : value) {
            result = result ^ std::hash<std::string>()(key);
        }
        return result;
    }
};



std::unordered_map<std::string, std::unordered_set<std::string>> computers;
std::unordered_set<std::string> checked;
std::unordered_set<std::unordered_set<std::string>, SpecialHash> triplets;


std::unordered_set<std::string> intersection_sets(
    const std::unordered_set<std::string> &first, 
    const std::unordered_set<std::string> &second
) {
    std::unordered_set<std::string> result{};
    for (auto value : first) {
        if (second.contains(value)) {
            result.insert(value);
        }
    }
    return result;
}



void find_tripplets(std::string input) {
    for (auto connection : computers[input]) {
        auto result = intersection_sets(computers[input], computers[connection]);
        if (result.size() > 1) {
            for (auto i : result) {
                triplets.insert(std::unordered_set<std::string>{input, connection, i});
            }
        }
    }
}



int main () 
{
    std::ifstream file;
    long long result = 0;
    if (test) {
        file.open("test.txt", std::ios::in);
    } else {
        file.open("input.txt", std::ios::in);
    }

    std::string read_string;
    std::string first, second;

    while (not file.eof() and (file.peek() != -1)) {
        file >> read_string;
        first = read_string.substr(0, 2);
        second = read_string.substr(3, 2);
        if (not computers.contains(first)) {
            computers[first] = std::unordered_set<std::string>{};
        }
        computers[first].insert(second);
        if (not computers.contains(second)) {
            computers[second] = std::unordered_set<std::string>{};
        }
        computers[second].insert(first);
    }
    file.close();
    std::cout << computers.size() << "\n";

    for (auto key : computers) {
        find_tripplets(key.first);
    }

    for (auto trip : triplets) {
        for (auto t : trip) {
            if (t[0] == 't') {
                result++;
                break;
            }
            //std::cout << t << " ";
        }
    }

    std::cout << "Check!\n";
    std::cout << "\n" << 
        "Triplets size: " << triplets.size() << "\n" <<
        "Results: "<< result << "\n";
    return 0;
}