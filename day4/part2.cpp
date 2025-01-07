#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>


bool check(std::vector<std::string> &input, int i, int i_change, int j, int j_change) {
    try {
    return input.at(i + i_change * 1).at(j + j_change * 1) == 'M' 
       and input.at(i + i_change * 2).at(j + j_change * 2) == 'A'
       and input.at(i + i_change * 3).at(j + j_change * 3) == 'S';
    } catch (std::out_of_range) {
        return false;
    }
}


bool x_mas(std::vector<std::string> &input, int i, int j) {
    try {
        return ((input.at(i + 1).at(j + 1) == 'M' and input.at(i - 1).at(j - 1) == 'S')
             or (input.at(i + 1).at(j + 1) == 'S' and input.at(i - 1).at(j - 1) == 'M'))
                and
               ((input.at(i - 1).at(j + 1) == 'M' and input.at(i + 1).at(j - 1) == 'S')
             or (input.at(i - 1).at(j + 1) == 'S' and input.at(i + 1).at(j - 1) == 'M'));
    } catch (std::out_of_range) {
        return false;
    }
}

int main () 
{
    std::ifstream file;
    file.open("input.txt", std::ios::in);
    std::vector<std::string> input;
    for (std::string line; !file.eof();) {
        file >> line;
        input.push_back(line);
    }
    file.close();

    int result = 0;

    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++) {
            if (input[i][j] == 'A') {
                //std::cout << "i: " << i << " j: " << j <<"\n";
                if (x_mas(input, i, j)) {
                    //std::cout << "Passed" <<"\n";
                    result++;
                }
            }
        }
    }
    
    std::cout << "Result: " << result << "\n";
    return 0;
}