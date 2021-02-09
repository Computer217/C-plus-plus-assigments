#include <vector>
#include <iostream>

using namespace std;

int main(){
	vector<int> listNumbers;
	int value = 31;
	listNumbers.push_back(1);
	listNumbers.push_back(2);
	listNumbers.push_back(3);
	listNumbers.push_back(5);
	listNumbers.push_back(6);
	listNumbers.push_back(10);
	listNumbers.push_back(20);
	listNumbers.push_back(30);
	listNumbers.push_back(50);
	listNumbers.push_back(51);
	  //pointer to the middle of the vector
  int index = listNumbers.size()/2;
  int begin_index = 0;
  int end_index = listNumbers.size();

  //performing integer division will resut in zero when there is 1 element left 
  while(end_index-begin_index != 1){
	  cout << index << endl;
	  cout << end_index-begin_index << endl;
	  if (listNumbers[index] == value){
		  cout<<"value found"<<endl;
		  cout<< listNumbers[index] <<endl;
		  return index;
	  }

    //if the pivot is less than target
    else if (listNumbers[index] < value){
      begin_index = index;
      index = begin_index + (end_index - begin_index)/2;
    }
    //if the pivot is greater than the target
    else {
      end_index = index;
      index = begin_index +(end_index - begin_index)/2;
    }

  }

  cout<<"value not found" <<endl;

  return -1;
}
