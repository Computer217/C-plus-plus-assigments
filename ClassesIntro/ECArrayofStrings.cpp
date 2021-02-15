#include <iostream>
#include "ECArrayofStrings.h" 

using namespace std;

ECArrayofStrings :: ECArrayofStrings()
{
}

ECArrayofStrings :: ~ECArrayofStrings()
{
  // your code goes here
  setofstrings.clear();
}

void ECArrayofStrings :: AddString( const string &strToAdd )
{
  // your code goes here
  setofstrings.push_back(strToAdd);
}

int ECArrayofStrings :: GetNumofStrings() const
{
  // your code goes here
  return setofstrings.size();

}

int ECArrayofStrings :: GetMaxLen() const
{
  // your code goes here
  int count = 0;

  for(int i=0; i<setofstrings.size();i++){
    if (setofstrings[i].size() > count){
      count = setofstrings[i].size();
    }
  }
  return count;
}

string ECArrayofStrings :: GetLongestCommonPrefix() const
{
  // your code goes here


  string strDummy = setofstrings[0];

  //for every word in the array (after first word)
  for (int i=1; i<setofstrings.size(); i++){
	  
	  //iterate as small as the smallest of the two word (between first and second word in question)
	  for(int j=0; j<= min(strDummy.length(), setofstrings[i].length()); j++){
		  //if we reach the length of the current word 
		  //the substring becomes the word itself
		  if (j == setofstrings[i].length()){
			  strDummy = setofstrings[i]; 
			  break;
		  }
		  //compare each char in first word to the chars of the nexrt word 
		  // if they are not equal then we make the substring until (not including) that char
		  if (strDummy[j] != setofstrings[i][j]){
			  strDummy = strDummy.substr(0,j);
			  break;
		  }
	  }
  }
  cout << endl;
  return strDummy;
}

string ECArrayofStrings :: Concatnate() const
{
  // your code goes here

  string concatenation = "";

  for (int i=0; i<setofstrings.size();i++){
    concatenation += setofstrings[i];
  }

  return concatenation;
}

void ECArrayofStrings:: Dump() const
{
  // your code goes here
  for (int i=0; i<setofstrings.size(); i++){
    cout << setofstrings[i] << endl;
  }

}

string ECArrayofStrings :: GetLongestCommonPrefixofTwo(const string &str1, const string &str2) const
{
  // your code goes here

  string strDummy = "";
  string other = "";

  /*
  if (str1.length() < 1 || str2.length() < 1){
    return strDummy;
  }
  */

  if (str1.length() > str2.length()){
    strDummy = str1;
    
  }
  else{
    strDummy = str2;
  }

  //iterate up to smallest of both strings
	for(int i=0; i< min(strDummy.length(), str2.length()); i++){

		  if (str1[i] != str2[i]){
        return strDummy;
		  }
      else{
        strDummy = strDummy.substr(0,i);
      }
	  }

  //cout << endl;
  return strDummy;


}


