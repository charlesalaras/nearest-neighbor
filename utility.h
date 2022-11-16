#ifndef __UTILITY_H__
#define __UTILITY_H__
#include "point.h"

// Given a newPoint, the algorithm iterates through every existing point comparing features.
// For each feature, we calculate distance between the two points, and store the point with lowest minimum.
// At the end of iteration, we observe the closest point's class, and set it / return as the newPoint's class.
int nearestNeighbor(std::vector<Point*> dataset, Point* newPoint);

std::vector<unsigned int> forwardSelection();

std::vector<unsigned int> backwardElimination();

#endif // __UTILITY_H__
