#include <cstdio>
#include "utility.h"

extern unsigned int NUM_FEATURES;

double crossValidation(
        const std::vector<Point*>& dataset, 
        const std::unordered_set<unsigned int>& currentSet, 
        const unsigned int& featureToAdd
        ) {
    // FOR DEBUG - COMMENT WHEN DONE
    return double(rand()) / double(RAND_MAX);
    /////
    int i = 0;
    for(auto object: dataset) {
        Point* removedObject = object;
        printf("Looping over i, at the %d location\n", i);
        printf("The %dth object is in class %d\n", i, object->classification);
        int k = 0;
        for(auto comparison: dataset) {
            if(object != comparison) {
                printf("Ask if %d is nearest neighbor with %d\n", i, k);
            }
            k++;
        }
        i++;
    }
    return 1.0;
}

std::unordered_set<unsigned int> featureSearch(const std::vector<Point*>& data, bool direction) {
    std::unordered_set<unsigned int> featureSet = {};
    if(direction) {
        for(unsigned int i = 0; i < NUM_FEATURES; i++) featureSet.insert(i);
    };
    for(unsigned int i = 0; i < NUM_FEATURES; i++) {
        printf("On the %dth level of the search tree\n", i);
        for(unsigned int k = 0; k < NUM_FEATURES; k++) {
            printf("\tConsidering adding the %d feature\n", k);
            double accuracy = crossValidation(data, featureSet, k);
        }
    }
    return featureSet;
}
