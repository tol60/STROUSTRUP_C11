// EX14: Can we declare a non-reference funciton argument const (e.g, void f(const int);)? What might that mean?
// why might we want to do that? Why don't people do that often?
// Try it; write a couple of small programs to see what works.

// g++ -std=c++11 -g -o ch8.e.14_non-reference_const.exe ch8.e.14_non-reference_const.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

void test (const int in){
  cout << "test: you passed " << in <<endl;
  // in++; // error, const int prevents this from compilation
  // cout << "test: after incr, " << in << endl;
}

int main ()
{
  test(5);
  int a=3;
  int b=6;
  test (a*b);

  return 0;
}
