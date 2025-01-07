#include <cstdlib>
#include <iostream> 
#include <fstream>
#include <sstream>
#include <vector>

void safety_check(int a, int b, bool decreasing, int to_skip){}

int legal(std::vector<int> * vector) {
    int a , b, change;
    bool decreasing = vector->at(0) > vector->at(1);
    std::cout << vector->size() << "\n";
    for (int i = 1; i < vector->size(); i++) {
        a = vector->at(i - 1);
        b = vector->at(i);
        change = abs(a - b);
        std::cout << "Legal call: " << i << a << " " << b << " Change: " << change << " Decreasing: " << decreasing << "\n";
        if (change < 1 or change > 3 or (decreasing xor (a > b))) {
            return i;
        }
    }
    return -1;
}

bool check_line(char line[]) {
    std::istringstream stream(line);
    std::vector<int> readings;
    
    int a;
    std::cout << "Original line: ";
    for (int a, i = 0; !stream.eof(); i++) {
        stream >> a;
        readings.push_back(a);
        std::cout << a << " ";
    }

    std::cout << "\n Size: " << readings.size() << "\n";

    int result = legal(&readings);

    std::cout << "First legal: " << result << "\n";

    if (result != -1) {
        std::vector<int> dampned;
        std::cout << "First damp: ";
        for (int i = 0; i < readings.size(); i++) {
            std::cout << i << "\n";
            if (i != result) {
                dampned.push_back(readings[i]);
                std::cout << dampned[i];
            }
        }
        std::cout << "\n";
        result = legal(&dampned);
        if (result != -1) {
            result--;
            dampned.clear();
            for (int i = 0; i < readings.size(); i++) {
                std::cout << i << "\n";
                if (i != result) {
                    dampned.push_back(readings[i]);
                    std::cout << dampned[i];
                }
            }
            std::cout << "\n";
            if (legal(&dampned) != -1) {
                return false;
            }
        }
    }
    return true;
}

int main () 
{
    std::ifstream file;
    file.open("input.txt", std::ios::in);

    int safe_reports = 0;

    char line[30];

    while (!file.eof()) {
        
        file.getline(line, 30);
        
        if (check_line(line)) {
            safe_reports++;
        }
    }

    std::cout << "Number of safe reports: " << safe_reports << "\n";
    file.close();
    return 0; 
}