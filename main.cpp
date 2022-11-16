#include <iostream>
#include <sstream>
#include <fstream>
#include "point.h"

void readFile(std::string file) {
    std::ifstream fin;
    fin.open(file);
    if(!fin.is_open()) {
        std::cerr << "ERROR: Could not open file: " << file << std::endl;
    }
    std::stringstream ss;
    int numPoints = 0;
    int numFeatures = 0;
    while(!fin.eof()) {
        numPoints++;
        std::string curr;
        getline(fin, curr);
        ss.str(curr);

        double currInput;
        unsigned int i = 0;
        while(ss >> currInput) {
            Point* currPoint = new Point;
            if(i == 0) currPoint->classification = currInput;
            else currPoint->features.push_back(currInput);
            i++;
        }
        numFeatures = std::max(int(i), numFeatures);
        ss.clear();
    }
    if(fin.is_open()) {
        fin.close();
    }
    std::cout << "Processed " << numPoints << " points each with " << numFeatures - 1 << " features." << std::endl;
}

int main() {
    std::cout << "Welcome to Charles Alaras' Feature Selection Algorithm." << std::endl;
    std::cout << "Type in the name of the file to test : ";
    std::string fname;
    std::cin >> fname;

    readFile(fname);
    return 0;
}
