// The Drill demonstrates the difference of passing the argument to a function:
//  a. by value swap_v(int,int)
//  b. by reference swap_r(int&,int&)
//  c. by const reference swap_cr(const int&, const int&)
/*
 * Try calling each function like this. Which functions and calls compiled, and why?
 * After each swap that compiled, print the value of the arguments after the call to see if they were actually swapped.
 *
  // integer
  int x=7;
  int y=9;
  swap_?(x,y);
  swap_?(7,9);

  // const integer
  const int cx=7;
  const int cy=9;
  swap_?(cx,cy);
  swap_?(7.7,9.9);

  // double
  double dx=7.7;
  double dy=9.9;
  swap_?(dx,dy);
  swap_?(7.7,9.9);
*/
// g++ -std=c++11 -g -o ch8.d.2_swap_v.exe ch8.d.2_swap_v.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

void swap_v(int a, int b) {int temp; temp = a; a=b; b=temp;}
void swap_r(int& a, int& b) {int temp; temp = a; a=b; b=temp;}
//void swap_cr(const int& a, const int& b) {int temp; temp = a; a=b; b=temp;} // will not compile as we have const ref

int main ()
{
  // integer
  int x=7;
  int y=9;
  cout << "Before the swap x = "<< x << ", y = "<<y <<endl;
  swap_v(x,y);
  cout << "After the swap x = "<< x << ", y = "<<y <<endl;
  swap_v(7,9);

  // const integer
  const int cx=7;
  const int cy=9;
  cout << "Before the swap cx = "<< cx << ", cy = "<<cy <<endl;
  swap_v(cx,cy);
  cout << "After the swap cx = "<< cx << ", cy = "<<cy <<endl;
  swap_v(7.7,9.9);

  // double
  double dx=7.7;
  double dy=9.9;
  cout << "Before the swap dx = "<< dx << ", dy = "<<dy <<endl;
  swap_v(dx,dy);
  cout << "After the swap dx = "<< dx << ", dy = "<<dy <<endl;
  swap_v(7.7,9.9);

  return 0;
}
