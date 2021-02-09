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

int main(int argc, const char* argv[]){
	vector<int> listNumbers;

	ReadIntsFromFile(argv[1], listNumbers);
	
	cout << listNumbers.size() <<endl;

	for (int i=0; i<listNumbers.size();i++){
		cout << listNumbers[i] <<endl;
		}
	cout << "ok" << endl;
}
