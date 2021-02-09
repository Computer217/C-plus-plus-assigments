#ifndef ECBINSEARCH_H
#define ECBINSEARCH_H

#include <vector>

// Perform binary search in the (sorted) list listNumbers for the passed in value
// return the position (from 0 to length of listNumbers mius 1; return -1 if not found 
int ECBinarySearch(const std::vector<int> &listNumbers, int value);

#endif  // ECBINSEARCH_H
