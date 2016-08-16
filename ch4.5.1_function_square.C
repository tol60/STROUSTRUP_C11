// calculate and print table of squares 0-99 (using summations;
// g++ -std=c++11 -g -o ch4.5.1_function_square.exe ch4.5.1_function_square.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

int square (int x) {
  //return x*x;
  int sum{0};
  for (int i=0; i<x; ++i)  // we want to handle x=0 case as well
    sum +=x;
  return sum;
}

int main ()
{
  for (int i = 0; i<100; ++i)
    cout << i << "\t" << square(i) << endl;
  return 0;
}


