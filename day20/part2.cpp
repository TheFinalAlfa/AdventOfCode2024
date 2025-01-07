#include <cstddef>
#include <functional>
#include <queue>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

#define test false


#include <iostream>
#include <fstream>

int int_max = 2147483646;
std::pair<int, int> end;
std::pair<int, int> start;

template<>
struct std::hash<std::tuple<int, int, int, int>> {
    std::size_t operator()(const std::tuple<int, int, int, int> & tup) const {
        return (
            std::hash<int>()(std::get<0>(tup)) ^
            std::hash<int>()(std::get<1>(tup)) ^
            std::hash<int>()(std::get<2>(tup)) ^
            std::hash<int>()(std::get<3>(tup))
        );
    }
};


std::vector<std::vector<int>> area;
std::queue<std::pair<int, int>> pathfind;
std::vector<std::pair<int, int>> path;
std::unordered_set<std::tuple<int, int, int, int>> cheats;


// 1519 Too high
// 1507 Correct - minimal is > not >=



// IDEA
// Shorcut_available preuredi da ima še dva argumenta cheat_start_x _y in še cheat time remaining
// Se rekluzivno kliče in pogleda če je veljaven cheat -> dodaja v cheats
// lahko sneaky


int shortcut_avaiable(int x, int y, int minimal = 100) {
    //if (test) {
    //    minimal = 0;
    //}
    int sum = 0;
    //std::cout << "In shortcut: \t" << x << " " << y << "\n";
    if (x + 2 < area.size() and area[y][x + 1] - area[y][x] != 1 and area[y][x + 2] - area[y][x] > minimal) {
        cheats.emplace(x, y, x + 2, y);
        sum++;
    }
    if (x - 2 >= 0 and area[y][x - 1] - area[y][x] != 1 and area[y][x - 2] - area[y][x] > minimal) {
        cheats.emplace(x, y, x - 2, y);
        sum++;
    }
    if (y + 2 < area.size() and area[y + 1][x] - area[y][x] != 1 and area[y + 2][x] - area[y][x] > minimal) {
        cheats.emplace(x, y, x, y + 2);
        sum++;
    }
    if (y - 2 >= 0 and area[y - 1][x] - area[y][x] != 1 and area[y - 2][x] - area[y][x] > minimal) {
        cheats.emplace(x, y, x, y - 2);
        sum++;
    }
    //std::cout << "Sum " << sum << "\n";
    return sum;
}



void pathing(int x, int y) {
    path.emplace_back(x, y);
    //std::cout << "Pathing: " << x << " " << y << "\n";
    if (x + 1 < area[0].size() and area[y][x + 1] > area[y][x] + 1) {
        area[y][x + 1] = area[y][x] + 1;
        pathfind.emplace(x + 1, y);
    }
    if (x - 1 >= 0 and area[y][x - 1] > area[y][x] + 1) {
        area[y][x - 1] = area[y][x] + 1;
        pathfind.emplace(x - 1, y);
    }
    if (y + 1 < area.size() and area[y + 1][x] > area[y][x] + 1) {
        area[y + 1][x] = area[y][x] + 1;
        pathfind.emplace(x, y + 1);
    }
    //std::cout << (area[y - 1][x]) << "\n";
    if (y - 1 >= 0 and area[y - 1][x] > area[y][x] + 1) {
        area[y - 1][x] = area[y][x] + 1;
        pathfind.emplace(x, y - 1);
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

    char read_char;
    int i = 0;
    area.emplace_back();

    while (not file.eof() and (file.peek() != -1)) {
        file.get(read_char);
        //std::cout << read_char;
        switch (read_char) {
            case '\n':
                area.emplace_back();
                i++;
                break;
            case '#':
                area[i].push_back(-1);
                break;
            case '.':
                area[i].push_back(int_max);
                break;
            case 'S':
                start = std::make_pair(area[i].size(), i);
                area[i].push_back(int_max);
                break;
            case 'E':
                end = std::make_pair(area[i].size(), i);
                area[i].push_back(int_max);
                break;
        }
    }
    file.close();
    std::cout << "\n";
    std::cout << "Check!\n";
    pathfind.push(start);
    area[start.second][start.first] = 0;


    std::cout << "Pathfind size: " << pathfind.size() << "\n";


    while (not pathfind.empty()) {
        pathing(pathfind.front().first, pathfind.front().second);
        pathfind.pop();
    }

//    std::cout << "Area:\n";
//    for (int i = 0; i < area.size(); i++) {
//        for (int j = 0; j < area[0].size(); j++) {
//            if (area[i][j] == -1) {
//                std::cout << "#";
//            }
//            else if (area[i][j] == 2147483647) {
//                std::cout << ".";
//            }
//            else {
//                std::cout << area[i][j];
//            }
//        }
//        std::cout << "\n";
//    }
    std::cout << "Path\n";

    for (auto p : path) {
        result += shortcut_avaiable(p.first, p.second);
    }

    std::cout << "\n" << 
        area[end.second][end.first] << " " << area [start.second][start.first] << "\n" <<
        "Results: "<< result << "\n";
    return 0;
}