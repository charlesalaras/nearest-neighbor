#ifndef __UTILITY_H__
#define __UTILITY_H__
#include <unordered_set>
#include "point.h"

// 
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
