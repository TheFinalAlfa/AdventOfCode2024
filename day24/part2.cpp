#include <bitset>
#include <string>
#include <unordered_map>

#define test false


#include <iostream>
#include <fstream>


class Gate {
    public:

    std::string name;
    bool value_set = false;
    bool value;
    Gate * first_operand;
    Gate * second_operand;
    bool (*function)(bool, bool);

    bool get_value() {
        if (not value_set) {
            if (first_operand == nullptr or second_operand == nullptr) {
                throw "Gate first or second operand is nullptr\n";
            }
            value = function(first_operand->get_value(), second_operand->get_value());
        }
        return value;
    };
    Gate() {}
    Gate(std::string name_): name(name_), first_operand(nullptr), second_operand(nullptr), function(nullptr) {}
};


std::unordered_map<std::string, Gate> gates;


long long read_from_gates(std::string name_prefix) {
    std::bitset<64> starting_number;
    starting_number.reset();
    std::string name_num, name;
    std::cout << "Number prefix: ";
    for (int i = 0;; i++) {
        name_num = std::to_string(i);
        name = name_prefix;
        if (i < 10) {
            name.append("0");
        }
        name.append(name_num);
        if (gates.contains(name)) {
            starting_number[i] = gates[name].get_value();
            std::cout << gates[name].get_value();
        }
        else {
            break;
        }
    }
    std::cout << "\n";
    return starting_number.to_ullong();
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

    char read_char;
    int i = 0;
    std::string name1, name2, operation, name3;

    while (not file.eof() and (file.peek() != -1)) {
        file >> name1 >> operation;
        if (name1.size() != 3) {
            name1 = name1.substr(0, 3);
            gates[name1] = Gate(name1);
            if (operation == "0") {
                gates[name1].value = false;
            }
            else {
                gates[name1].value = true;
            }
            gates[name1].value_set = true;
        }
        else {
            file >> name2 >> name3 >> name3;
            std::cout << name1 << " " << name2 << " " << name3 << " " << operation << "\n";
            if (not gates.contains(name3)) {
                gates[name3] = Gate(name3);
            }
            if (not gates.contains(name2)) {
                gates[name2] = Gate(name2);
            }
            if (not gates.contains(name3)) {
                gates[name3] = Gate(name3);
            }
            gates[name3].first_operand = &gates[name1];
            gates[name3].second_operand = &gates[name2];
            if (operation == "AND") {
                gates[name3].function = [](bool i, bool j) -> bool {return i & j;};
            }
            else if (operation == "OR") {
                gates[name3].function = [](bool i, bool j) -> bool {return i | j;};
            }
            else if (operation == "XOR") {
                gates[name3].function = [](bool i, bool j) -> bool {return i ^ j;};
            }
        }
    }
    file.close();
    std::cout << "Gates nize: " << gates.size() << "\n";


    std::cout << "number X: " << read_from_gates("x") << "\n" << 
        "Number Y: " << read_from_gates("y") << "\n";
    

    result = read_from_gates("z");

    std::cout << "\n";
    std::cout << "Check!\n";

    std::cout << "\n" << 
        "Results: "<< result << "\n";
    return 0;
}



// 23538241273549
// 29926666651673
// 53464907925222

// 101100110111111001000001001101100001011010101
// 100110000001001110101010000110111110110011011
// 00000000000000001000000000000001000001
// 0123456789012345678901234567890123456789012345
// 0110011101100010111010110010001111111110000011

// Razlika med pravilnim odgovorom in napačnim
// 139586502656
// 10000010000000000000010000000000000000


// 10110
// 11111

// sus gates
// 
// z16
// z31
// z37

// https://www.101computing.net/binary-additions-using-logic-gates/