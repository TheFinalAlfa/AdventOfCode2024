#include <cstddef>
#include <cstdlib>
#include <vector>
#include <stack>


#define test true

#include <iostream> 
#include <fstream>

struct Blocks {
    static int id_last;
    int id;
    int count;
    static std::stack<Blocks> block_stack;
    Blocks(int count_):
        id(id_last),
        count(count_) 
        {
            ++id_last;
        }
    Blocks(int count_, int id_) :
        id(id_),
        count(count_) 
        {}
};

int Blocks::id_last = 0;
std::stack<Blocks> Blocks::block_stack = std::stack<Blocks>();


int main () 
{
    std::ifstream file;
    long long result = 0;
    if (test) {
        file.open("test.txt", std::ios::in);
    } else {
        file.open("input.txt", std::ios::in);
    }
    bool free_space = false;
    std::vector<int> file_sytem;
    char input;
    while (!file.eof() and file.peek() != -1) {
        file.get(input);
        int count = std::atoi(&input);
        if (not free_space) {
            Blocks block(count);
            Blocks::block_stack.push(block);
            for (int i = 0; i < block.count; i++) {
                file_sytem.push_back(block.id);
            }
            free_space = true;
        }
        else {
            for (int i = 0; i <  count; ++i) {
                file_sytem.push_back(-1);
            }
            free_space = false;
        }
    }
    file.close();

    
    std::cout << "\nFileSys size: "<< file_sytem.size() << "\n";
    std::cout << "Moving blocks\n";

    auto front = file_sytem.begin();
    auto end = file_sytem.end();
    end--;
    while (true) {
        if (*front != -1) {
            front++;
        }
        else if (*end < 0) {
            end--;
        }
        else {
            *front = *end;
            *end = -1;
            //std::cout << *front << *end << "\n";
        }
        if (front == end) {
            break;
        }
    }
        //std::cout << "\nFileSys size: "<< file_sytem.size() << "\n";

    size_t position = 0;
    front = file_sytem.begin();
    while (front != file_sytem.end()) {
        if (*front == -1) {
            //std::cout << '.';
        }
        else {
            result += *front * position;
            //std::cout << result << " " << *front << " " << position << "\n";
        }
        position++;
        front++;
        //std::cout << " ";
    }

    
    std::cout << "\n" << 
        "File System size: " << file_sytem.size() << "\n" <<
        "Result of correct ones: "<< result << "\n";
    return 0;
}