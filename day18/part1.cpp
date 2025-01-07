#include <array>
#include <queue>
#include <utility>
#include <vector>

#define test false


#include <iostream>
#include <fstream>

const int map_size = 71;
int count;

std::array<std::array<int, map_size>, map_size> area;
std::vector<std::pair<int, int>> incoming_mem;
std::queue<std::pair<int, int>> pathfind;


void populate_area(int count) {
    for (int i = 0; i < count; i++) {
        area[incoming_mem[i].second][incoming_mem[i].first] = -1;
    }
}


void pathing(int x, int y) {
    if (x + 1 < map_size and area[y][x + 1] > area[y][x] + 1) {
        area[y][x + 1] = area[y][x] + 1;
        pathfind.emplace(x + 1, y);
    }
    if (x - 1 >= 0 and area[y][x - 1] > area[y][x] + 1) {
        area[y][x - 1] = area[y][x] + 1;
        pathfind.emplace(x - 1, y);
    }
    if (y + 1 < map_size and area[y + 1][x] > area[y][x] + 1) {
        area[y + 1][x] = area[y][x] + 1;
        pathfind.emplace(x, y + 1);
    }
    if (y - 1 >= 0 and area[y - 1][x] > area[y][x] + 1) {
        area[y - 1][x] = area[y][x] + 1;
        pathfind.emplace(x, y - 1);
    }
}


int main () 
{
    for (int i = 0; i < map_size; i++) {
        area[i].fill(2147483647);
    }
    std::ifstream file;
    long long result = 0;
    if (test) {
        file.open("test.txt", std::ios::in);
        count = 12;
    } else {
        count = 1024;
        file.open("input.txt", std::ios::in);
    }

    char read_char;
    int i, j;

    while (not file.eof() and (not (file.peek() == -1))) {
        file >> i >> j;
        incoming_mem.emplace_back(i,j);
    }
    file.close();

    std::cout << "Incoming memory size: "<< incoming_mem.size() << "\n";
    
    area[0][0] = 0;
    populate_area(count);
    pathfind.push(std::make_pair(0, 0));


    std::cout << "Area:\n";
    for (int i = 0; i < map_size; i++) {
        for (int j = 0; j < map_size; j++) {
            if (area[i][j] == -1) {
                std::cout << "#";
            }
            else if (area[i][j] == 2147483647) {
                std::cout << ".";
            }
            else {
                std::cout << area[i][j];
            }
        }
        std::cout << "\n";
    }

    while (not pathfind.empty()) {
        pathing(pathfind.front().first, pathfind.front().second);
        pathfind.pop();
    }

    result = area[map_size - 1][map_size - 1];

    std::cout << "\n" << 
        "Results: "<< result << "\n";
    return 0;
}