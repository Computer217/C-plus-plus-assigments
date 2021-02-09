#include "EC2SUM.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream> 
#include <string>
using namespace std;

// File I/O
static void ReadIntsFromFile(const char *filename, vector<int> &listNumbers)
{
  // Your code here
  ifstream file(filename);

  int x;

  if (file.is_open()){ 
    while (file >> x){
      listNumbers.push_back(x);
    }
  }

  file.close();
}

// main function
int main( int argc, const char* argv[] )
{
  // 
  if( argc != 3 )
  {
    // Usage: ./2SUM <number-file> <target-file>
    cout << "Error.  Usage:  ./2SUM <number-file> <target-file> \n";
    exit(1);  
  }

  // read in integers from the first file
  vector<int> listNumbers;
  ReadIntsFromFile( argv[1], listNumbers );

  // read in integers from the seconf file
  vector<int> listTargets;
  ReadIntsFromFile( argv[2], listTargets );

  // 
  vector<bool> listResults;
  EC2SUM(listNumbers, listTargets, listResults);

  // dump out results
  cout << "Number of integers in list: " << listNumbers.size() << endl;
  cout << "Nummber of integers to search: " << listTargets.size() << endl;
  for(int i=0; i<(int)listTargets.size(); ++i)
  {
    cout << "Target " << listTargets[i] << ":\t";
    if( listResults[i] )
    {
      cout << "FOUND\n";
    }
    else
    {
      cout << "NOT FOUND\n";
    }
  } 

}
