// Example with simple operations
// g++ -std=c++11 -g -o ch3.3_simple_operations.exe ch3.3_simple_operations.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"
int main ()
{
//  cout << "Please enter a floating-point value: ";
//  double F = -1.0;
  cout << "Please enter an integer value: ";
  int F = 1;
  cin >> F; // read the floatin-point number
  cout<< "F == " << F << endl
      << "F+1 == " << F+1 << endl
      << "three times F == " << 3 * F << endl
      << "F squared == " << F * F << endl
      << "square root of F == " << sqrt(F) << endl
      << "half of F == " << F/2 << endl
      << "F modulo 2 == " << F%2 << endl
      << "F / 3 == " << F/3 << endl
      << "F modulo 3 == " << F%3 << endl
;

  return 0;
}
