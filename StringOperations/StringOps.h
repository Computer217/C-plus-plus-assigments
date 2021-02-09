#ifndef STRING_OPS_H
#define STRING_OPS_H

#include <vector>
#include <set>

// concatnate strings: concatnate strConcating into strConcatTo
void ConcatenateStrings( std::vector<char> &strConcatTo, const std::vector<char> &strConcating );

// find all distinct k-length substrings in strInput and store in the set setUniqueSubstrings
void GetDistinctSubstrings( const std::vector<char> & strInput, int k, std::set< std::vector<char> > &setUniqueSubstrings  );

// determine if strInput contains strPattern as a substring
bool IsSubString( const std::vector<char> &strInput, const std::vector<char> &strPattern );

// find duplicate (i.e. appearing at least twice) characters in string
void GetDuplicateChars(const std::vector<char> &strInput, std::set<char> &setDupChars);

#endif // STRING_OPS_H
