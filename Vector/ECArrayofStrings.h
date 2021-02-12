#ifndef EC_ARRAY_OF_STRINGS
#define EC_ARRAY_OF_STRINGS

using namespace std;
#include <string>

#include <vector>

// define a class for an array of strings
// use vector<string> to implement an array of strings
class ECArrayofStrings
{
public:
  ECArrayofStrings();
  ~ECArrayofStrings();
  // Add one string to the array of strings
  void AddString( const std::string &strToAdd );
  // return the total number of strings in the array
  int GetNumofStrings() const;
  // return the maximum length of the longest string in the array
  int GetMaxLen() const;
  // Return the longest common prefix of the strings in the array
  std::string GetLongestCommonPrefix() const;
  // return the concatnated string of all strings in the array (in the order of their addition)
  std::string Concatnate() const;
  // dump out all strings in the array
  void Dump() const;

private:
  // return the longest common prefix of two strings
  std::string GetLongestCommonPrefixofTwo(const std::string &str1, const std::string &str2) const;

  // use vector of strings to implement an array of strings
  std::vector<std::string> setofstrings;
};


#endif
