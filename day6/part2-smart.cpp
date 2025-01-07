#include <array>
#include <ios>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>


// Input floor (0,0) is in the upper - left corner
// X is going downwards and Y is going rightwards


// Option 1, 2, 6


class Guard {
    private:
    int coor_x;
    int coor_y;
    std::vector<std::string>& input_floor;

    int steps_ = 1; // Counting starting space
    int direction = 0;
    constexpr static const std::array<std::pair<int, int>, 4> directions = {
        // Coordinate X, Coordinate Y
        std::pair<int, int> (-1,0),
        std::pair<int, int> (0, 1),
        std::pair<int, int> (1, 0),
        std::pair<int, int> (0, -1),
    };

    //std::unordered_map<int, std::unordered_set<int>> obsticales_loop;
    int locs = 0;

    std::array<std::unordered_map<int, std::unordered_set<int>>, 4> traces;


    int next_dir() {
        int t_dir = direction + 1;
        if (t_dir >= directions.size()) {
            t_dir = 0;
        }
        return t_dir;
    }

    char peek_next(){
        //std::cout << "Peeking: " << coor_x + directions[direction].first <<
        //    " " << coor_y + directions[direction].second << "\n";
        //std::cout << input_floor.at(coor_x + directions[direction].first)\
        //                  .at(coor_y + directions[direction].second) << "\n";
        return input_floor.at(coor_x + directions[direction].first)\
                          .at(coor_y + directions[direction].second);
    };

    bool peek_right() {
        int t_dir = next_dir();
        int axis, seek;
        bool descending = directions[t_dir].first < 0 or directions[t_dir].second < 0;
        if (directions[t_dir].first == 0) {
            axis = coor_x;
            seek = coor_y;
        } else {
            axis = coor_y;
            seek = coor_x;
        }
        //std::cout << axis << seek << "\n";

        for (int comparison : traces[t_dir][axis]) {
            std::cout << "Comparison: " << comparison << "\n";
            if (comparison < seek == descending) {
                return true;
            }
        }
        return false;
    }
    

    public:
      Guard(std::vector<std::string> &input_floor_) : input_floor(input_floor_) {
        for (int i = 0; i < input_floor.size(); ++i) {
            int coordinate_y = input_floor[i].find('^');
            if (coordinate_y != input_floor[i].npos) {
                coor_x = i;
                coor_y = coordinate_y;
            }
        }
        std::cout << "Starting coordinates: " << coor_x << " " << coor_y << "\n";
      }

    void move() {
        while (true) {
            if (directions[direction].first == 0) {
                traces[direction][coor_x].insert(coor_y);
            }
            else {
                traces[direction][coor_y].insert(coor_x);
            }

            if (input_floor[coor_x][coor_y] == '.') {
                input_floor[coor_x][coor_y] = '@';
                steps_++;
            }

            if (peek_right()) {
                std::cout << "Found loc\n";
                ++locs;
            }

            if (peek_next() == '#') {
                direction = next_dir();
            }
            

            coor_x += directions[direction].first;
            coor_y += directions[direction].second;
        }
    }

    int steps() const {return steps_;}
    int obsticale_places() const {return locs;}
};


int main ()
{
    std::ifstream file;
    file.open("test.txt", std::ios::in);

    int paces = 0;
    int obsticale_places = 0;

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
        obsticale_places = g.obsticale_places();
    }


    file.close();
    std::cout << "Total paces: " << paces << "\nObsticale places: " <<
        obsticale_places << "\n";

    return 0;
}
