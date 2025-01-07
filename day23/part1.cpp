#include <cstddef>
#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>

#define test false


#include <iostream>
#include <fstream>


struct SpecialHash {
    std::size_t operator() (const std::unordered_set<std::string> value) const {
        std::size_t result = 1;
        for (auto key : value) {
            result = result ^ std::hash<std::string>()(key);
        }
        return result;
    }
};



std::unordered_map<std::string, std::unordered_set<std::string>> computers;
std::unordered_set<std::string> checked;
std::unordered_set<std::unordered_set<std::string>, SpecialHash> triplets;


std::unordered_set<std::string> intersection_sets(
    const std::unordered_set<std::string> &first, 
    const std::unordered_set<std::string> &second
) {
    std::unordered_set<std::string> result{};
    for (auto value : first) {
        if (second.contains(value)) {
            result.insert(value);
        }
    }
    return result;
}



void find_tripplets(std::string input) {
    std::cout << "Tripplets\nInput: " << "\n";
    for (auto connection : computers[input]) {
        std::cout << "\tCon " << connection << " ";
        if (true) {
        //if (not checked.contains(connection)) {
            auto result = intersection_sets(computers[input], computers[connection]);
            std::cout << "Conn size: " << result.size();
            if (result.size() >= 1) {
                std::cout << input << " " << connection << "\n";
                for (auto i : result) {
                    std::cout << "\t" << i << "\n";
                    triplets.insert(std::unordered_set<std::string>{input, connection, i});
                }
            }
        }
        std::cout << "\n";
    }
    checked.insert(input);
    std::cout << 
        "\tChecked size: " << checked.size() <<
        "\n";
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

    std::string read_string;
    std::string first, second;

    while (not file.eof() and (file.peek() != -1)) {
        file >> read_string;
        first = read_string.substr(0, 2);
        second = read_string.substr(3, 2);
        if (not computers.contains(first)) {
            computers[first] = std::unordered_set<std::string>{};
        }
        computers[first].insert(second);
        if (not computers.contains(second)) {
            computers[second] = std::unordered_set<std::string>{};
        }
        computers[second].insert(first);
    }
    file.close();
    std::cout << computers.size() << "\n";

    for (auto key : computers) {
        find_tripplets(key.first);
    }

    std::cout << "R " << computers["co"].contains("ta") << "\n";


    std::cout << "Connections:\n";
    for (auto trip : computers) {
        std::cout << trip.first << ": ";
        for (auto t : trip.second) {
            std::cout << t << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nTriplets:\n";

    for (auto trip : triplets) {
        for (auto t : trip) {
            if (t[0] == 't') {
                result++;
                break;
            }
            //std::cout << t << " ";
        }
        std::cout << "\n";
    }

    std::cout << "Check!\n";
    std::cout << "\n" << 
        "Triplets size: " << triplets.size() << "\n" <<
        "Results: "<< result << "\n";
    return 0;
}


// Test triplets

// co,de,ka
// co,de,ta
// co,ka,ta
// de,ka,ta

// kh,qp,ub
// aq,cg,yn

// aq,wq,vc
// ub,wq,vc
// tb,wq,vc

// qp,td,wh
// td,yn,wh
// tc,td,wh



// ub qp kh 
// yn cg aq 
// wh td tc qp yn 
// qp td wh 
// yn td wh 
// de ka co ta 
// ub wq vc 
// aq wq vc 
// tc td wh 
// tb wq vc 
// vc wq tb ub aq 



// wq: vc aq ub tb 
// td: yn qp wh tc 
// yn: td wh cg aq 
// tc: td co wh kh 
// ka: de ta tb co 
// de: ka ta co cg 
// cg: aq yn tb de 
// aq: wq cg vc yn 
// co: de ta tc ka 
// ta: kh de ka co 
// tb: vc wq ka cg 
// qp: wh td ub kh 
// wh: qp yn td tc 
// kh: ta ub qp tc 
// ub: vc wq kh qp 
// vc: tb wq ub aq 