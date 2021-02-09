#ifndef EC2SUM_H
#define EC2SUM_H

#include <vector>

// EC2SUM: decide whether each number in listTargets is a sum of two numbers (duplicates allowed) in
// listNumbers. Store True/False in list2SUMRes for each target number 
void EC2SUM( const std::vector<int> &listNumbers, const std::vector<int> &listTargets, std::vector<bool> &list2SUMRes );

#endif  // EC2SUM_H
