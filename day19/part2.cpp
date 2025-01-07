#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#define test false

#include <iostream>
#include <fstream>


std::unordered_map<std::string, long> successes;


std::map<char, std::vector<std::string>> towels;
std::vector<std::string> designs;


bool fits_test(std::string towel, std::string design) {
    //std::cout << "\t\tFits check " << *towel << "\n";
    if (towel.size() > design.size()) {
        return false;
    }
    for (int i = 0; i < towel.size(); i++) {
        //std::cout << "\t\t\t" << *(design + i) << " " << towel->at(i) << "\n";
        if (towel[i] != design[i]) {
            return false;
        }
    }
    return true;
}


long find_towel(std::string design) {
    //std::cout << "\t" << design << "\n";
    if (successes.contains(design)) {
        //std::cout << successes.size() << "\n";
        return successes[design];
    }
    else {
        long solutions = 0;
        for (std::string towel : towels[design[0]]) {
            //std::cout << "\tTowel: " << towel << "\n";
            if (fits_test(towel, design)) {
                //std::cout << "\tFound match\n";
                if (design.size() == towel.size()) {
                    //std::cout << "END\n";
                    //successes[design] = true;
                    solutions++;
                }
                else {
                    long a = find_towel(design.substr(towel.size()));
                    //if (a > 0) {
                    //    successes[design] = true;
                    //}
                    solutions += a;
                }
            }
        }
        //if (solutions == 0) {
        //    successes[design] = false;
        //}
        successes[design] = solutions;
        return solutions;
    }
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

    std::string input;

    while (file.peek() != '\n') {
        file >> input;
        if (towels.contains(input[0])) {
            towels[input[0]].push_back(input);
        }
        else {
            towels[input[0]] = std::vector<std::string>{input};
        }
    }
    std::cout << "Towels size: " << towels.size() << "\n";


    while (not file.eof()) {
        file >> input;
        designs.push_back(input);
    }
    std::cout << "Designs size: " << designs.size() << "\n";

    file.close();


    for (auto value : designs) {
        std::cout << "Design to check: " << value << "\n";
        result += find_towel(value);
    }
    

    std::cout << "\n" << 
        "Results: "<< result << "\n";
    return 0;
}