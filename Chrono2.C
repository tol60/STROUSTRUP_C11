/*
 * Chrono2.C
 * Class to represent Date
 */

#include "Chrono2.h"

namespace Chrono2{

ostream& operator <<(ostream& os, const Month& m){
  return os << month_tbl[int(m)];
  //return os << int(m);
}

Month operator++(Month& m) // prefix increment operator
{
  m = (m==Month::dec)? Month::jan:Month(int(m)+1); // wrap around
  return m;
}

Date::Date(int yy, Month mm, int dd)
:md_zero{0}
{
  if (!is_date(yy,mm,dd)) throw Invalid{};

  const long int leap_cycle = 365*4+1; // If a user gives us a large number (multiple years), we can speed up the process by adding 4 years at a time.
  int y_diff = (yy - 1970);

  md_zero = ( y_diff / 4 ) * leap_cycle;
  y_diff %= 4;  // we need the remaining 4 years.

  // to simplify, make sure all the increments are non-zero from now on.
  if (y_diff < 0){
    y_diff += 4;
    md_zero -= leap_cycle;
  }

  // at his point y_diff can be 0 1 2 or 3 (equivalent to 1970, 1971, 1972 and 1973 as far as determining the leap year calculation)
  for (int i = 1; i<=y_diff; ++i){  // only need to adjust years 1,2 and 3 (no adjustment for year 0 is required)
    // we need to add the following to adjust the full year
    // 0: 1970 1 jan - add 0
    // 1: 1971 1 jan - add (days in 1970 = 365)
    // 2: 1972 1 jan - add (days in 1970 and 1971 = 2*365)
    // 3: 1973 1 jan - add (days in 1970, 1971 and 1972:  2*365+366, 1972 is a leap)

    // Note: for 0:1970 we do not need to add anything, so we bypass this branch at all (we start with i=1)
    if (i==3)
      md_zero += 366LL; // 1973 (wee need to add a leap contribution of 1972)
    else
      md_zero += 365LL; // (this will be for 1971 and 1972).
  }

  // adjust based by the month
  Month mth = Month::jan;
  while (mth < mm) {
    md_zero +=  days_in_month(mth, yy); //adjust by preceding months
    ++mth; // increment the month
  }

  // adjust by the day. Don't forget to subtract -1 as we count from zero
  md_zero += dd-1;
}

const Date& default_date()
{
  //static Date dd {2001,Month::jan,1}; // start of 21st century
  // static Date dd {1970,Month::jan,1}; // zero date
  static Date dd {0}; // zero date
  return dd;
}

Date::Date(long int d) // basic constructor.
:md_zero{d}
{}

Date::Date()
:md_zero{0}
 {}

 int Date::year() const{
   int yr=0;
   Month m;
   int days;
   calendar(yr,m,days);
   return yr;
 }

 int Date::day() const{
   int yr=0;
   Month m;
   int day;
   calendar(yr,m,day);
   return day;
 }

 Month Date::month() const{
   int yr=0;
   Month m;
   int day;
   calendar(yr,m,day);
   return m;
 }

 void Date::calendar(int& yr, Month& m, int& day) const{
   // Extract year, month and day from the zero day representation of the Date

   // first adjust the year within 4 years
   const long int leap_cycle = 365*4+1; // =1461. If a user gives us a large number (multiple years), we can speed up the process by adding 4 years at a time.
   yr = 1970 + (md_zero/leap_cycle)*4;
   day = md_zero % leap_cycle;

   // this step is needed to support years before day zero (md_zero<0)
   if (day <0) {
     yr -=4;
     day += leap_cycle;
   }

   // The year to date transfer.
   // we need to add the following to adjust the full year
   // 0: 1970 1 jan - add 0
   // 1: 1971 1 jan - add (days in 1970 = 365)
   // 2: 1972 1 jan - add (days in 1970 and 1971 = 2*365)
   // 3: 1973 1 jan - add (days in 1970, 1971 and 1972:  2*365+366, 1972 is a leap)


   // To transfer back from zero_date to year
   // 1461 = leap_cycle; 0..1460
   // 0..364 (365 days total): 0 year 1970
   // 365..729 (730=2*365): 1 year 1971
   // 730..1095 (1096=2*365+366) : 2 year 1972 - leap year
   // 1096..1460 (1461=2*365+366+365) : 3 year 1973


   if(day >= 1096) { // 1096..1460 (1461=2*365+366+365) : 3 year 1973
     yr += 3;
     day -= 1096;
   } else if (day >= 730){ // 730..1095 (1096=2*365+366) : 2 year 1972 - leap year
     yr += 2;
     day -= 730;
   } else if (day >= 365) { // 365..729 (730=2*365): 1 year 1971
     yr += 1;
     day -= 365;
   } else {  // 0..364 (365 days total): 0 year 1970
     // yr += 0;
     // day -= 0;
   }
   // now yr is correct (year)

   m = Month::jan; // we start with January
   int d_month = days_in_month(m, yr);
   while (d_month <= day) {
     ++m; // increment the month
     day -= d_month;

     d_month = days_in_month(m, yr); // prepare for the next iteration
   }

   // at this point days are still numbered from zero
   ++day; // now the days is normalized.
 }

 void Date:: add_day(int n)
 {
   md_zero += n; // this is all that was needed
 }

 int Date:: days_in_month(const Month& mth, int year ) const // returns the number of days in a given month. We only use year for Month::feb to determine a leap year
 {
   int days_in_month = 31;  // most months have 31 days

   switch (mth) {
   case Month::feb:   // the length of February varies
     days_in_month = (leapyear(year))?29:28;
     break;
   case Month::apr: case Month::jun: case Month::sep: case Month::nov:
     days_in_month = 30;  // the rest have 30 days
     break;
   }
   return days_in_month;
 }

 void Date::add_month(int n)
 // If you add a month to 31 Jan you will get 28 or 29 Feb (depending on the leap year)
 {
   // convert from zero day format.
   int y=0;
   Month m;
   int d;
   calendar(y,m,d);

   int year = n/12;
   int num_month = n % 12; // this should be between 0 and 11

   if (num_month<0) { // support the negative n as well.
     year -=1; // year was already negative
     num_month += 12; // and now we adjusted num_month (num_month is positive) and the old code should work
   }

   // add the whole number of years (says if someone asks us to add 100 months)
   y += year;

   for (int i=0; i<num_month; i++) {
     ++m; // increment the month.
     if (m== Month::jan)
       ++y; // we wrapped into the next year.
   }

   int d_in_month = days_in_month(m, y ); // figure out the number of days in a month.

   if (d_in_month<d)
     d = d_in_month; // set the last of the month

   // convert back to zero day format:
   Date tmpD {y,m,d};
   md_zero = tmpD.zero_day(); // modify our own representation
 }


 void Date::add_year(int n) // If you add a year to the last day of Feb, you will get a last day of Feb (depending on the leap year it will be 28 or 29)
 {
   //if (m==Month::feb && d==29 && !leapyear(y+n)) { // beware of leap years!
   //  m = Month::mar;
   //}

   // convert from zero day format.
   int y=0;
   Month m;
   int d;
   calendar(y,m,d);

   // I think it would make more sense that if we are at the last day of February and we add a year, we are still at the last day of Februay
   if (m==Month::feb){
     if ( (leapyear(y) && d==29) || (!leapyear(y) && d==28) )  // if the last day of February
     {
       if (leapyear(y+n))
         d = 29;
       else
         d = 28;
     }
   }
   y+=n;

   // convert back to zero day format:
   Date tmpD {y,m,d};
   md_zero = tmpD.zero_day(); // modify our own representation
 }

 // helper functions:
 bool is_date(int y, Month m, int d)
 {
   // assume that y is valid

   if (d<=0) return false;  // d must be positive
   if (m<Month::jan || Month::dec<m) return false;

   int days_in_month = 31;  // most months have 31 days

   switch (m) {
   case Month::feb:   // the length of February varies
     days_in_month = (leapyear(y))?29:28;
     break;
   case Month::apr: case Month::jun: case Month::sep: case Month::nov:
     days_in_month = 30;  // the rest have 30 days
     break;
   }

   if (days_in_month<d) return false;

   return true;
 }

 bool leapyear(int y)
 {
   // see exercise 10
   if (y%4 == 0)
    return true;
   return false;
 }

 bool operator==(const Date& a, const Date& b)
 {
   return a.zero_day()==b.zero_day();
 }

 bool operator != (const Date& a, const Date& b)
 {
   return !(a==b);
 }

 ostream& operator << (ostream& os, const Date& date)
 {
   //return os << '(' << d.year()
   //    << ',' << d.month()
   //    << ',' << d.day() << ')';

   int y=0;
   Month m;
   int d;
   date.calendar(y,m,d);

   return os << '(' << y
          << ',' << m
          << ',' << d << ')';

 }

 istream & operator >> (istream& is, Date& dd)
 {
   int y, m, d;
   char ch1, ch2, ch3, ch4;
   is >> ch1>> y >> ch2 >> m >> ch3 >> d >> ch4;
   cout << "y = " << y<< endl;

   if (!is) return is;
   if (ch1!='(' || ch2!=',' || ch3!=',' || ch4!=')') {
     is.clear(ios_base::failbit);   // set the fail bit
     return is;
   }

   dd = Date(y,Month(m),d); // update dd

   return is;
 }

 ostream& operator <<(ostream& os, const Day& d){
   return os << day_tbl[int(d)];
 }

 Day int_to_Day(int x) // does boundary checking
 {
   if (x<int(Day::sunday) || int(Day::saturday)<x)
     error ("bad day conversion");
   return Day(x);
 }


 /*
 Day day_of_week(const Date& d) // will return the date of the week.
 {
   // 1 Jan 2000 was Saturday, want to start on a leap year
   const int base_year=2000; // want to start on a leap year
   int day_count = int(Day::saturday); // we will keep %7 representation of the day of the week

   // calculate the Day of the 1 Jan of the current year.
   int year_span = d.year()-base_year; // can be + or -
   int num_leap_years = year_span/4; // can be + or -
   // in a regular year 365 days, 365%7 = 1 day shift between the day of the week
   // in a leap year 366 days, 366%7 = 2 day shift between the day of the week.
   day_count += year_span + num_leap_years; // leap year represent an extra day shift. Formula uses the implied values of 1 and 2 days
   day_count %= 7; // it can still be a negative number at this point (spawned by values before the base_year)
   if (day_count < 0 )
     day_count += 7;  // make sure the value is positive.

   // Now adjust the day of the week within the current year:
   int adjust_by_month = 0; // based on the previous we need to adjust the count. Feb adjustment would only show up in March (or later)
   switch (d.month()){
   case Month::dec:
     // adjust by november length:
     adjust_by_month +=2; // november adjustment 30-28 days.
     // no break, as we want november and preceding months!
   case Month::nov:
     // adjust by october length
     adjust_by_month += 3; // october adjustment 31-28 days.
     // no break, as we want october and preceding months!
   case Month::oct:
     // adjust by september length:
     adjust_by_month +=2; // september adjustment 30-28 days.
     // no break, as we want september and preceding months!
   case Month::sep:
     // adjust by august length
     adjust_by_month += 3; // august adjustment 31-28 days.
     // no break, as we want august and preceding months!
   case Month::aug:
     // adjust by july length
     adjust_by_month += 3; // july adjustment 31-28 days.
     // no break, as we want july and preceding months!
   case Month::jul:
     // adjust by june length:
     adjust_by_month +=2; // june adjustment 30-28 days.
     // no break, as we want june and preceding months!
   case Month::jun:
     // adjust by may length
     adjust_by_month += 3; // may adjustment 31-28 days.
     // no break, as we want may and preceding months!
   case Month::may:
     // adjust by april length:
     adjust_by_month +=2; // april adjustment 30-28 days.
     // no break, as we want april and preceding months!
   case Month::apr:
     // adjust by march length
     adjust_by_month += 3; // march adjustment 31-28 days.
     // no break, as we want march and preceding months!
   case Month::mar:
     // adjust by february length
     if (leapyear(d.year()))
       adjust_by_month +=1; // february adjustment 29-28 days for leap year, 28-28 for regular year
     // no break, as we want february and preceding months!
   case Month::feb:
     // adjust by january length
     adjust_by_month +=3; // january adjustment 31-28 days.
     // no break here (to follow the logical flow), but we could (as for january, we do not adjust anything)
   case Month::jan:
     // adjust_by_month += 0; // no months before that.
     break;
   default:
     error ("Unexpected switch state");
     break;
   }

   day_count += adjust_by_month + (d.day() - 1); // adjust by months and by day (the year was already adjusted)
   day_count %= 7; // due to the nature of the calculation, at this point this value is >=0

   return int_to_Day(day_count);
 }
 // helper functions
 Date next_workday(const Date& d) // (assume that any day that is not a Saturday or a Sunday is a workday)
 {
   Date new_date(d); // make a copy of the current date;
   new_date.add_day(1); // this will give us the next day
   Day day = day_of_week(new_date);  // determine the day of the week
   while (day==Day::sunday || day == Day::saturday){
     new_date.add_day(1); // this will give us the next day
     day = day_of_week(new_date);  // determine the day of the week
   }
   return new_date;
 }
 int week_of_year(const Date& d) // (assume that week 1 is the week with January 1 in it and that the first day of a week is a Sunday)
 {
   int num_days_from_year_end = 0; // This is true for 1 Jan of any year, but we will adjust this later.
   // then we will calculate the number of days from d to the start of the years (7 days automatically give us one week increment)

   // Now adjust the number of days within the current year (each month - different month length. Also need to check leap year:
   int adjust_by_month = 0; // based on the previous we need to adjust the count. Feb adjustment would only show up in March (or later)
   switch (d.month()){
   case Month::dec:
     // adjust by november length:
     adjust_by_month +=30; // november adjustment 30-28 days.
     // no break, as we want november and preceding months!
   case Month::nov:
     // adjust by october length
     adjust_by_month +=31; // october adjustment 31-28 days.
     // no break, as we want october and preceding months!
   case Month::oct:
     // adjust by september length:
     adjust_by_month +=30; // september adjustment 30-28 days.
     // no break, as we want september and preceding months!
   case Month::sep:
     // adjust by august length
     adjust_by_month +=31; // august adjustment 31-28 days.
     // no break, as we want august and preceding months!
   case Month::aug:
     // adjust by july length
     adjust_by_month +=31; // july adjustment 31-28 days.
     // no break, as we want july and preceding months!
   case Month::jul:
     // adjust by june length:
     adjust_by_month +=30; // june adjustment 30-28 days.
     // no break, as we want june and preceding months!
   case Month::jun:
     // adjust by may length
     adjust_by_month +=31; // may adjustment 31-28 days.
     // no break, as we want may and preceding months!
   case Month::may:
     // adjust by april length:
     adjust_by_month +=30; // april adjustment 30-28 days.
     // no break, as we want april and preceding months!
   case Month::apr:
     // adjust by march length
     adjust_by_month +=31; // march adjustment 31-28 days.
     // no break, as we want march and preceding months!
   case Month::mar:
     // adjust by february length
     if (leapyear(d.year()))
       adjust_by_month +=29; // february adjustment 29-28 days for leap year, 28-28 for regular year
     else
       adjust_by_month +=28;
     // no break, as we want february and preceding months!
   case Month::feb:
     // adjust by january length
     adjust_by_month +=31; // january adjustment 31-28 days.
     // no break here (to follow the logical flow), but we could (as for january, we do not adjust anything)
   case Month::jan:
     // adjust_by_month += 0; // no months before that.
     break;
   default:
     error ("Unexpected switch state");
     break;
   }

   // then we will calculate the number of days from d to the start of the years (7 days automatically give us one week increment)
   num_days_from_year_end = adjust_by_month + (d.day()-1);

   //(7 days automatically give us one week increment)
   int week_num = 1 + num_days_from_year_end/7; // Remember, 1 Jan of the week, belongs to week 1 (the leading 1+)

   // Now we need to check up to 6 days (num_days_from_year_end%7) to see if they push us into a different week:
   Date first_of_year{d.year(),Chrono::Month::jan,1};
   if (int(day_of_week(first_of_year)) > int(day_of_week(d)))
     week_num +=1; // we did get into the new week

   return week_num;
 }

*/
} // Chrono




