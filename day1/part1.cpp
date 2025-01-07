#include <cstdlib>
#include <iostream> 
#include <fstream>
#include <vector>
#include <algorithm>

int main () 
{
    std::ifstream file;
    file.open("input.txt", std::ios::in);
    int s;
    std::vector<int> first;
    std::vector<int> second;
    while (!file.eof())
    {
        file >> s;
        first.push_back(s);
        file >> s;
        second.push_back(s);
    };
    sort(first.begin(), first.end());
    sort(second.begin(), second.end());
    auto distance_total = 0;
    for (int i = 0; i < first.size(); i++) {
        distance_total += abs(first[i] - second[i]);
    };
    std::cout << distance_total << "\n";
    return 0; 
}