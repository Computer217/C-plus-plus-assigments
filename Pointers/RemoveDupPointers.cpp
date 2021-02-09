//
//  RemoveDupPointers.cpp
//  
//
//  Created by Yufeng Wu on 1/18/21.
//
//

#include <string>
#include <iostream>
#include <vector>

using namespace std;

void RemoveDupPointers(vector<string *> &arrayPtrs)
{
    // arrayPtrs: STL vector of pointers to strings
    // remove pointers that are pointed to identical strings in the array
    // Your code goes here...

    //check if the array is empty
    if (arrayPtrs.size() == 0){
        return;
    }

    //vector to check membership
    vector<string *> arrayTest; 
    arrayTest.push_back(arrayPtrs[0]);

    bool flag = false;

    //iterate through arrayPtrs
    for (int i = 0; i < arrayPtrs.size(); i++){
        //check to make sure the element isnt in arrayTest
        for (int j = 0; j < arrayTest.size(); j++){
            if (*arrayPtrs[i] == *arrayTest[j]){
                //if the element is in the array set to true
                flag = true;
            }
        }

        //if element in the testarray dont add
        if (flag == false){
            arrayTest.push_back(arrayPtrs[i]);
        }

        flag = false;

    }

    arrayPtrs.clear();

    //rewrite arrayPtrs
    for (int i=0; i<arrayTest.size();i++){
        else{
            arrayPtrs.push_back(arrayTest[i]);
        }
    }

    /*
    for (int i=0; i<arrayPtrs.size(); i++){
        cout<< *arrayPtrs[i] <<endl;
    }
    */
}


/*
int main(){
    string s1="abc", s2 = "bcd", s3="abc";
    vector<string *> array;
    array.push_back(&s1);
    array.push_back(&s2);
    array.push_back(&s3);
    array.push_back(&s1);

    RemoveDupPointers(array);
}
*/

