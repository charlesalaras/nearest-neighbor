#include <iostream>
#include <fstream>

int main() {
    std::cout << "Welcome to Charles Alaras' Feature Selection Algorithm." << std::endl;
    std::cout << "Type in the name of the file to test : ";
    std::string fname;
    std::cin >> fname;

    std::ifstream fin;
    fin.open(fname);
    if(!fin.is_open()) {
        std::cerr << "ERROR: Could not open file: " << fname << std::endl;
    }
    if(fin.is_open()) {
        fin.close();
    }
    return 0;
}
