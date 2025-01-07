#include <array>
#include <cstddef>
#include <functional>
#include <unordered_set>
#include <utility>
#include <vector>

#define test true

#include <iostream>
#include <fstream>


// Part 1 answer: 1363484


class HashPair {
    public:
    size_t operator() (const std::pair<int, int> &o) const {
        size_t first = std::hash<int>{}(o.first);
        size_t second = std::hash<int>{}(o.second);
        return first & second;
    }
};


class Region {
    private:
    int coor_x, coor_y;
    int area, borders;
    std::unordered_set<std::pair<int, int>, HashPair> border;
    std::unordered_set<std::pair<int, int>, HashPair> checked;

    bool is_area(std::pair<int, int> key, std::pair<int, int> & direction) {
        if (
            key.first + direction.first < 0 or 
            key.second + direction.second < 0 or 
            key.first + direction.first >= map[0].size() or 
            key.second + direction.second >= map.size() 
        ) {
            return false;
        }
        return map[key.second + direction.second][key.first + direction.first] == 
            map[coor_y][coor_x];
    }

    void follow_border(std::pair<int, int> key, std::pair<int, int> direction) {
        if ((not checked.contains(key)) and is_area(key, direction)) {
            checked.insert(key);
            auto next = std::make_pair(key.first + direction.first, 
                key.second + direction.second);
            auto prev = std::make_pair(key.first - direction.first, 
                key.second - direction.second);
            if (border.contains(next)) {
                follow_border(next, direction);
            }
            if (border.contains(prev)) {
                follow_border(prev, direction);
            }
        }
    }

    void count_borders() {
        std::cout << "Counting borders!\n";
        checked.clear();
        std::array<std::pair<int, int>, 4>  directions {
            std::make_pair(1, 0),
            std::make_pair(-1, 0),
            std::make_pair(0, 1),
            std::make_pair(0, -1)
        };
        for (
        auto direction = directions.begin(); 
        direction != directions.end(); 
        direction++
        ) {
            std::cout << "Going direction: " << direction->first << " " <<
                direction->second << "\n";
            checked.clear();
            for (auto value : border) {
                if (not checked.contains(value) and 
                    is_area(value, *direction)) {
                        borders++;
                        std::cout << "Borders total: " << border.size() << "\n";
                        follow_border(value, *direction);
                        std::cout << "Checked borders: " << checked.size() << "\n";
                }
            }
        }
        return ;
    }

    bool is_area (int x, int y) {
        if (map[y][x] != map[coor_y][coor_x]) {
            return false;
        }
        else {
            if (not dealtwith[y][x]) {
                area++;
                dealtwith[y][x] = true;
                if (x + 1 < map[y].size()) {
                    if (not is_area(x + 1, y)) {
                        border.insert(std::make_pair(x + 1, y));
                    }
                }
                else {
                    border.insert(std::make_pair(x + 1, y));
                }
                if (x - 1>= 0) {
                    if (not is_area(x - 1, y)) {
                        border.insert(std::make_pair(x - 1, y));
                    }
                }
                else {
                    border.insert(std::make_pair(x - 1, y));
                }

                if (y + 1 < map.size()) {
                    if (not is_area(x, y + 1)) {
                        border.insert(std::make_pair(x, y + 1));
                    }
                }
                else {
                    border.insert(std::make_pair(x, y + 1));
                }
                if (y - 1 >= 0) {
                    if (not is_area(x, y - 1)) {
                        border.insert(std::make_pair(x, y - 1));
                    }
                }
                else {
                    border.insert(std::make_pair(x, y - 1));
                }
            }
            return true;
        } 
    }

    public:
    static std::vector<std::vector<bool>> dealtwith;
    static std::vector<std::vector<int>> map;
    
    Region(int x, int y) :
        coor_x(x),
        coor_y(y),
        area(0),
        borders(0)
        {}
    
    int calculate_cost() {
        is_area(coor_x, coor_y);
        count_borders();
        std::cout << "\nEnd Borders: " << borders << "\n\n";
        return borders * area;
    }
};

std::vector<std::vector<bool>> Region::dealtwith{};
std::vector<std::vector<int>> Region::map{};





int main () 
{
    std::ifstream file;
    long long result = 0;
    if (test) {
        file.open("test.txt", std::ios::in);
    } else {
        file.open("input.txt", std::ios::in);
    }


    Region::map.emplace_back();
    Region::dealtwith.emplace_back();
    char input;
    int y = 0;
 
    while (!file.eof() and file.peek() != -1) {
        file.get(input);
        if (input != '\n') {
            Region::map[y].push_back(input);
            Region::dealtwith[y].push_back(false);
        }
        else {
            Region::map.emplace_back();
            Region::dealtwith.emplace_back();
            y++;
        }
    }
    file.close();
    
    for (int y = 0; y < Region::map.size(); y++) {
        for (int x = 0; x < Region::map[0].size(); x++) {
            if (not Region::dealtwith[y][x]) {
                Region subject(x,y);
                result += subject.calculate_cost();
            }
        }
    }


    std::cout << "\n" << 
        "Price: "<< result << "\n";
    return 0;
}