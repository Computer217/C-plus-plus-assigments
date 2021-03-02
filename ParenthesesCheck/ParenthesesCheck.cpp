//
//  ParenthesesCheck.cpp
//  
//
//  Created by Yufeng Wu on 11/13/19.
//
//
#include <string>
#include <iostream>
#include <vector>
using namespace std;

// Check if the string has valid nested parentheses
// If so, return true; if not return false; if the string contains
// unexpected symbols, return false
bool ECParentheseCheck(const string &strInput)
{
  // your code goes here

  if (strInput.size() == 0){
      return true;
  }

  vector<char> check;

  for (int i = 0; i < strInput.length(); i++){

    if (strInput[i] != '(' && strInput[i] != '[' && strInput[i] != ')' && strInput[i] != ']'){
        return false;
    }


    if (strInput[i] == '(' || strInput[i] == '['){
        check.push_back(strInput[i]);
    }
    else if (strInput[i] == ')'){
        if (check.size() > 0 && check[check.size()-1] == '('){
            check.pop_back();
        }
        else{
            return false;
        }
    }
    else if (strInput[i] == ']'){
        if (check.size() > 0 && check[check.size()-1] == '['){
            check.pop_back();
        }
        else{
            return false;
        }
    }
     
  }

  if (check.size() == 0){
    return true;
  }
  else{
    return false;
  }
  

}

int main()
{
    
    string s1 = "()";
    bool f1 = ECParentheseCheck(s1);
    if( f1 == false )
    {
        cout << "WRONG1\n";
    }
    string s2 = "()[]";
    bool f2 = ECParentheseCheck(s2);
    if( f2 == false )
    {
        cout << "WRONG2\n";
    }
    

    string s3 = "([)]";
    bool f3 = ECParentheseCheck(s3);
    if( f3 == true )
    {
        cout << "WRONG3\n";
    }

    
    string s4 = "([])";
    bool f4 = ECParentheseCheck(s4);
    if( f4 == false )
    {
        cout << "WRONG4\n";
    }
    
    return 0;
}
