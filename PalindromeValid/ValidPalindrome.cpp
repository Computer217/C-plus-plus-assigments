//
//  ValidPalindrome.cpp
//  
//
//  Created by Yufeng Wu on 1/18/21.
//
//

#include <iostream>
#include <cstdio>

using namespace std;

// Function to test if the input string is a valid palindrome
// Note: only consider alphanumeric symbols and ignore cases
bool IsValidPalindrome(const string &strInput)
{
    // your code go here ...
    string Original;

    //remove any non-alphanumeric char
    for (int i = 0; i < strInput.size(); i++){
        if (isalnum(strInput[i])){
            Original += tolower(strInput[i]);
            
        }
    }

    //store original without spaces 
    remove(Original.begin(), Original.end(), ' ');

    //reverse original into another variable

    string palindrome_test = Original;

    reverse(palindrome_test.begin(), palindrome_test.end());

    //compare the two
    cout << strInput << endl;
    cout << Original << endl;
    cout << palindrome_test << endl;


    if (palindrome_test == Original){
        return true;
    }
    else{
        return false;
    }
}


