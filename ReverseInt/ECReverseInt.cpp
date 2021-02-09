//
//  ECReverseInt.cpp
//  
//
//  Created by Yufeng Wu on 11/13/19.
//  Reverse an integer. Assume unsigned.
//

#include <iostream>

using namespace std;

// Reverse an integer (stored in decimal format in a string)
string ECReverseInt(const string &strNumber)
{
    string res;
    
    // your code goes here
    for (int i = strNumber.size()-1; i >= 0; i--){

        if (res.empty() && strNumber[i] == '0'){
            continue;
        }
        else{
            res += strNumber[i];
        }
    }


    return res;
}


int main(){
    string num = "";
    cout << ECReverseInt(num) << endl; 

    return 0;
}


