// This drill simply involves getting the sequence of versions of Data to work
/*
   For each version define a Date called today initialized to June 25, 1978.
 Then, define a Data called tomorrow and give it a value by copying today into it
 and increasing its day by one using add_day().
 Finally, output today and tomorrow using a << defined as in 9.8.

   Your check for a valid data may be very simple. Feel free to ignore leap years.
 However, don't accept a month that is not in the [1,12] range or day of the month
 that is not in the [1,31]. Test each version with at least one invalid date (e.g. 2004,13,-5).

 1. The version from 9.4.1
 2. The version from 9.4.2
 3. The version from 9.4.3
 4. The version from 9.7.1
 5. The version from 9.7.4
 */
// g++ -std=c++11 -g -o ch9.d_0_DateClass.exe ch9.d_0_DateClass.C Chrono.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

#include "Chrono.h"

int main ()
{
  Chrono::Month mm {Chrono::Month::jan};
  cout << "mm = " << mm << endl;
  Chrono::Date today {2013,Chrono::Month::nov,9};
  cout << "Date = " << today << endl;
  cout << "Enter a new date (yyyy,mm,dd)\n";
  cin >> today;
  cout << "Date = " << today << endl;

  return 0;
}


