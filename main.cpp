#include <iostream>
#include <iterator>
#include <fstream>

std::string get_logo() {
    std::cout << "START" << std::endl;
    std::string filename = "ascii_logo.txt";
    std::string logo;
    std::ifstream ifs{filename.c_str()};
    std::getline(ifs, logo, '\0');
    std::cout << logo << std::endl;
    return logo;
}

int main(int args, const char **argv) {

}
