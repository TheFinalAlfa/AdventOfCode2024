#include <array>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>


// Map<Character, SetWhat'sBefore>
// 5674 too high

int main ()
{
    std::ifstream file;
    file.open("input.txt", std::ios::in);

    bool first_section = true;
    std::array<char, 128> line;

    int middle_pages = 0;

    // Value can't be before Key
    std::pmr::unordered_map<int, std::pmr::unordered_set<int>> map;

    std::vector<int> page;
    std::pmr::unordered_set<int> page_prefix;
    bool manual_correct = true;

    while (!file.eof()) {
        file.getline(line.data(),128);
        if (line[0] == '\0' and not first_section) {
            break;
        }
        if (file.gcount() == 1) {
            std::cout << "Ruleset\n";

            for (auto i = map.begin(); i != map.end(); ++i) {
                std::cout << i->first<< ": ";
                for (auto j : map[i->first]){
                    std::cout << j << " ";
                }
                std::cout << "\n";
            }

            std::cout << "Moving to next section\n\n";
            first_section = false;

        }
        else if (first_section) {
            line[2] = ' ';
            int first, second;
            std::stringstream number((std::string(line.data())));
            number >> first >> second;

            if (!map.contains(second)) {
                map[second] = std::pmr::unordered_set<int>();
            }
            map[second].insert(first);
        }
        else {
            // Line preperation
            // ',' -> ' ', shrani v page
            for (int i = 0; i < line.size(); i++) {
                if (line[i] == ',') {
                    line[i] = ' ';
                }
            }
            page.clear();
            std::istringstream manual(line.data());
            int number;
            while (!manual.eof()) {
                manual >> number;
                page.push_back(number);
            }

            std::cout << "Line: "<< line.data() << "\n";
            page_prefix.clear();
            for (int page_number : page) {
                std::cout << page_number << " after ";
                for (auto c : map[page_number]) {
                    std::cout << c << " ";
                }
                std::cout << "\n";
                for (int prefix : page_prefix) {
                    if (!map[page_number].contains(prefix)) {
                        std::cout << "Didn't pass: " << page_number << " after " << prefix << "\n";
                        manual_correct = false;
                    }
                }
                if (!manual_correct) {
                    break;
                }
                page_prefix.insert(page_number);
            }
            if (manual_correct) {
                std::cout << "Manual correct " << page[(page.size() - 1) / 2] << "\n\n";
                middle_pages += page[(page.size() - 1) / 2];
            } else {
                manual_correct = true;
            }


            //    page.push_back(page_number);
            //{}
            //std::cout << page[0] << "\n";
        }
    }
    file.close();



    std::cout << "Total middle pages: " << middle_pages << "\n";

    return 0;
}
