// Implement leap year from $9.8 (Chrono.h)
// g++ -std=c++11 -g -o ch9.e.10_LeapYear.exe ch9.e.10_LeapYear.C Chrono.C  2>&1 | tee tmp.txt
 
#include "std_lib_facilities.h"

#include "Chrono.h"


int main ()
{
  /*
  Chrono::Month mm {Chrono::Month::jan};
  cout << "mm = " << mm << endl;
  Chrono::Date today {2015,Chrono::Month::dec,30};
  Chrono::Date date_A {2013,Chrono::Month::nov,9};
  Chrono::Date date_B {2013,Chrono::Month::jan,31};
  cout << "Date today = " << today << endl;
  cout << "Date date_A = " << date_A << endl;
  cout << "Date date_B = " << date_B << endl;
  */

  for (int year = 2016;year <2030; year++) {
    cout << year;
    if (Chrono::leapyear(year))
      cout << " is a leap year\n";
    else
      cout << " is not a leap year\n";
  }
  return 0;
}


