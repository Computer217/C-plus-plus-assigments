#include <vector>
#include <iostream>
using namespace std;

void ClearInt(int *pt)
{
  // your code goes here
  // check if the pointer is NULL
  //
  if (pt) {
	*pt = 0;
  }
}

// same thing but use a const pointer...
void ClearIntConstPtr(int* const pt)
{
  // 
  *pt = 0;
}

// now pass in a reference to integer...
void ClearIntRef(int &pt)
{
  pt = 0;
}


int main(){
	int x = 2;
	ClearInt(&x);
	ClearInt(NULL);

	cout<<x<<endl;
	int y = 1;
	ClearIntConstPtr(&y);
	cout<<y<<endl;
	int z = 3;
	ClearIntRef(z);
	cout<<z<<endl;

	return 0;
}

