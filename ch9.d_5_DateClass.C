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
// g++ -std=c++11 -g -o ch9.d_5_DateClass.exe ch9.d_5_DateClass.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

enum class Month {
  jan,feb,mar,apr,may,jun,jul,aug,sep,oct,nov,dec
};

vector <string> month_tbl{"jan","feb","mar","apr","may","jun","jul","aug","sep","oct","nov","dec"};
ostream& operator <<(ostream& os, const Month& m){
  return os << month_tbl[int(m)];
}

// simple date (control access)
class Date{
public:
  Date(int y, Month m, int d); // check for valid date and initialize

  Month month() const {return m;}
  int day() const {return d;}
  int year() const {return y;}

  void add_day(int n); // increase the Date by n days
  void add_month(int n);
  void add_year(int n)
private:
  int y; // year
  Month m; // month of year
  int d; // day of month
};

/*
ostream& operator <<(ostream& os, const Date& d){
  return os << '(' << d.year()
            << ',' << d.month()
            << ',' << d.day() << ')';
}
*/

// helper functions
Date::Date( int yy, Month mm, int dd )// constructor
  :y{yy}, m{mm}, d{dd}
{
  string msg;
  // check that (y,m,d) is a valid date
  if (y<=31)       error("Error: Date constructor: Year <=31. You entered " + to_string(y)); // probably entered a day or a month
  //if (m<1|| m>12)  error("Error: Date constructor: month has to be within [1,12]. You entered " + to_string(m));
  if (d<1 || d>31) error("Error: Date constructor: day has to be within [1,31]. You entered " + to_string(d));
}

void Date::add_day(int n)
{
  // increase dd by n days
  if (n<0) error("Error: add_day: Negative increment not supported" + to_string(n));

  d +=n; // generally wrong (can wrap around, but for simple test ok
}

void some_function(Date& d, const Date& start_of_term){
  int a = d.day(); // OK
  int b = start_of_term.day();
  d.add_day(3); // fine
  // start_of_term.add_day(3); // error
}

int main ()
{
  // Date my_birthday; // Error, my_birthday is not initialized

  // set today to June 25, 1978
  Date today {1978,Month::jun,25};
    // Date today {25,6,1978}; // run-time error
    // Date today {1978,25,6}; // run-time error

  // create a Date tomorrow
  Date tomorrow = today;
  // tomorrow.d++; // error, can not access private member  increment the date
  tomorrow.add_day(1);

  // output today and tomorrow
/*
  cout << "Today: " << today << endl;
  cout << "Tomorrow: " << tomorrow << endl;
*/
  return 0;
}


