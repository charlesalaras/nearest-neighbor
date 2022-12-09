#ifndef __POINT_H__
#define __POINT_H__
#include <unordered_set>
#include <cmath>
#include <vector>
#include <iostream>

// Stores the necessary classification and features of a data point.
// Also provides a helper function to calculate distance from this and Point b, using distance of features in set.
struct Point {
    int classification;
    std::vector<double> features;
    // Calculate Euclidean distance in an n-dimensional space using features listed in feature set.
    double distance(const Point* b, std::unordered_set<unsigned int> featureSet) const {
        double dist = 0;
        for(auto it: featureSet) {
            double currentSquare = b->features[it] - features[it];
            dist += (currentSquare * currentSquare);
        }
        return std::sqrt(dist);
    }
};

#endif // __POINT_H__
