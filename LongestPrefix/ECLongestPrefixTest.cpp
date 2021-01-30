#include "ECLongestPrefix.h"
#include <iostream>
using namespace std;
#define BIG_NUM 1000

// perform test
static void Test()
{
  // Test case 1: Two matching characters
  string arrStr1[3];
  arrStr1[0] = "flower";
  arrStr1[1] = "flow";
  arrStr1[2] = "flight";
  string res1 = ECLongestPrefix(3, arrStr1);
  cout << res1 << endl;;

  // Test case 2 : No Prefix
  string arrStr2[3];
  arrStr2[0] = "dog";
  arrStr2[1] = "racecar";
  arrStr2[2] = "car";
  string res2 = ECLongestPrefix(3, arrStr2);
  cout << res2 << endl;;

  // Test case 3: Large number of String in Array
  string arrStr3[BIG_NUM];
  for(int i=0;i<BIG_NUM;i++)
  {
    arrStr3[i] = "dog"+to_string(i);
  }
  string res3 = ECLongestPrefix(BIG_NUM, arrStr3);
  cout << res3 << endl;;

  // Test case 4 : One String different in Array
  string arrStr4[3];
  arrStr4[0] = "da";
  arrStr4[1] = "da";
  arrStr4[2] = "de";
  string res4 = ECLongestPrefix(3, arrStr4);
  cout << res4 << endl;;

  // Test case 5 : One String in Array
  string arrStr5[1];
  arrStr5[0] = "apple";
  string res5 = ECLongestPrefix(1, arrStr5);
  cout << res5 << endl;;

  // Test case 6: Empty String
  string arrStr6[3];
  arrStr6[0] = "";
  arrStr6[1] = "abc";
  arrStr6[2] = "abc"; 
  string res6 = ECLongestPrefix(3, arrStr6);
  cout << res6 << endl;;

  // Test case 7: Long string
  string arrStr7[3];
  arrStr7[0] = "";
  arrStr7[1] = "";
  arrStr7[2] = ""; 
  for(int i=0;i<BIG_NUM;i++)
  {
    arrStr7[0] += char((int('A')+i%26));
    arrStr7[1] += char((int('A')+i%26));
    arrStr7[2] += char((int('A')+i%26));  
  }
  string res7 = ECLongestPrefix(3, arrStr7);
  cout << res7 << endl;;
}


int main()
{
  Test();
  return 0;
}

