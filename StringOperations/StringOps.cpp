#include "StringOps.h"
#include <iostream>
#include <map>

using namespace std;


// concatnate strings: concatnate strConcating into strConcatTo
void ConcatenateStrings( std::vector<char> &strConcatTo, const std::vector<char> &strConcating  )
{
    // your code goes here
    for(char c: strConcating){
        strConcatTo.push_back(c);
    }
}

// find all distinct k-length substrings in strInput and store in the set setUniqueSubstrings
void GetDistinctSubstrings( const std::vector<char> & strInput, int k, std::set< std::vector<char> > &setUniqueSubstrings  )
{
  // your code goes here
  //get all substrings in strInput of length k 
  

  setUniqueSubstrings.clear();
  int index = 0;
  vector<char> temp;

  if (k < 1){
      return;
  }

  while (index + k != strInput.size()+1){
      for(int i = index; i < index + k; i++){
          temp.push_back(strInput[i]);
      }
      setUniqueSubstrings.insert(temp);

      /*
      for (char c : temp){
          cout << c << endl;
      }

      cout << "***ADDED***" << endl;
      */

      temp.clear();
      index++;
  }

}

// determine if strInput contains strPattern as a substring
bool IsSubString( const std::vector<char> &strInput, const std::vector<char> &strPattern )   
{
    // your code goes here
    //strPattern a substring of StrInput

    if (strPattern.size() < 1){
        return false;
    }

    int index = 0;
    int k = strPattern.size();
    vector<char> temp;
    
    bool flag;

    while (index + k != strInput.size()+1){
        flag = true;
        


        //create substring
        for(int i = index; i < index + k; i++){
            temp.push_back(strInput[i]);
        }

        //compare substrings 
        for(int j = 0; j < k; j++){
            if (temp[j] != strPattern[j]){
                flag = false;
                break;

            }
        }

        if (flag == true){
            //cout << "ENTERED" << endl;
            return flag;
        }

        /*
        for (char c : temp){
            cout << c << endl;
        }
        for (char x : strPattern){
            cout << x << endl;
        }

        cout << "DONE" << endl;
        */


        temp.clear();
        index++;
    }

    return flag;
}

// find duplicate (i.e. appearing at least twice) characters in string
void GetDuplicateChars(const std::vector<char> &strInput, std::set<char> &setDupChars)
{
    // your code goes here
    map <char,int> mapDistinct;
    setDupChars.clear();

    if (strInput.size() < 1){
        return;
    }

    for(char v : strInput){
        //if there is no element
        if (mapDistinct.find(v) == mapDistinct.end()){
            //add element
            mapDistinct[v] = 1;
        }
        else{
            mapDistinct[v] += 1;
        }
    }


    for (int i = 0; i< strInput.size();i++){        
        if (mapDistinct[strInput[i]] > 1){
            setDupChars.insert(strInput[i]);
        }
    }


    /*
    for (char c: setDupChars){
        cout << c << endl;
    }

    
    why does this not work -> doesnt work bc you cant use a range loop on a map
    only on vector/array
    for(char d : mapDistinct){
        if (mapDistinct[d] > 1){
            setDupChars.insert(d);
        }
    }
    */
}


/*
int main(){

    vector<char> str = {'a', 'b', 'a', 'c', 'c', 'b'};
	set<char> dups;
	GetDuplicateChars(str, dups);

}
*/


