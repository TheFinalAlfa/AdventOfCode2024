#include <cstdlib>
#include <iterator>
#include <ostream>
#include <regex>
#include <string>
#include <utility>
#include <vector>

#define test false

#include <iostream>
#include <fstream>




unsigned long long det(unsigned long long x1 , unsigned long long x2, unsigned long long y1, unsigned long long y2) {
    unsigned long long a = x1 * y2;
    unsigned long long b = x2 * y1;
    if (a >= b) {
        return a - b;
    }
    else {
    return  b - a;
    }
}


bool brute_force(std::pair<unsigned long long, unsigned long long> x, std::pair<unsigned long long, unsigned long long> y, std::pair<unsigned long long, unsigned long long> price, unsigned long long x_times, unsigned long long y_times) {
    unsigned long long x_coor = x.first * x_times + y.first * y_times;
    unsigned long long y_coor = x.second * x_times + y.second * y_times;
    return std::make_pair(x_coor, y_coor) == price;
}


int main () 
{
    std::ifstream file;
    unsigned long long result = 0;
    if (test) {
        file.open("test.txt", std::ios::in);
    } else {
        file.open("input.txt", std::ios::in);
    }

    std::istreambuf_iterator<char> eos;
    std::string input (std::istreambuf_iterator<char>(file), eos);
    file.close();

    std::vector<std::pair<unsigned long long, unsigned long long>> buttons; // Button A, B, Destination
    std::vector<std::pair<unsigned long long, unsigned long long>> price; // Button A, B, Destination
    std::regex regex_buttons("Button [AB]: X\\+(\\d+), Y\\+(\\d+)");
    std::regex regex_prize("Prize: X=(\\d+), Y=(\\d+)");

    auto buttons_iterator = std::sregex_iterator(input.begin(), input.end(), regex_buttons);
    auto price_iterator = std::sregex_iterator(input.begin(), input.end(), regex_prize);
    auto end = std::sregex_iterator();

    for (auto j = buttons_iterator; j != end; j++) {
        std::smatch buttons_matches = *j;
        buttons.push_back(std::make_pair(std::stoull(buttons_matches[1].str()), 
            std::stoull(buttons_matches[2].str())));
        
        std::cout << buttons_matches.str() << "\n\t" << buttons_matches[1] << "\n\t" << buttons_matches[2].str().data() << "\n";
    }
    std::cout << "Prizes!!!\n";
    for (auto i = price_iterator; i != end; i++) {
        std::smatch price_matches = *i;
        price.push_back(std::make_pair(10000000000000 + std::stoull(price_matches[1].str()), 
            10000000000000 + std::stoull(price_matches[2].str())));

        std::cout << price_matches.str() << "\n\t" << price.back().first << "\n\t" << price.back().second << "\n";
    }


    std::cout << "Buttons\n";
    for (auto value : buttons) {
        std::cout << "\t" << value.first << " " << value.second << "\n";
    }
    std::cout << "Prizes:\n";
    for (auto value : price) {
        std::cout << "\t" << value.first << " " << value.second << "\n";
    }


    std::cout << "\nCalculating\n\n";
    unsigned long long c = 0;

    for (unsigned long long p = 0; p < price.size(); p++) {

        std::pair<unsigned long long, unsigned long long> &x_p = buttons[p * 2];
        std::pair<unsigned long long, unsigned long long> &y_p = buttons[p * 2 + 1];
        std::pair<unsigned long long, unsigned long long> &p_p = price[p];


        unsigned long long d = det(x_p.first, x_p.second, y_p.first, y_p.second);
        unsigned long long x = det(p_p.first, p_p.second, y_p.first, y_p.second) / d;
        unsigned long long y = det(x_p.first, x_p.second, p_p.first, p_p.second) / d;

        std::cout << "C during stuff: " << c << std::endl;

        if (x > 0 and y > 0) {
            if (brute_force(x_p, y_p, p_p, x, y)) {
                c++;
                std::cout << 
                    "Price index: " << p << "\n\t" << 
                    "X: " << x_p.first << " " << x_p.second << "\n\t" << 
                    "Y: " << y_p.first << " " << y_p.second << "\n\t" <<
                    "Price: " << p_p.first << " " << p_p.second << "\n\t" << 
                    "Solutions\n\t\t" << 
                    "D: " << d << "\n\t\t" << 
                    "X: " << x << "\n\t\t" << 
                    "Y: " << y << "\n";
                
                result += x * 3 + y;
                std::cout << "Result: " << result << "\n";
            }
            else {
            }
        }
        

        std::cout << "\n";
    }

    std::cout << buttons.size() << " " << price.size() << "\n";

    std::cout << "\n" << 
        "Number of stones: "<< result << "\n" <<
        "C: " << c << "\n";
    return 0;
}


// 80 40
// 38 86


// 80251841036737