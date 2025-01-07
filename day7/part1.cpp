#include <bitset>
#include <cstdlib>
#include <iostream> 
#include <fstream>
#include <sstream>
#include <vector>

// Too low
//      257 
//      266
// 
// 10779029898
// 10779030122
// 2299996598890 -- correct

class Line {
    private:
    const int answer_;
    std::vector<int> factors_;
    std::bitset<32> multiply;

    int anwser() {
        int result = factors_[0];
        for (int i = 1; i < factors_.size(); ++i) {
            if (multiply[i - 1]) {
                result *= factors_[i];
            }
            else {
                result += factors_[i];
            }
        }
        return result;
    }


    bool recluse_calculation(int total, int pos_factor) {
        int multi = total * factors_[pos_factor];
        int addi = total + factors_[pos_factor];
        if (pos_factor + 1 == factors_.size()) {
            return multi == answer_ or addi == answer_;
        }
        else {
            if (//multi < answer_ and 
                    recluse_calculation(multi, pos_factor + 1)) {
                return true;
                }
            else if (//addi < answer_ and 
                recluse_calculation(addi, pos_factor + 1)) {
                return true;
            } 
            return false;
        }
    }


    public:
    Line(int answer) : answer_(answer) {}
    
    void add_factor(int f) { factors_.push_back(f); }

    int calculate() {
        std::cout << answer_ << "\n";
        if (recluse_calculation(factors_[0], 1)) {
            return answer_;
        }
        else {
            return 0;
        }
    }
};


int main () 
{
    std::ifstream file;
    long long result = 0;
    int line_counter = 0;
    file.open("test.txt", std::ios::in);
    //file.open("input.txt", std::ios::in);

    while (!file.eof()) {
        ++line_counter;
        std::vector<int> equation;
        char input[64];
        file.getline(input, 64, ':');
        Line line (std::atoi(input));
        char factors[1024];
        file.getline(factors, 1024, '\n');
        std::stringstream factors_stream (factors);
        int factor;
        while (!factors_stream.eof()) {
            factors_stream >> factor;
            line.add_factor(factor);
        }
        //std::cout << "Line: " << line_counter << "";
        int calc = line.calculate();
        if (calc != 0) {
            std::cout << result << "\n";
            result += calc;
        }
        else {
            //std::cout << " Impossible\n";
        }
    }


    file.close();

    std::cout << 
        "Number of lines: "<< line_counter << "\n"
        "Result of correct ones: "<< result << "\n";

    return 0;
}