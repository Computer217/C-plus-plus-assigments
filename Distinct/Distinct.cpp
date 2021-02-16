#include <vector>
#include <map>

using namespace std;

// Find the list of distinct elements and store it in vecDistnct (which is sorted)
void ECDistinctNums(const vector<int> &vecInput, vector<int> &vecDistinct)
{
  // your code here
  if (vecDistinct.size() > 0) {vecDistinct.clear();}

  set <int> membership;

  for(int v: vecInput){
    membership.insert(v);
  }
  
  vecDistinct = vector<int>(membership.begin(), membership.end());
}

