#ifndef __UTILITY_H__
#define __UTILITY_H__
#include <unordered_set>
#include "point.h"

// Uses k fold cross validation (k = 1) to find the accuracy of adding featureToAdd
// to the currentSet. The function loops over each point in the dataset, and calculates
// the nearest neighbor to it (Euclidean distance for distance to every feature axis)
// If the calculated nearest neighbor given the feature set has the same class, it is a correct classification
// We take a percentage of correctly identified data points divided by the size of the dataset.
double crossValidation(
        const std::vector<Point*>& dataset, 
        const std::unordered_set<unsigned int>& currentSet, 
        const unsigned int& featureToAdd
        );

// Iterates through all feature sets, expanding the set with the most promising accuracy.
// If forward (direction == false), we start with the empty set.
// Else, we start with the most complete set (every feature in the set).
std::unordered_set<unsigned int> featureSearch(const std::vector<Point*>& data, bool direction);

#endif // __UTILITY_H__
