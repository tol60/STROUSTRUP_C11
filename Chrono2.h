/*
 * Chrono2.h
 *
 *  Date class
 *  ch9 Ex 12: Change the representation of a Date to be the number of days sinse January 1, 1970 (known as day 0), represented as a long int,
  re-implement the functions from $9.8. (Put in Chrono2.h) Be sure to reject dates outside the range we can represent that way (feel free to reject days before day 0,
  i.e, no negative days.
 */

#ifndef CHRONO2_H_
#define CHRONO2_H_

#include "std_lib_facilities.h"
using namespace std;

namespace Chrono2 {

enum class Month {
  jan=1,feb,mar,apr,may,jun,jul,aug,sep,oct,nov,dec
};

const vector <string> month_tbl{"Months","jan","feb","mar","apr","may","jun","jul","aug","sep","oct","nov","dec"};
ostream& operator <<(ostream& os, const Month& m);
Month operator++(Month& m); // prefix increment operator

class Date{
public:
  class Invalid{};              // to throw an exception

  Date(int y, Month m, int d);  // check for valid date and initialize// Adjusted to zero day
  Date(long int d); // basic constructor.
  Date();                       // default constructor
  // the default copy operations are fine

  // nonmodifying operations
  int zero_day() const {return md_zero;}; // returns actual representation

  // keep these functions similar to Chrono version
  int day() const;
  Month month() const;
  int year() const;
  void calendar(int& y, Month& m, int& d) const; // we will get standard presentation from the zero day

  long int d_zero() const {return md_zero;}

  // modifying operations
  void add_day(int n);
  void add_month(int n);  // If you add a month to 31 Jan you will get 28 or 29 Feb (depending on the leap year)
  void add_year(int n);   // If you add a year to the last day of Feb, you will get a last day of Feb (depending on the leap year it will be 28 or 29)

  int days_in_month(const Month& mth, int year ) const; // returns the number of days in a given month. We only use year for Month::feb to determine a leap year
private:
  long int md_zero; // number of days since 1 Jan 1970 (day 0)
};

bool is_date(int y, Month m, int d); // true for valid date
bool leapyear(int y); // true if y is a leap year

bool operator==(const Date& a, const Date& b);
bool operator!=(const Date&a, const Date& b);

ostream& operator<<(ostream& os, const Date& d);

istream& operator>>(istream& is, Date& dd);

enum class Day {
  sunday, monday, tuesday, wednesday, thursday, friday, saturday
};
const vector <string> day_tbl{"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
ostream& operator <<(ostream& os, const Day& d);

Day int_to_Day(int x); // does boundary checking. Returns sunday for 0, monday for 1, saturday for 6

Day day_of_week(const Date& d); // will return the day of the week (Day::sunday, Day::monday, ..., Day::saturday).

// helper functions
Date next_workday(const Date& d); // (assume that any day that is not a Saturday or a Sunday is a workday)
int week_of_year(const Date& d); // (assume that week 1 is the week with January 1 in it and that the first day of a week is a Sunday)


} // Chrono2




#endif /* CHRONO2_H_ */
