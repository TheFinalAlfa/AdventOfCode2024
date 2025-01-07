#include <cstddef>
#include <cstdlib>
#include <functional>
#include <unordered_set>
#include <utility>
#include <vector>

#define test false

#include <iostream> 
#include <fstream>

struct PairHash {
    size_t operator() (const std::pair<int, int> pair) const noexcept {
        size_t first = std::hash<int> {} (pair.first);
        size_t second = std::hash<int> {} (pair.second);
        return  first & second;
    }
};


class Trailhead {
    int x, y;
    std::unordered_set<std::pair<int, int>, PairHash> peaks;


    int hiketrail(int x, int y, std::vector<std::vector<int>> &map) {
        if (peaks.contains(std::pair<int, int>(x, y))) {
            return 0;
        }
        else if (map[y][x] == 9) {
            //std::cout << "Found!\n";
            peaks.insert(std::make_pair(x, y));
            return 1;
        }
        else {
            //std::cout << x << " " << y << " " << map[y][x] << "\n";
            int result = 0;
            if (y + 1 < map.size() and map[y][x] - map[y + 1][x] == -1) {
                result += hiketrail(x, y + 1, map);
            }
            if (y - 1 >= 0 and map[y][x] - map[y - 1][x] == -1) {
                result += hiketrail(x, y - 1, map);
            }
            if (x + 1 < map[0].size() and map[y][x] - map[y][x + 1] == -1) {
                result += hiketrail(x + 1, y, map);
            }
            if (x - 1 >= 0 and map[y][x] - map[y][x - 1] == -1) {
                result += hiketrail(x - 1, y, map);
            }
            return result;
        }
    }

    public:
    Trailhead(int _x, int _y) :
        x(_x),
        y(_y)
        {}
    int hike(std::vector<std::vector<int>> &map) {
        return hiketrail(x, y, map);
    }
};





int main () 
{
    std::ifstream file;
    long long result = 0;
    if (test) {
        file.open("test.txt", std::ios::in);
    } else {
        file.open("input.txt", std::ios::in);
    }

    int y = 0;
    std::vector<std::vector<int>> topological_map;
    topological_map.emplace_back();
    char input;
    while (!file.eof() and file.peek() != -1) {
        file.get(input);
        if (input != '\n') {
            topological_map[y].push_back(atoi(&input)) ;
        }
        else {
            y++;
            topological_map.emplace_back();
        }
        std::cout << input;
    }
    std::cout << "\n\nMap as saved: \n";

    for (std::vector<int> value : topological_map) {
        for (int i : value) {
            std::cout << i;
        }
        std::cout << "\n";
    }


    std::cout << "\nMap size: " << topological_map.size() <<  "\n";

    for (int i = 0; i < topological_map.size(); i++) {
        std::cout << "Y: " << i << "\n";
        for (int j = 0; j < topological_map[i].size(); j++) {
            std::cout << "X: " << j << "\n";
            if (topological_map[i][j] == 0) {
                Trailhead hike(j, i);
                result += hike.hike(topological_map);
            }
        }
    }
    
    
    std::cout << "\n" << 
        "Number of trails: "<< result << "\n";
    return 0;
}