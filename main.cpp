#include <iostream>
#include <fstream>

void get_logo() {
    using namespace std;
    string line;
    ifstream logo_file("../resources/ascii_logo.txt"); //TODO: change to config file
    if (logo_file.is_open()) {
        while (getline(logo_file, line)) {
            cout << line << '\n';
        }
        logo_file.close();
    }
}

int main(int args, const char **argv) {
    get_logo();
    return 0;
}
