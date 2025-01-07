#include <limits>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

#define test true

#include <iostream>
#include <fstream>




class Node {
    private:
    int coor_x, coor_y;
    std::unordered_map<Node*, int> connections;
};


std::vector<std::vector<int>> maze;
std::queue<std::pair<int, int>> latest;

int main () 
{
    maze.emplace_back();

    std::ifstream file;
    long long result = 0;
    if (test) {
        file.open("test.txt", std::ios::in);
    } else {
        file.open("input.txt", std::ios::in);
    }

    //std::istreambuf_iterator<char> eos;
    //std::string input (std::istreambuf_iterator<char>(file), eos);
    int maximum = std::numeric_limits<int>::max();
    int wall = -1;
    std::pair<int, int> start;
    std::pair<int, int> finish;


    char read_char;
    int i = 0;

    while (not file.eof() and (not (file.peek() == -1))) {
        file.get(read_char);
        if (read_char == '\n') {
            i++;
            maze.emplace_back();
        }
        else if (read_char == '#') {
            maze[i].emplace_back(wall);
        }
        else if (read_char == '.') {
            maze[i].emplace_back(maximum);
        }
        else if (read_char == 'E') {
            finish = std::make_pair(maze[i].size(), i);
            maze[i].emplace_back(0);
            latest.push(finish);
        }
        else if (read_char == 'S') {
            start = std::make_pair(maze[i].size(), i);
            maze[i].emplace_back(maximum);
        }
    }
    file.close();
    
    int znj = 0;
    while (latest.size() > 0) {
        auto coor = latest.front();
        latest.pop();
        std::cout << "Coor: " << coor.first << " " << coor.second << " itr " << znj++ << "\n\t" <<
            maze[coor.second][coor.first] << "\n";
        if (maze[coor.second + 1][coor.first] > maze[coor.second][coor.first]) {
            maze[coor.second + 1][coor.first] = maze[coor.second][coor.first] + 1;
            latest.emplace(coor.first, coor.second + 1);
            std::cout << "\tDown\t" << coor.second +1 << " " << coor.first << maze[coor.second + 1][coor.first] << "\n";
        }
        else {
        }
        if (maze[coor.second - 1][coor.first] > maze[coor.second][coor.first]) {
            maze[coor.second - 1][coor.first] = maze[coor.second][coor.first] + 1;
            latest.emplace(coor.first, coor.second - 1);
            std::cout << "\tUp\t" << coor.second - 1 << " " << coor.first  << maze[coor.second - 1][coor.first] << "\n";
        }
        else {
        }

        if (maze[coor.second][coor.first + 1] > maze[coor.second][coor.first]) {
            maze[coor.second][coor.first + 1] = maze[coor.second][coor.first] + 1;
            latest.emplace(coor.first + 1, coor.second);
            std::cout << "\tRight\t" << coor.second << " " << coor.first + 1 << maze[coor.second][coor.first + 1] << "\n";
        }
        else {
        }

        if (maze[coor.second][coor.first - 1] > maze[coor.second][coor.first]) {
            maze[coor.second][coor.first - 1] = maze[coor.second][coor.first] + 1;
            latest.emplace(coor.first - 1, coor.second);
            std::cout << "\tLeft\t" << coor.second << " " << coor.first - 1  << maze[coor.second][coor.first - 1] << "\n";
        }
        else {
        }
        std::cout << "Latest size: " << latest.size() << "\n\n";
        
        //maze[coor.second][coor.first]
    }

    bool direction_up = false;
    bool direction_up_this = false;
    std::pair<int, int> point;
    int score;
    std::cout << finish.first <<" "<<finish.second<< " " << start.first << " " << start.second<<"\n";
    while (start != finish) {
        point = std::make_pair(start.first, start.second);
        std::cout << "Point " << point.first << " " << point.second << "\n";
        direction_up = direction_up_this;
        if (maze[start.second + 1][start.first] != -1 and maze[start.second + 1][start.first] < maze[point.second][point.first]) {
            point = std::make_pair(start.first, start.second + 1);
            direction_up_this = true;
        }
        if (maze[start.second - 1][start.first] != -1 and maze[start.second - 1][start.first] < maze[point.second][point.first]) {
            point = std::make_pair(start.first, start.second - 1);
            direction_up_this = true;
        }
        if (maze[start.second][start.first + 1] != -1 and maze[start.second][start.first + 1] < maze[point.second][point.first]) {
            point = std::make_pair(start.first + 1, start.second);
            direction_up_this = false;
        }
        if (maze[start.second][start.first - 1] != -1 and maze[start.second][start.first - 1] < maze[point.second][point.first]) {
            point = std::make_pair(start.first - 1, start.second);
            direction_up_this = false;
        }
        if (direction_up_this == direction_up) {
            result++;
        }
        else {
            result += 1000;
        }
        start = std::make_pair(point.first, point.second);
    }

    
    std::cout << "\n" << 
        "Results: "<< result << "\n";
    return 0;
}