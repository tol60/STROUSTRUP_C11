// Enter 3 integers. Output them in increasing order
// g++ -std=c++11 -g -o ch3.e.6_three_int.exe ch3.e.6_three_int.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"
int main ()
{
  cout<< "Please enter the 3 integers:\n";
  int a{0},b{0},c{0}; // 3 numbers we get
  int tmp{0}; // temporary value
  cin >> a >> b >> c;

  if (a>b) {
    tmp = b;
    b = a;
    a = tmp;
  }
  // now a <= b

  if (a> c) {
    // means c < a<=b
    cout << c <<", " << a <<", " << b <<endl;
  } else {
    // a is the smallest (or equal to), but we need to check b and c
    cout << a << ", ";
    if (b>c) {
      // a <= c < b
      cout << c << ", " << b<< endl;
    } else {
      // a <= b <= c
      cout  << b << ", " << c<< endl;
    }
  }
  return 0;
}


