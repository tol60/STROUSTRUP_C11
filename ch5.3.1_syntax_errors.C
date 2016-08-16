// Illustrate some compile-time errors
// g++ -std=c++11 -g -o ch5.3.1_syntax_errors.exe ch5.3.1_syntax_errors.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

int area (int length, int width) {
  return length * width;
}

int main ()
{
  // int s0 = area(7,8);// good

  // Syntax errors:
  // int s1 = area(7,8; // error: ) missing
  // int s2 = area(7,8) // error: ; missing
  // Int s3 = area(7,8);   // error: Int is not a type
  // int s4 = area('7,8);  // error: non-terminated character (' missing)

  // Type errors:
  // int x0 = arena(7); // error: undeclared function
  // int x1 = area(7); // error: wrong number of arguments
  // int x2 = area("seven",2); // error: 1st argument has a wrong type

  // 5.3.3 Non-errors
  int x4 = area(10,-7); // OK: but what is a rectangle with a width of minus 7
  cout << "area(10,-7) = "<< x4 << endl;
  int x5 = area(10.7, 9.3); // OK: but calls area(10,9)
  cout << "area(10.7, 9.3) = " << x5 << endl;
  char x6 = area(100,9999); // OK: but trancates the result
  //int x6_int = x6;
  //cout << "area(100,9999) = "<< x6_int << endl;
  cout << "area(100,9999) = "<< (int) x6 << endl;
  return 0;
}


