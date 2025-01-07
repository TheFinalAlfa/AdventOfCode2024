#include <cstddef>
#include <cstdlib>
#include <iterator>
#include <list>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>


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
    while (front != file_sytem.end()) {
        if (*front == -1) {
            std::cout << '.';
        }
        else {
            std::cout << *front;
        }
        front++;
    }
    std::cout << "\n";


    auto front_seek = front;
    auto end = file_sytem.rbegin();
    auto end_seek = end;
    std::unordered_set<int> moved;
    int file_size, opening, target_id;
    while (end != file_sytem.rend()) {
        if (*end < 0 or  moved.contains(*end)) {
            end++;
        }
        else {
            file_size = 0;
            end_seek = end;
            while (*end_seek == *end and end_seek != file_sytem.rend()) {
                file_size++;
                end_seek++;
            }
            std::cout << "Dealing with " << *end << " size " << file_size << "\n";
            front = file_sytem.begin();
            target_id = *end;
            while (front != file_sytem.end()) {
                opening = 0;
                while (*front != -1 and front != file_sytem.end()) {
                    front++;
                }
                if (std::distance(front, file_sytem.begin()) > std::distance(end_seek, file_sytem.rend()) - 1) {
                    break;
                }
                front_seek = front;
                while (front_seek != file_sytem.end() and *front_seek < 0) {
                    front_seek++;
                    opening++;
                }
                std::cout << *front << " " << 
                    *front_seek << " " << 
                    opening << "\n";
                if (opening >= file_size) {
                    std::cout << "Found " << opening << "\n";
                    for (int i = 0; i < file_size; i++) {
                        *front = *end;
                        *end = -1;
                        front++;
                        end++;
                    }
                    break;
                }
                else if (front == file_sytem.begin()) {
                    break;
                }
                else front = front_seek;
            }
            moved.insert(target_id);
        }
    }
    std::cout << "\nFileSys size: "<< file_sytem.size() << "\n";

    size_t position = 0;
    front = file_sytem.begin();
    while (front != file_sytem.end()) {
        if (*front == -1) {
            std::cout << '.';
        }
        else {
            result += *front * position;
            std::cout << *front;
        }
        position++;
        front++;
    }

    
    std::cout << "\n" << 
        "File System size: " << file_sytem.size() << "\n" <<
        "Moved size: " << moved.size() << "\n"<<
        "Result of correct ones: "<< result << "\n";
    return 0;
}