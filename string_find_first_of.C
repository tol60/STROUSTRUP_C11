/*
 * string_find_first_of.C
 *
 *  http://www.cplusplus.com/reference/string/string/find_first_of
 */
// g++ -std=c++11 -g -o string_find_first_of.exe string_find_first_of.C  2>&1 | tee tmp.txt

// string::find_first_of
#include <iostream>       // std::cout
#include <string>         // std::string
//#include <cstddef>        // std::size_t

int main ()
{
  std::string str ("Please, replace the vowels in this sentence by asterisks.");
  std::cout<< str << '\n';
  std::size_t found = str.find_first_of("aeiou"); // If no matches are found, the function returns string::npos.
  while (found!=std::string::npos)
  {
    str[found]='*';
    found=str.find_first_of("aeiou",found+1);
  }

  std::cout << str << '\n';

  return 0;
}


