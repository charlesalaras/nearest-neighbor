#include <cstdio>
#include "utility.h"

extern unsigned int NUM_FEATURES;

double crossValidation(std::vector<Point*> dataset, std::vector<unsigned int> currentSet, unsigned int featureToAdd) {
    int i = 0;
    for(auto object: dataset) {
        Point* removedObject = object;
        printf("Looping over i, at the %d location\n", i);
        printf("The %dth object is in class %d\n", i, object->classification);
        int k = 0;
        for(auto comparison: dataset) {
            if(object != comparison) {
                printf("Ask if %d is nearest neighbor with %d", i, k);
            }
            k++;
        }
        i++;
    }
    return 1.0;
}

std::unordered_set<unsigned int> featureSearch(std::vector<Point*> data, bool direction) {
    std::unordered_set<unsigned int> featureSet = {};
    if(direction) {
        for(unsigned int i = 0; i < NUM_FEATURES; i++) {
            featureSet.insert(i);
        }
    };
    for(unsigned int i = 0; i < NUM_FEATURES; i++) {
        printf("On the %dth level of the search tree\n", i);
        for(unsigned int k = 0; k < NUM_FEATURES; k++) {
            printf("\tConsidering adding the %d feature\n", k);
        }
    }
    return featureSet;
}
