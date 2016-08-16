// Just a simple hello world test
// g++ -std=c++11 -g -o ch3.7_hello_cruel.exe ch3.7_hello_cruel.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"
int main ()
{
  string s = "Goodbye, cruel world! ";
  cout << s << '\n';
  // int if =7; // error: if is a keyword
  int string = 7; // this will lead to trouble (but will compile)
  return 0;
}
