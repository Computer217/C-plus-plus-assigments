#include <vector>
#include <iostream>
using namespace std;

string RemoveSpaces( const string &strIn)
{
    // remove all spaces in strIn and return this new string
    // The function _RemoveSpaces_ cannot alter the strIn variable values of the calling function
    //since you cant ALTER <strIn> then you can only USE <strIn> as shown below...
    // your code goes here...
    string temporary;
    int len = strIn.size();

    for (int i = 0; i <= len; i++){
	    if (strIn[i] != ' '){
		    temporary = temporary + strIn[i];
	    }
    }

    return temporary;
}

// now test it out
int main()
{
    const string str1 = "I am a student.";
    const string str2 = "";
    const string str3 = "This   is   wrong!";
    string str1Out = RemoveSpaces(str1);
    cout << str1Out << endl;
    string str2Out = RemoveSpaces(str2);
    cout << str2Out << endl;
    string str3Out = RemoveSpaces(str3);
    cout << str3Out << endl;
    return 0;
}

