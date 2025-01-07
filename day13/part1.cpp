#include <cstdlib>
#include <iterator>
#include <regex>
#include <string>
#include <utility>
#include <vector>

#define test false

#include <iostream>
#include <fstream>




int det(int x1 , int x2, int y1, int y2) {
    return x1 * y2 - x2 * y1;
}


bool brute_force(std::pair<int, int> x, std::pair<int, int> y, std::pair<int, int> price, int x_times, int y_times) {
    int x_coor = x.first * x_times + y.first * y_times;
    int y_coor = x.second * x_times + y.second * y_times;
    return std::make_pair(x_coor, y_coor) == price;
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

    std::istreambuf_iterator<char> eos;
    std::string input (std::istreambuf_iterator<char>(file), eos);
    file.close();

    std::vector<std::pair<int, int>> buttons; // Button A, B, Destination
    std::vector<std::pair<int, int>> price; // Button A, B, Destination
    std::regex regex_buttons("Button [AB]: X\\+(\\d+), Y\\+(\\d+)");
    std::regex regex_prize("Prize: X=(\\d+), Y=(\\d+)");

    auto buttons_iterator = std::sregex_iterator(input.begin(), input.end(), regex_buttons);
    auto price_iterator = std::sregex_iterator(input.begin(), input.end(), regex_prize);
    auto end = std::sregex_iterator();

    for (auto j = buttons_iterator; j != end; j++) {
        std::smatch buttons_matches = *j;
        buttons.push_back(std::make_pair(std::stoi(buttons_matches[1].str()), std::stoi(buttons_matches[2].str())));
        
        //std::cout << buttons_matches.str() << "\n\t" << buttons_matches[1] << "\n\t" << buttons_matches[2].str().data() << "\n";
    }
    for (auto i = price_iterator; i != end; i++) {
        std::smatch price_matches = *i;
        price.push_back(std::make_pair(std::stoi(price_matches[1].str()), std::stoi(price_matches[2].str())));

        //std::cout << price_matches.str() << "\n\t" << price_matches[1] << "\n\t" << price_matches[2] << "\n";
    }

    //std::cout << "\nCalculating\n\n";
    int c = 0;

    for (int p = 0; p < price.size(); p++) {

        std::pair<int, int> &x_p = buttons[p * 2];
        std::pair<int, int> &y_p = buttons[p * 2 + 1];
        std::pair<int, int> &p_p = price[p];


        int d = det(x_p.first, x_p.second, y_p.first, y_p.second);
        //std::cout << "\tDet: " << d << "\n";
        
        int x = det(p_p.first, p_p.second, y_p.first, y_p.second) / d;
        int y = det(x_p.first, x_p.second, p_p.first, p_p.second) / d;

        if (x <= 100 and y <= 100 and x > 0 and y > 0) {
            if (brute_force(x_p, y_p, p_p, x, y)) {
                result += x * 3 + y;
                c++;
            
            }
            else {
                std::cout << 
                    "Price index: " << price[p].first << " " << price[p].first << "\n\t" << 
                    "X: " << buttons[p*2].first << " " << buttons[p*2].second << "\n\t" << 
                    "Y: " << buttons[p*2+1].first << " " << buttons[p*2+1].second << "\n\t" <<
                    "Price: " << price[p].first << " " << price[p].second << "\n";
            }
        }
        

        //std::cout << "\tX: " << x << "\n\tY: " << y << "\n";
        //std::cout << "\n";
    }

    //std::cout << buttons.size() << " " << price.size() << "\n";

    std::cout << "\n" << 
        "Number of stones: "<< result << "\n" <<
        "C: " << c << "\n";
    return 0;
}

// 35897 too high
// 35891 too high


// 80 40
// 38 86



// Bruteforce check failed
// Price index: 8156 8156
//         X: 69 15
//         Y: 15 63
//         Price: 8156 7136
// Price index: 3114 3114
//         X: 59 18
//         Y: 18 44
//         Price: 3114 1340
// Price index: 740 740
//         X: 51 19
//         Y: 12 67
//         Price: 740 1681
// Price index: 5656 5656
//         X: 60 12
//         Y: 22 60
//         Price: 5656 4004
// Price index: 1834 1834
//         X: 80 17
//         Y: 17 79
//         Price: 1834 1342
// Price index: 3144 3144
//         X: 50 11
//         Y: 14 25
//         Price: 3144 968
// Price index: 3912 3912
//         X: 58 14
//         Y: 18 64
//         Price: 3912 2686
// Price index: 6896 6896
//         X: 57 20
//         Y: 24 56
//         Price: 6896 6032
// Price index: 3330 3330
//         X: 26 83
//         Y: 73 15
//         Price: 3330 8173