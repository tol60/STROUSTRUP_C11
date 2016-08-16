//
/* D1. Start a program to work with points, discussed in 10.4. Begin by defining the data type Point that has two coordinate nembers x and y.
 */
// g++ -std=c++11 -g ch10.d.1_Point.C  -o ch10.d.1_Point.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

struct Point {
  int x;
  int y;
  Point ():x{0},y{0}{}
  Point (int a, int b) :x{a},y{b}{}
};

ostream& operator<< (ostream& os, const Point& p) {
  return os << '('<< p.x
      <<','<< p.y << ')';
}

int main ()
{
  Point pA;
  cout << "Default Point A = " << pA<< endl;

  Point pB{-45, 7};
  cout << "Point B = " << pB<< endl;

  Point pC(pB); // Copy constructor
  cout << "Point C (initialized by Point B) = " << pC<< endl;
  pC.y +=3;
  cout << "After incrementing y by 3, Point C = " << pC << endl;

  return 0;
}


