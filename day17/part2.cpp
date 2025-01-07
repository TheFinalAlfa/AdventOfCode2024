#include <cmath>
#include <vector>

#define test false

#include <iostream>
#include <fstream>


int registerA;
int registerB;
int registerC;


int combo(int input) {
    if (input < 4) {
        return input;
    }
    else if (input == 4) {
        return registerA;
    }
    else if (input == 5) {
        return registerB;
    }
    else if (input == 6) {
        return registerC;
    }
    else {
        std::cout << "Combo 7 is reserved\n";
        return -1;
    }
}



int instruction_counter = 0;
std::vector<int> instructions;

void bxl(int input) {
    registerB = registerB ^ input;
}

void bst(int input) {
    registerB = combo(input) % 8;
}

void jnz(int input) {
    if (registerA != 0) {
        instruction_counter = input - 2;
    }
}

void bxc(int input) {
    registerB = registerB ^ registerC;
}

int out(int input) {
    return combo(input) % 8;
}

void adv(int input) {
    registerA = registerA / std::pow(2, combo(input));
}

void bdv(int input) {
    registerB = registerA / std::pow(2, combo(input));
}

void cdv(int input) {
    registerC = registerA / std::pow(2, combo(input));
}


int main () 
{
    std::ifstream file;
    long long result = 0;
    if (test) {
        registerA = 729;
        registerB = 0;
        registerC = 0;
        file.open("test.txt", std::ios::in);
    } else {
        registerA = 37283687;
        registerB = 0;
        registerC = 0;
        file.open("input.txt", std::ios::in);
    }

    //std::istreambuf_iterator<char> eos;
    //std::string input (std::istreambuf_iterator<char>(file), eos);


    char read_char;
    int i = 0;
    bool newline = true;


    while (not file.eof() and (not (file.peek() == -1))) {
        file >> i;
        instructions.emplace_back(i);
    }

    file.close();

    std::vector<int> outs;

    for (int count = 1; instructions != outs; i++) {
        registerA = count;
        registerB = 0;
        registerC = 0;
        outs.clear();
        std::cout << i << "\n";
        while (instruction_counter < instructions.size() and instruction_counter >= 0) {
            //std::cout << "Instruction: " << instruction_counter << " " << instructions[instruction_counter] << "\n";
            switch (instructions[instruction_counter]) {
                case 0:
                    adv(instructions[instruction_counter + 1]);
                    break;
                case 1:
                    bxl(instructions[instruction_counter + 1]);
                    break;
                case 2:
                    bst(instructions[instruction_counter + 1]);
                    break;
                case 3:
                    jnz(instructions[instruction_counter + 1]);
                    break;
                case 4:
                    bxc(instructions[instruction_counter + 1]);
                    break;
                case 5:
                    outs.push_back(out(instructions[instruction_counter + 1]));
                    break;
                case 6:
                    bdv(instructions[instruction_counter + 1]);
                    break;
                case 7:
                    cdv(instructions[instruction_counter + 1]);
                    break;
            }
            instruction_counter += 2;
        }
    }

    std::cout << "Outs:\n";
    for (int i : outs) {
        std::cout << i << ",";
    }
    std::cout << "\n";

    std::cout << "\n" << 
        "Results: "<< result << "\n";
    return 0;
}

// 4,6,3,5,6,3,5,2,1,0
// 4,6,3,5,6,3,5,2,1,0