#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include "utility.h"
#include "point.h"

unsigned int NUM_FEATURES = 0;
std::vector<Point*> dataset;

void readFile(std::string file) {
    std::ifstream fin;
    fin.open(file);
    if(!fin.is_open()) {
        throw std::invalid_argument("ERROR: Could not open specified file: " + file);
    }
    std::stringstream ss;
    int numPoints = 0;
    while(!fin.eof()) {
        numPoints++;
        std::string curr;
        getline(fin, curr);
        ss.str(curr);
        double currInput;
        unsigned int i = 0;
        Point* currPoint = new Point;
        while(ss >> currInput) {
            if(i == 0) currPoint->classification = currInput;
            else currPoint->features.push_back(currInput);
            i++;
        }
        ss.clear();
        std::cout << "Object: " << dataset.size() << ": " << currPoint->classification << std::endl;
        dataset.push_back(currPoint);
        fin.peek();
    } 
    if(fin.is_open()) {
        fin.close();
    }
    if(!dataset.empty()) NUM_FEATURES = dataset[0]->features.size();
    //std::cout << "Processed " << numPoints << " points each with " << NUM_FEATURES << " features." << std::endl;
}

int main() {
    std::cout << "Welcome to Charles Alaras' Feature Selection Algorithm." << std::endl;
    std::cout << "Type in the name of the file to test : ";
    std::string fname;
    std::cin >> fname;

    try
    {
        readFile(fname);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 0;
    }
    //featureSearch(dataset, false);
    crossValidation(dataset, {}, 0);
    return 0;
}
