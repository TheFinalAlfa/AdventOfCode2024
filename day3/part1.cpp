#include <iostream> 
#include <iterator>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>


int main () 
{
    std::ifstream file;
    file.open("input.txt", std::ios::in);
    std::istreambuf_iterator<char> eos;
    std::string input (std::istreambuf_iterator<char>(file),eos);
    file.close();

    int result = 0;
    int number_matches = 0;
    bool do_enabled = true;

    std::regex dos_donts ("don't|do");
    std::regex simple_mul ("mul\\((\\d+),(\\d+)\\)");

    auto i_dos_donts = std::sregex_iterator(input.begin(), 
                    input.end(), dos_donts);
    auto simple_mulie = std::sregex_iterator(input.begin(),
        input.end(), simple_mul);
    auto end = std::sregex_iterator();

    auto mark = input.begin();

    for (std::sregex_iterator j = i_dos_donts; j != end; ++j) {
        std::smatch enabler = *j;
        std::cout << "DOs mark\n";
        //enabler.position()
        if (do_enabled) {
            for (std::sregex_iterator i = std::sregex_iterator(mark, input.begin() + enabler.position(),
                simple_mul); i != end; ++i) {
                std::smatch match = *i;
                std::stringstream matches;
                matches << match[1] << " " << match[2];
                int y, x;
                matches >> x >> y;
                result += x * y;
                ++number_matches;
            }
        }
        if (enabler[0] == "do") {
            do_enabled = true;
        }
        else {
            do_enabled = false;
        }
        mark = input.begin() + enabler.position();
    }
    if (do_enabled) {
        for (std::sregex_iterator i = std::sregex_iterator(mark, input.end(),
            simple_mul); i != end; ++i) {
            std::smatch match = *i;
            std::stringstream matches;
            matches << match[1] << " " << match[2];
            int y, x;
            matches >> x >> y;
            result += x * y;
            ++number_matches;
        }
    }


    std::cout << "Number of matches: "<< number_matches << "\nResult: " << result << "\n";

    return 0;
}