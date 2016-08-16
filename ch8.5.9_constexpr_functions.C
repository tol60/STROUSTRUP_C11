// Enter the first name and age (in years)
// g++ -std=c++11 -g -o ch8.5.9_constexpr_functions.exe ch8.5.9_constexpr_functions.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

struct Point {
  double x;
  double y;
};

constexpr double xscale = 10; // scaling factor
constexpr double yscale = 0.8;
constexpr Point scale(Point p) {return {xscale *p.x, yscale*p.y};}
void PrintPoint (Point& p){
  cout << "x = "<<p.x << ", y = "<<p.y;
}

void user(Point p1)
{
  Point p2{20,20};
  Point p3 = scale(p1); // OK; run-time evaluation is fine
  Point p4 = scale(p2);
  //constexpr Point p5 = scale(p1); // error: scale(p1) is not a constant expression
  constexpr Point p6 = scale(p2); // OK according to Stroustrup, compiler complains
}

int main ()
{
  Point p1{10,10};
  cout << "p1: "; PrintPoint(p1); cout << endl;
  Point p4 = scale(p1);
  cout << "After scaling, "; PrintPoint(p4); cout << endl;
  return 0;
}
