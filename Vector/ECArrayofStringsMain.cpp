#include<iostream>
#include"ECArrayofStrings.h"

int main(void)
{
    ECArrayofStrings as;
    as.AddString(std::string("hello1"));
    as.AddString(std::string("hello2"));
    as.AddString(std::string("hello3"));
    as.AddString(std::string("hello4"));
    as.AddString(std::string("hello"));
    std::cout<<"Strings: "<<std::endl;
    as.Dump();
    std::cout<<"Number of Strings: "<<as.GetNumofStrings()<<std::endl;
    std::cout<<"Maximum Length of string: "<<as.GetMaxLen()<<std::endl;
    std::cout<<"Maximum Length of string: "<<as.GetLongestCommonPrefix()<<std::endl;
    return 0;
}