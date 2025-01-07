#include <cstdlib>
#include <iostream> 
#include <fstream>
#include <sstream>

int main () 
{
    std::ifstream file;
    file.open("input.txt", std::ios::in);

    int a, b; // first and second values
    int change; // How much did the value change
    bool decreasing; // If values are decreasing

    int safe_reports = 0;

    char line[30];

    while (!file.eof()) {
        
        file.getline(line, 30);
        std::istringstream line_stream(line);
        
        bool safe = true;

        line_stream >> a >> b;

        if ((abs(a - b) > 3) or (abs(a - b) < 1)) {
            safe = false;
        }
        decreasing = a > b;
        
        while (!line_stream.eof() and safe) {
            a = b;
            line_stream >> b;
            
            if ((abs(a - b) > 3) or (abs(a - b) < 1)) {
                safe = false;
            }
            if ((a > b) xor decreasing) {
                safe = false;
            }
        }
        if (safe) {
            std::cout << line << "\n";
            safe_reports++;
        }
    }

    std::cout << safe_reports << "\n";
    file.close();
    return 0; 
}