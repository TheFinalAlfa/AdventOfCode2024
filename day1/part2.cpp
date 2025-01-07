#include <cstdlib>
#include <iostream> 
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

int main () 
{
    std::ifstream file;
    file.open("input.txt", std::ios::in);
    int s;
    std::vector<int> first;
    std::unordered_map<int, int> second ={};
    while (!file.eof())
    {
        file >> s;
        first.push_back(s);
        file >> s;
        if (second.count(s) == 0) {
            second[s] = 1;
            std::cout << s << " " << second[s] << "\n";
        }
        else {
            second[s]++;
            std::cout << s << " " << second[s] << "\n";
        }
    };
    std::cout << "\n\n";

    sort(first.begin(), first.end());
    for (int i : first) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    auto similarity = 0;
    for (int i = 0; i < first.size(); i++) {
        if (second.count(first[i]) == 1) {
            similarity += first[i] * second[first[i]];
            std::cout << first[i] << " " << second[first[i]] << "\n";
        }
    };
    std::cout << "similarity: " << similarity << "\n";
    file.close();
    return 0; 
}