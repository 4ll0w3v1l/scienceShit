#include <iostream>
#include <fstream>

void read_file(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
