#include <cstddef>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define test false

#include <iostream>
#include <fstream>

//class Solutions {
//    int max_depth = 0; // Za koliko korakov
//    std::unordered_map<int, std::vector<int>> solutions;
//};

//class Stone {
//    private:
//    static std::unordered_map<int, std::vector<std::unordered_multiset<int>>> solutions;
//};
//std::unordered_map<int, std::vector<std::unordered_multiset<int>>> Stone::solutions = 
//    std::unordered_map<int, std::vector<std::unordered_multiset<int>>>();

std::unordered_map<int, std::vector<std::unordered_multiset<int>>> solutions;


std::unordered_multiset<long> equation(long value) {
    if (value == 0) {
        return std::unordered_multiset<long>{1};
    }
    else if (std::to_string(value).size() % 2 == 0) {
        std::string v_in_s = std::to_string(value);
        v_in_s.insert(v_in_s.size() / 2, " ");
        //std::cout << "Eq v_in_s: " << v_in_s << "\n";
        long first, second;
        std::stringstream stream (v_in_s);
        stream >> first >> second;
        //size_t midpoint = v_in_s.size() / 2;
        //std::cout << "Eq midpoint: " << midpoint << "\n";
        //first.resize(midpoint);
        //second.resize(midpoint);
        //for (int i = 0; i < midpoint; i++) {
        //    first[i] = v_in_s[i];
        //    second[midpoint + i] = v_in_s[midpoint + i];
        //    std::cout << "\t" << i << ": " << 
        //        second[midpoint + i] << " " << 
        //        v_in_s[midpoint + i] << "\n";
        //    // Print i: first + vins[i]
        //    //          second + vins[midpoint + i]
        //}
        //std::cout << "\t" << first << " " << second << "\n";
        return std::unordered_multiset<long> {
            first, 
            second
        };
    }
    else {
        return std::unordered_multiset<long>{value * 2024};
    }
}

int calculate(long initial_stone, int depth) {
    std::unordered_multiset<long> result{initial_stone};
    for (int i = 0; i < depth; i++) {
        std::unordered_multiset<long> result2{};
        for (long key : result) {
            result2.merge(equation(key));
        }
        result = result2;
    }
    return result.size();
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

    int stone;
    while (!file.eof()) {
        file >> stone;
        std::cout << "Initial stone: " << stone << "\n";
        result += calculate(stone, 75);
    }

    std::cout << "\n" << 
        "Number of stones: "<< result << "\n";
    return 0;
}