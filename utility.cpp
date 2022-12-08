#include <cstdio>
#include <iomanip>
#include <limits>
#include "utility.h"

extern unsigned int NUM_FEATURES;

double crossValidation(
        const std::vector<Point*>& dataset, 
        const std::unordered_set<unsigned int>& currentSet, 
        const int& feature,
        bool direction
        ) {
    // FOR DEBUG - COMMENT WHEN DONE
    // return double(rand()) / double(RAND_MAX);
    //
    unsigned int correctClassifications = 0;
    std::unordered_set<unsigned int> testFeatureSet = currentSet;

    if(feature >= 0) {
        if(!direction) testFeatureSet.insert(feature);
        else testFeatureSet.erase(feature);
    }
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
    std::cout << "Running nearest neighbor with all " << NUM_FEATURES << " features, using \"leaving-one-out\" evaluation, I get an accuracy of " << std::fixed << std::setprecision(1) << crossValidation(data, featureSet, -1, direction) * 100 << "%\n" << std::endl;

    unsigned int observedFeature;
    double bestAccuracy = 0;
    std::unordered_set<unsigned int> bestFeatureSet;
    for(unsigned int i = 0; i < NUM_FEATURES; i++) {
        printf("On the %dth level of the search tree\n", i);
        double bestLevelAccuracy = 0;
        for(unsigned int k = 0; k < NUM_FEATURES; k++) {
            if(featureSet.find(k) != featureSet.end() && !direction) continue;
            if(featureSet.find(k) == featureSet.end() && direction) continue;

            double accuracy = crossValidation(data, featureSet, k, direction);
            std::cout << "\tUsing feature(s) ";

            if(!direction) std::cout << print(featureSet, k + 1);
            else std::cout << printErased(featureSet, k + 1);

            std::cout << " accuracy is " << std::fixed << std::setprecision(1) << accuracy * 100 << "%" << std::endl;
            
            if(accuracy > bestLevelAccuracy) {
                bestLevelAccuracy = accuracy;
                observedFeature = k;
            }
        }

        if(!direction) featureSet.insert(observedFeature);
        else featureSet.erase(observedFeature);

        std::cout << "Feature set " << print(featureSet) << " was best, with accuracy " << std::fixed << std::setprecision(1) << bestLevelAccuracy * 100 << "%" << std::endl;
        if(bestLevelAccuracy >= bestAccuracy) {
            bestAccuracy = bestLevelAccuracy;
            bestFeatureSet = featureSet;
        }
    }
    return {bestAccuracy, bestFeatureSet};
}

// Auxiliary print functions
const std::string print(const std::unordered_set<unsigned int> set) {
    std::string featureSet = "{";
    for(auto it: set) featureSet += std::to_string(it + 1) + ", ";
    if (set.size() != 0) {
        featureSet.pop_back();
        featureSet.pop_back();
    }
    featureSet += "}";
    return featureSet;
}

const std::string print(const std::unordered_set<unsigned int> set, unsigned int end) {
    std::string featureSet = "{";
    for(auto it: set) featureSet += std::to_string(it + 1) + ", ";
    featureSet += std::to_string(end);
    featureSet += "}";
    return featureSet;
}

const std::string printErased(const std::unordered_set<unsigned int> set, unsigned int k) {
    std::string featureSet = "{";
    for(auto it: set) {
        if(it == k - 1) continue;
        featureSet += std::to_string(it + 1) + ", ";
    }
    if (featureSet.size() > 1) {
        featureSet.pop_back();
        featureSet.pop_back();
    }
    featureSet += "}";
    return featureSet;
}
