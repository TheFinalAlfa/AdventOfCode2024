#include <array>
#include <ios>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>


// Input floor (0,0) is in the upper - left corner
// X is going downwards and Y is going rightwards

// 1825 too high
// 1819


class Guard {
    private:
    int coor_x;
    int coor_y;
    int coor_x_s, coor_y_s;
    std::vector<std::string>& input_floor;

    long long steps_ = 0;
    int direction = 0;
    constexpr static const std::array<std::pair<int, int>, 4> directions = {
        // Coordinate X, Coordinate Y
        std::pair<int, int> (-1,0),
        std::pair<int, int> (0, 1),
        std::pair<int, int> (1, 0),
        std::pair<int, int> (0, -1),
    };

    void next_dir() {
        ++direction;
        if (direction >= directions.size()) {
            direction = 0;
        }
    }

    char peek_next(){
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
                coor_x_s = i;
                coor_y_s = coordinate_y;
                break;
            }
        }
      }

    bool move() {
        coor_x = coor_x_s;
        coor_y = coor_y_s;
        direction = 0;
        steps_ = 0;
        //std::cout << "Starting coordinates: " << coor_x << " " << coor_y << "\n";


        try {
        while (steps_ < 169000) {
            //std::cout << coor_x << " " << coor_y << "\n";
            if (steps_ == 10) {
                //std::cout << "Moving\n";
            }
            steps_++;
            if (peek_next() == '#') {
                next_dir();
            }
            coor_x += directions[direction].first;
            coor_y += directions[direction].second;
        }
        } catch (std::out_of_range) {
        return false;
        }
        return true;
    }
    int steps() const {return steps_;}
    int x_s(){return coor_x_s;}
    int y_s(){return coor_y_s;}
};


int main ()
{
    std::ifstream file;
    file.open("test.txt", std::ios::in);

    int paces = 0;

    std::vector<std::string> input_floor;

    for (std::string line; !file.eof();) {
        file >> line;
        input_floor.push_back(line);
    }

    Guard g(input_floor);

    int loc = 0;

    for (int i = 0; i < input_floor.size(); ++i) {
        for (int j = 0; j < input_floor[0].size(); ++j) {
            std::cout << i << " " << j<< "\n";
            if (i == g.x_s() and j == g.y_s()) {++j;}
            char tmp = input_floor[i][j];
            input_floor[i][j] = '#';

            if (g.move()) {
                loc++;
                //std::cout << "Found!!\n";
            }

            //std::cout << i<< " " << j << " " << input_floor[i][j];
            //std::cout << " " << tmp<< " ";
            input_floor[i][j] = tmp;
            //std::cout << input_floor[i][j] << "\n";
        }
    }

    file.close();
    std::cout << "Total paces: " << paces << "\nLocs: " << loc << "\n";

    return 0;
}
