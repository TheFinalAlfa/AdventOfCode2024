#include <cstddef>
#include <exception>
#include <functional>
#include <string>
#include <unordered_map>
#define test false

#include <iostream> 
#include <fstream>
#include <unordered_set>

using std::unordered_set;

// 321 too high
// 320


class MyException : public std::exception {
    private:
    std::string msg;
    public:
    MyException(const char* msg_)
        : msg(msg_){}
    const char* what() const throw()
    {
        return msg.c_str();
    }
};


class Vector2D {
private:
    int _x, _y;

public:
    Vector2D() {};
    Vector2D(int x, int y) : _x(x), _y(y) {};
    bool operator==(const Vector2D &second) const {
        return _x == second._x and _y == second._y;
    };
    int x() const { return _x; };
    int y() const { return _y; };

    Vector2D mirror(Vector2D const & to_mirror, int bounds) {
        int delta_x = _x + _x - to_mirror._x;
        int delta_y = _y + _y - to_mirror._y;
        if (delta_x < 0 or delta_x >= bounds or delta_y < 0 or delta_y >= bounds) {
            throw MyException("Out of Bounds");
        }
        else {
            return Vector2D(delta_x, delta_y);
        }
    }

    
};


struct Vector2D_Hash {
    std::size_t operator () (const Vector2D &v) const noexcept {
        return std::hash<int>() (v.x());
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
    //file.open("test.txt", std::ios::in);
    std::unordered_map<char, unordered_set<Vector2D, Vector2D_Hash>> points;
    int bounds = -1;
    for (int y = 0; !file.eof(); ++y) {
        std::string line;
        file >> line;
        if (bounds == -1) {
            bounds = line.size();
        }
        for (int x = 0; x < line.size(); ++x) {
            if (line[x] != '.') {
                points[line[x]].insert(Vector2D(x, y));
            }
        }
    }
    file.close();

    int unique = 0;
    unordered_set<Vector2D, Vector2D_Hash> antinodes;
    for (auto nodes : points) {
        unique++;
        std::cout << "Nodes[0]: " << nodes.first << "\n";
        for (auto node: nodes.second) {
            std::cout << "Compared: " << node.x() << " " << node.y() << "\n";
            for (auto to_mirror: nodes.second) {
                std::cout << "\tMirroring: " << to_mirror.x() << " " << to_mirror.y();
                if (node != to_mirror) {
                    try {
                        Vector2D mirrored = node.mirror(to_mirror, bounds);
                        if (antinodes.contains(mirrored)) {
                            std::cout << "\tAlready present!\n";
                        }
                        else {
                            std::cout << "\tInserting: " << mirrored.x() <<
                                " " << mirrored.y() << "\n";
                            antinodes.insert(mirrored);
                        }
                    } catch (MyException& e) {
                        std::cout << "\tCaught: " << e.what() << "\n";
                    }
                }
                else {
                std::cout << "\tSame node!\n";
                }
            }
        }
    }

    //unordered_set<Vector2D, Vector2D_Hash> temp_t;
    //Vector2D i (1,1);
    //temp_t.insert(i);

    std::cout << 
        "Points size: " << points.size() << "\n" <<
        "Bounds: " << bounds << "\n" <<
        "Contains 44 23: "<< true << antinodes.contains(Vector2D(44,23)) << "\n" <<
        points.size() << " " << unique << "\n" <<
        "Map: " << antinodes.size() << "\n" << 
        "Result of correct ones: "<< result << "\n";
    return 0;
}