#include <cstdlib>
#include <iterator>
#include <regex>
#include <string>
#include <tuple>
#include <vector>

#define test false

#include <iostream>
#include <fstream>

int width, height;


// 218295000 correct :D

class Robots {
    private:
    int coor_x, coor_y;
    int velocity_x, velocity_y;
};


std::tuple<int, int> move_robot(int x, int y, int speed_x, int speed_y, int seconds) {
    x += speed_x * seconds;
    y += speed_y * seconds;
    while (x < 0) {
        x += width;
    }    
    while (y < 0) {
        y += height;
    }
    return std::make_tuple(x % width, y % height);
}

//std::tuple<int, int> move_robot(int x, int y, int speed_x, int speed_y, int seconds) {
//    x += speed_x * seconds;
//    x %= width;
//    y += speed_y * seconds;
//    y %= height;
//    if (x < 0) {
//        x += width;
//    }
//    else if (y < 0) {
//        y += height;
//    }
//    return std::make_tuple(x,y);
//}


int main () 
{
    std::ifstream file;
    long long result = 0;
    if (test) {
        width = 11;
        height = 7;
        file.open("test.txt", std::ios::in);
    } else {
        width = 101;
        height = 103;
        file.open("input.txt", std::ios::in);
    }

    std::istreambuf_iterator<char> eos;
    std::string input (std::istreambuf_iterator<char>(file), eos);
    file.close();

    std::vector<std::tuple<int, int, int, int>> robots; // Button A, B, Destination
    std::regex regex("p=(-?\\d*),(-?\\d*) v=(-?\\d*),(-?\\d*)");

    auto regex_iterator = std::sregex_iterator(input.begin(), input.end(), regex);
    auto end = std::sregex_iterator();

    for (auto j = regex_iterator; j != end; j++) {
        std::smatch matches = *j;
        robots.push_back(std::make_tuple(std::stoi(matches[1].str()), std::stoi(matches[2].str()),
            std::stoi(matches[3].str()), std::stoi(matches[4].str())));
        //std::cout << matches.str() << "\n\t" << matches[1] << " " << matches[2] << " " <<
        //    matches[3] << " " << matches[4] << "\n";
    }

    std::cout << "Robots size: " << robots.size() << "\n";

    int q1 = 0; 
    int q2 = 0;  
    int q3 = 0;
    int q4 = 0;

    for (auto value : robots) {
        auto destination = move_robot(std::get<0>(value), std::get<1>(value), 
            std::get<2>(value), std::get<3>(value), 100);
        
        std::cout << "Robot: \n\t" << std::get<0>(value) << " " << std::get<1>(value) << " " <<
            std::get<2>(value) << " " << std::get<3>(value) << "\n\t" << 
            std::get<0>(destination) << " " << std::get<1>(destination) << "\n";

        if (std::get<1>(destination) < height / 2 and std::get<0>(destination) < width / 2) {
            q1++;
        }
        else if (std::get<1>(destination) < height / 2 and std::get<0>(destination) > width / 2) {
            q2++;
        }
        else if (std::get<1>(destination) > height / 2 and std::get<0>(destination) < width / 2) {
            q3++;
        }
        else if (std::get<1>(destination) > height / 2 and std::get<0>(destination) > width / 2) {
            q4++;
        }
    }

    std::cout << "Qs: " << q1 << " " << q2 << " " << q3 << " " << q4 << "\n";

    result = q1 * q2 * q3 * q4;

    std::cout << "\n" << 
        "Results: "<< result << "\n";
    return 0;
}