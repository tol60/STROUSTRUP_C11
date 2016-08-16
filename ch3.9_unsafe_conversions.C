// Just a simple hello world test
// g++ -std=c++11 -g -o ch3.9_unsafe_conversions.exe ch3.9_unsafe_conversions.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"
int main ()
{
  cout << "This program will illustrate conversion from double into other types." << endl
      << "Please enter a number(s):"<< endl;
  double d = 0.0;
  while (cin >> d) {
    int i = d;  // try to squeeze double into int
    char c = i; // try to squeeze int into char
    int i2 = c; // get the integer value of the character
    cout << "d==" << d  // the original double
        << " i==" << i   // converted to int
        << " i2=="<<i2   // int value of char
        << " char("<<c<<")\n"; // the char
  }
  double x {2.7};
  int y = x;
  cout << "x="<<x<<", y="<< y <<endl;

  x = -2.7;
  y=x;
  cout << "x="<<x<<", y="<< y <<endl;
  return 0;
}
