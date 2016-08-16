// This drill simply involves getting the sequence of versions of Date to work
/*
   For each version define a Date called today initialized to June 25, 1978.
 Then, define a Date called tomorrow and give it a value by copying today into it
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
// g++ -std=c++11 -g -o ch9.d_1_DateClass.exe ch9.d_1_DateClass.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

// simple date (too simple?)
struct Date{
  int y; // year
  int m; // month of year
  int d; // day of month
};

ostream& operator <<(ostream& os, const Date& d){
  return os << '(' <<d.y
            << ',' << d.m
            << ',' << d.d << ')';
}

// helper functions
void init_day(Date& dd, int y, int m, int d )
{
  string msg;
  // check that (y,m,d) is a valid date
  if (y<=31)        error("Error: init_day: Year <=31. You entered " + to_string(y)); // probably entered a day or a month
  if (m<1|| m>12)  error("Error: init_day: month has to be within [1,12]. You entered " + to_string(m));
  if (d<1 || d>31) error("Error: init_day: day has to be within [1,31]. You entered " + to_string(d));

  // if it is, use to initialize dd
  dd.y = y;
  dd.m = m;
  dd.d = d;
}

void add_day(Date& dd, int n)
{
  // increase dd by n days
  if (n<0) error("Error: add_day: Negative increment not supported" + to_string(n));

  dd.d +=n; // generally wrong (can wrap around, but for simple test ok
}

int main ()
{
  Date today;
  // set today to June 25, 1978
  // today.y = 1978;
  // today.m = 6;
  // today.d = 25;
  init_day(today,1978,6,25);
    // init_day(today,25,6,1978); // error entry
    // init_day(today,1978,25,6); // error entry

  // create a Date tomorrow
  Date tomorrow = today;
  // tomorrow.d++; // increment the date // use function later)
  add_day(tomorrow,1);

  // output today and tomorrow
  cout << "Today: " << today << endl;
  cout << "Tomorrow: " << tomorrow << endl;

  return 0;
}


