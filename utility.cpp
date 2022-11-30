#include <cstdio>
#include <limits>
#include "utility.h"

extern unsigned int NUM_FEATURES;

double crossValidation(
        const std::vector<Point*>& dataset, 
        const std::unordered_set<unsigned int>& currentSet, 
        const unsigned int& featureToAdd,
        bool direction
        ) {
    // FOR DEBUG - COMMENT WHEN DONE
    // return double(rand()) / double(RAND_MAX);
    //
    unsigned int correctClassifications = 0;
    std::unordered_set<unsigned int> testFeatureSet = currentSet;
    testFeatureSet.insert(featureToAdd);
    for(unsigned int i = 0; i < dataset.size(); i++) {
        //printf("Looping over i, at the %d location\n", i);
        //printf("The %dth object is in class %d\n", i, dataset[i]->classification);
        double nearestNeighborDist = std::numeric_limits<double>::max();
        int nearestNeighborClass = std::numeric_limits<int>::max();
        for(unsigned int j = 0; j < dataset.size(); j++) {
            if(dataset[i] != dataset[j]) {
                //printf("Ask if %d is nearest neighbor with %d\n", i, j);
                double currDist = dataset[i]->distance(dataset[j], testFeatureSet);
                if(currDist < nearestNeighborDist) {
                    nearestNeighborDist = currDist;
                    nearestNeighborClass = dataset[j]->classification;
                }
            }
        }
        if(nearestNeighborClass == dataset[i]->classification) correctClassifications++;
    }
    return double(correctClassifications) / double(dataset.size());
}
// FIXME: DO BACKWARD ELIMINATION TOO
std::pair<double, std::unordered_set<unsigned int>> featureSearch(const std::vector<Point*>& data, bool direction) {
    std::unordered_set<unsigned int> featureSet = {};
    if(direction) {
        for(unsigned int i = 0; i < NUM_FEATURES; i++) featureSet.insert(i);
    };
    unsigned int addedFeature;
    double bestAccuracy = 0;
    std::unordered_set<unsigned int> bestFeatureSet;
    for(unsigned int i = 0; i < NUM_FEATURES; i++) {
        printf("On the %dth level of the search tree\n", i);
        double bestLevelAccuracy = 0;
        for(unsigned int k = 0; k < NUM_FEATURES; k++) {
            if(featureSet.find(k) != featureSet.end()) continue;
            double accuracy = crossValidation(data, featureSet, k, direction);
            printf("\tConsidering adding the %d feature with accuracy %f\n", k, accuracy);
            if(accuracy > bestLevelAccuracy) {
                bestLevelAccuracy = accuracy;
                addedFeature = k;
            }
        }
        featureSet.insert(addedFeature);
        printf("Adding feature %d with accuracy %f\n", addedFeature, bestLevelAccuracy);
        if(bestLevelAccuracy > bestAccuracy) {
            std::cout << "Adding feature " << addedFeature << " gave a better accuracy of " << bestLevelAccuracy << std::endl;
            bestAccuracy = bestLevelAccuracy;
            bestFeatureSet = featureSet;
        }
    }
    return {bestAccuracy, bestFeatureSet};
}
