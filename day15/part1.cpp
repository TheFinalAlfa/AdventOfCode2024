#include <string>
#include <utility>
#include <vector>

#define test false

#include <iostream>
#include <fstream>


std::string directions = "^>v<";
std::vector<std::vector<char>> map;
std::vector<char> instructions;
std::pair<int, int> robot_coor;



std::pair<int, int> get_direction(char input) {
    if (input == 'v') {
        return std::make_pair(0, +1);
    }
    else if (input == '^') {
        return std::make_pair(0, -1);
    }
    else if (input == '<') {
        return std::make_pair(-1, 0);
    }
    else if (input == '>') {
        return std::make_pair(+1, 0);
    }
};


bool push_box(std::pair<int, int> coor, std::pair<int, int> direction) {
    auto moved = std::make_pair(coor.first + direction.first, coor.second + direction.second);
    //std::cout << "Pushing: " << map[moved.second][moved.first] << " " << map[coor.second][coor.first] << "\n";
    if (map[moved.second][moved.first] == '#') {
        return false;
    }
    else {
        if (map[moved.second][moved.first] == 'O') {
            bool check = push_box(moved, direction);
            //std::cout << "Check " << check  << "\n";
            if (not check) {
                return false;
            }
        }
        //std::cout << map[moved.second][moved.first] << " -> " << map[coor.second][coor.first] << '\n';
        map[moved.second][moved.first] = 'O';
        map[coor.second][coor.first] = '.';
        return true;
    }
}


void move_robot(int position) {
    auto dir = get_direction(instructions[position]);
    auto next = std::make_pair(robot_coor.first + dir.first, robot_coor.second + dir.second);
    //std::cout << "\tNext: " << map[next.second][next.first] << "\n";
    //std::cout << "\tThis: " << map[robot_coor.second][robot_coor.first] << "\n";

    if (map[next.second][next.first] == '#') {
        //std::cout << "going wall\n";
        return;
    }
    else {
        //std::cout << "outh\n";
        if (map[next.second][next.first] == '.') {
            //std::cout << " Dot\n";
        }
        else {
            bool check = push_box(next, dir);
            //std::cout << "Check robot: " << check << "\n";
            if (check) {
                //std::cout << " 0 p\n";
            }
            else {
                //std::cout << " 0 unp\n";
                return;
            }
        }
        robot_coor = next;
    }
    // Poglej ali se lahko premakne v dir
    //      '.' -> samo premakni robot_coor
    //      '0' -> kliči push in premakni
    //      '#' -> ne naredi ničesar
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

    //std::istreambuf_iterator<char> eos;
    //std::string input (std::istreambuf_iterator<char>(file), eos);


    char read_char;
    int i = 0;
    bool newline = true;


    while (not file.eof() and (not (file.peek() == -1))) {
        file.get(read_char);
        //std::cout << read_char << "\n";
        if (read_char == '\n') {
            //std::cout << "New line" << "\n";
            newline = true;
            i++;
        }
        else if (directions.find(read_char) < directions.size()) { // read_char in directions
            //std::cout << "Instructions: " << read_char << "\n";
            instructions.push_back(read_char);
        }
        else if (read_char == '@') {
            robot_coor = std::make_pair(map[i].size(), i);
            map[i].push_back('.');
        }
        else {
            //std::cout << "Map: " << read_char << "\n";
            if (newline) {
                map.emplace_back();
                newline = false;
            }
            map[i].push_back(read_char);
        }
    }

    file.close();
    std::cout << "Input sizes: " << map.size() << " " << 
        map[0].size() << " " << 
        instructions.size() << " " << 
        robot_coor.first << " " << robot_coor.second << "\n";
    

    for (int i = 0; i < instructions.size(); i++) {
        //std::cout << i << "\n";
        //std::cout << "Instructions: " << instructions[i] << "\n";
        //std::cout << "Robot coords: " << robot_coor.first << " " << robot_coor.second << "\n";
        move_robot(i);
        //std::cout << "Robot coords: " << robot_coor.first << " " << robot_coor.second << "\n";
        for (int j = 0; j < map.size(); j++) {
            for (int i = 0; i < map.size(); i++) {
                if (robot_coor.second == j and robot_coor.first == i) {
                    //std::cout << '@';
                }
                else {
                    //std::cout << map[j][i];
                }
            }
        }
    }

    for (int j = 0; j < map.size(); j++) {
        for (int i = 0; i < map.size(); i++) {
            if (map[j][i] == 'O') {
                result += i + 100 * j;
            }
        }
    }

    std::cout << "\n" << 
        "Results: "<< result << "\n";
    return 0;
}