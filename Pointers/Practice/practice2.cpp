#include <iostream>

// don't change
void PrintInt(int *ptr)
{
  if( ptr != NULL )
  {
    std::cout << *ptr << std::endl;
  }
}

void PrintChar(char *ptr)
{
  if( ptr != NULL )
  {
    std::cout << *ptr << std::endl;
  }
}

// CHANGE HERE....
void PrintCharInInt(char *ptr)
{
  // your code here...
  // Use Reinterpret since youre changing between different types
  // Behaves like C when changing types  
  std::cout<<reinterpret_cast<int*>(ptr) << std::endl;
}

void PrintIntInChar(int *ptr)
{
  // your code here...
  std::cout<<reinterpret_cast<char*>(ptr) << std::endl;
  
  
}

// don't change
int main()
{
  int x = 48;
  PrintIntInChar(&x);
  // what if you do the following?
  char a = '0';
  // PrintCharInInt(&a);
  return 0;
}
