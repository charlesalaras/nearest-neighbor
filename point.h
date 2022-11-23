#ifndef __POINT_H__
#define __POINT_H__
#include <unordered_set>
#include <cmath>
#include <vector>

struct Point {
    int classification;
    std::vector<double> features;
    // Calculate Euclidean distance in an n-dimensional space
    double distance(const Point& b, std::unordered_set<unsigned int> featureSet) {
        double dist = 0;
        for(auto it: featureSet) {
            double currentSquare = std::fabs(b.features[it] - features[it]);
            dist += (currentSquare * currentSquare);
        }
        return std::sqrt(dist);
    }
};

#endif // __POINT_H__
