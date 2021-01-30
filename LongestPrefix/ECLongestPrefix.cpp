#include "ECLongestPrefix.h" 
#include <iostream>

using namespace std;

// Implement the longest prefix function here...
std::string ECLongestPrefix(int numStrings, const std::string arrayStrings[])
{
  // YW: this only serves as a starter code, which just print out the given array of strings
  // Replace with your own code here...
  //
  //Get first string to compare to rest of array
  string strDummy = arrayStrings[0];

  //for every word in the array (after first word)
  for (int i=1; i<numStrings; i++){
	  
	  //iterate as small as the smallest of the two word (between first and second word in question)
	  for(int j=0; j<= min(strDummy.length(), arrayStrings[i].length()); j++){
		  //if we reach the length of the current word 
		  //the substring becomes the word itself
		  if (j == arrayStrings[i].length()){
			  strDummy = arrayStrings[i]; 
			  break;
		  }
		  //compare each char in first word to the chars of the nexrt word 
		  // if they are not equal then we make the substring until (not including) that char
		  if (strDummy[j] != arrayStrings[i][j]){
			  strDummy = strDummy.substr(0,j);
			  break;
		  }
	  }
  }
  cout << endl;
  return strDummy;
}
