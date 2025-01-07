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



std::bitset<64> starting_number;
std::unordered_map<std::string, Gate> gates;


int main () 
{
    starting_number.reset();

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
            //std::cout << gates[name3].second_operand->get_value() << "\n";
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

    std::string name_prefix = "z";
    std::string name_num, name;
    for (int i = 0;; i++) {
        name_num = std::to_string(i);
        name = name_prefix;
        if (i < 10) {
            name.append("0");
        }
        name.append(name_num);
        std::cout << name << "\n";
        if (gates.contains(name)) {
            starting_number[i] = gates[name].get_value();
        }
        else {
            break;
        }
    }

    result = starting_number.to_ullong();

    std::cout << "\n";
    std::cout << "Check!\n";

    std::cout << "\n" << 
        "Results: "<< result << "\n";
    return 0;
}