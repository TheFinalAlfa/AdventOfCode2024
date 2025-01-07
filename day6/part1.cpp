#include <array>
#include <ios>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>


// Input floor (0,0) is in the upper - left corner
// X is going downwards and Y is going rightwards


class Guard {
    private:
    int coor_x;
    int coor_y;
    std::vector<std::string>& input_floor;

    int steps_ = 0;
    int direction = 0;
    constexpr static const std::array<std::pair<int, int>, 4> directions = {
        // Coordinate X, Coordinate Y
        std::pair<int, int> (-1,0),
        std::pair<int, int> (0, 1),
        std::pair<int, int> (1, 0),
        std::pair<int, int> (0, -1),
    };

    std::pmr::unordered_set<std::pair<int, int>> obsticales_loop();


    void next_dir() {
        ++direction;
        if (direction >= directions.size()) {
            direction = 0;
        }
    }

    char peek_next(){
        //std::cout << "Peeking: " << coor_x + directions[direction].first <<
        //    " " << coor_y + directions[direction].second << "\n";
        //std::cout << input_floor.at(coor_x + directions[direction].first)\
        //                  .at(coor_y + directions[direction].second) << "\n";
        return input_floor.at(coor_x + directions[direction].first)\
                          .at(coor_y + directions[direction].second);
    };


    public:
      Guard(std::vector<std::string> &input_floor_) : input_floor(input_floor_) {
        for (int i = 0; i < input_floor.size(); ++i) {
            int coordinate_y = input_floor[i].find('^');
            if (coordinate_y != input_floor[i].npos) {
                coor_x = i;
                coor_y = coordinate_y;
                break;
            }
        }
        std::cout << "Starting coordinates: " << coor_x << " " << coor_y << "\n";
      }

    void move() {
        while (true) {
            if (input_floor[coor_x][coor_y] != '@') {
                input_floor[coor_x][coor_y] = '@';
                steps_++;
                std::cout << "Steps: " << steps_ << "\n";
            }
            if (peek_next() == '#') {
                next_dir();
            }
            coor_x += directions[direction].first;
            coor_y += directions[direction].second;
        }
    }

    int steps() const {return steps_;}
};


int main ()
{
    std::ifstream file;
    file.open("input.txt", std::ios::in);

    int paces = 0;

    std::vector<std::string> input_floor;

    for (std::string line; !file.eof();) {
        file >> line;
        input_floor.push_back(line);
    }

    Guard g(input_floor);

    try {
    g.move();
    } catch (std::out_of_range) {
        paces = g.steps();
    }


    file.close();
    std::cout << "Total paces: " << paces << "\n";

    return 0;
}
