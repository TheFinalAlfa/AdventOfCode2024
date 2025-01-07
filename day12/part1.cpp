#include <vector>

#define test true

#include <iostream>
#include <fstream>




class Region {
    private:
    int coor_x, coor_y;
    int area, borders;

    void is_area (int x, int y) {
        if (map[y][x] != map[coor_y][coor_x]) {
            borders++;
        }
        else if (not dealtwith[y][x]) {
            area++;
            dealtwith[y][x] = true;
            if (x + 1 < map[y].size()) {
                is_area(x + 1, y);
            }
            else {
                borders ++;
            }
            if (y + 1 < map.size()) {
                is_area(x, y + 1);
            }
            else {
                borders ++;
            }
            if (x - 1>= 0) {
                is_area(x - 1, y);
            }
            else {
                borders ++;
            }
            if (y - 1 >= 0) {
                is_area(x, y - 1);
            }
            else {
                borders ++;
            }
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
        "Number of stones: "<< result << "\n";
    return 0;
}