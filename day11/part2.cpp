#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define test true
#define blinks 25

#include <iostream>
#include <fstream>


std::unordered_multiset<long> equation(long value) {
    if (value == 0) {
        return std::unordered_multiset<long>{1};
    }
    else if (std::to_string(value).size() % 2 == 0) {
        std::string v_in_s = std::to_string(value);
        v_in_s.insert(v_in_s.size() / 2, " ");
        long first, second;
        std::stringstream stream (v_in_s);
        stream >> first >> second;
        return std::unordered_multiset<long>{first, second};
    }
    else {
        return std::unordered_multiset<long>{value * 2024};
    }
}


class PrimaryStones {
    private:
    long stone;
    std::vector<long> multitude;
    std::unordered_multiset<PrimaryStones *> end;

    public:
    static std::unordered_map<long, PrimaryStones *> solutions;

    void finish() {
        std::unordered_multiset<long> progress {stone};
        std::cout << "Finish on stone " << stone << "\n";
        do {
            std::unordered_multiset<long> temp_progress{};
            std::cout << "\tValue ";
            for (long value : progress) {
                std::cout << value << " ";
                temp_progress.merge(equation(value));
            }
            std::cout << "\n";
            progress = temp_progress;
            multitude.push_back(progress.size() - 1);
        }
        while (not (*progress.begin() <= 9));

        std::cout << "\tEndpoints size " << progress.size() << "\n";
        for (long endpoint : progress) {
            end.insert(solutions[endpoint]);
        } 
    }

    long calculate_new_stones(long depth) {
        std::cout << "Calculating stone: " << stone << " ends " << end.size() << "\n";
        if (depth < multitude.size()) {
            return multitude[depth];
        }
        else {
            long result = multitude.back();
            depth -= multitude.size() - 1;
            for (PrimaryStones * next : end) {
                result += next->calculate_new_stones(depth);
            }
            return result;
        }
    }

    PrimaryStones(const PrimaryStones &) = default;
    PrimaryStones(PrimaryStones &&) = default;
    PrimaryStones &operator=(const PrimaryStones &) = default;
    PrimaryStones &operator=(PrimaryStones &&) = default;

    PrimaryStones(long initial_stone) : stone(initial_stone) {}
};

std::unordered_map<long, PrimaryStones *> PrimaryStones::solutions {};


long calculate(std::unordered_multiset<long> & initial_stone) {
    long output = 0;
    for (int i = 0; i < blinks; i++) {
        std::unordered_multiset<long> result{};
        std::cout << "Blinks: " << i << "\n";
        for (long key : initial_stone) {
            std::cout << "Key: " << key << "\n";
            if (PrimaryStones::solutions.contains(key)) {
                output += PrimaryStones::solutions[key]->calculate_new_stones(blinks - i - 1);
            }
            else {
                result.merge(equation(key));
            }
        }
        initial_stone = result;
    }
    return output + initial_stone.size();
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

    std::unordered_multiset<long> initial{};
    long stone;
    while (!file.eof()) {
        file >> stone;
        initial.insert(stone);
        std::cout << "Initial stone: " << stone << "\n";
    }
    file.close();

    PrimaryStones * temp;
    for (long i = 0; i < 10; i++) {
        if (i == 8) i++;
        temp = new PrimaryStones(i);
        PrimaryStones::solutions[i] = temp;
    }
    for (long i = 0; i < 10; i++) {
        if (i == 8) i++;
        PrimaryStones::solutions[i]->finish();
    }
    std::cout << 
        "Initial size: " << initial.size() << "\n" <<
        "Primary Solutions size: " << PrimaryStones::solutions.size() << 
        "\n";

    result = calculate(initial);

    std::cout << "\n" << 
        "Number of stones: "<< result << "\n";
    return 0;
}