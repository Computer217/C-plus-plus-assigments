#include <vector>
#include <iostream>
using namespace std;

// Your first C++ program is here...
int ECBinarySearch(const vector<int> &listNumbers, int value)
{
  // input list of numbers comes as listNumbers vector
  // You need to implement binary search of "value" over this list; 
  // return the position (i.e., array index) of the vector that matches "value"; 
  // or return -1 if not found.
  //while from beginer to pointer != 1

  //pointer to the middle of the vector
  int begin_index = 0;
  int end_index = listNumbers.size()-1;
  int index = begin_index + (end_index - begin_index)/2;

  //when there are no more elements left the different of begin and end index will be 1 
  while(end_index >= begin_index){

    if (listNumbers[index] == value){
      return index;
    }

    //if the target greater than pivot
    if (value > listNumbers[index]){
      begin_index = index + 1;
      index = begin_index + (end_index - begin_index)/2;
    }

    //if the pivot is greater than the target
    else {
      end_index = index - 1;
      index = begin_index + (end_index - begin_index)/2;
    }
  }

  return -1; 
}
