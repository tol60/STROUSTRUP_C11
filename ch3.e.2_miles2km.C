// Convert miles to km
// g++ -std=c++11 -g -o ch3.e.2_miles2km.exe ch3.e.2_miles2km.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"
int main ()
{
  const double factor_m2km = 1.609;
  cout<< "Please enter the number of miles you would like to convert into km:\n";
  double miles{0};
  while (cin >> miles) {
    cout << miles << " miles = " << miles * factor_m2km << " km\n";
  }
  return 0;
}
