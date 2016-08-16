/*
 * Chrono.C
 * Class to represent Date
 */

#include "Chrono.h"

namespace Chrono{

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
:y{yy},m{mm},d{dd}
{
  if (!is_date(yy,mm,dd)) throw Invalid{};
}

const Date& default_date()
{
  static Date dd {2001,Month::jan,1}; // start of 21st century
  return dd;
}

Date::Date()
:y{default_date().year()},
 m{default_date().month()},
 d{default_date().day()}
 {
 }

 void Date:: add_day(int n)
 {
   // once every 4 years we have a leap year (366 days), vs the normal 365 days.
   const int leap_cycle = 365*4+1; // If a user gives us a large number (multiple years), we can speed up the process by adding 4 years at a time.
   int year_incr = ( n/leap_cycle) *4; // how many ears to increment (4 years in a leap cycle
   n %= leap_cycle; // the remaining number is guaranteed to be less then 4 years.

   // add support for negative n:
   if (n<0) {
     year_incr -= 4; // subtract extra 4 years
     n += leap_cycle; // now n is positive. And we can use the old code.
   }

   add_year( year_incr); // add this big chunk (or zero)

   int cur_month_length = days_in_month(m,y); // will give the number of days in a given month

   if (cur_month_length - d >= n) // do we stay within a given month?
   {
     // we do stay within the current month, we just change the date
     d += n;
     return;
   } else {
     // first go to the beginning of the next month:
     ++m; // next month
     if (m==Month::jan)  // check if we wrapped into a new year
       y++;
     n -= (cur_month_length - d + 1); // this is what we used up from the previous month
           // note that if we start on the last of the month, d = cur_month_lenght, and we are using one day when we skip 31 Jan -> 1 Feb
     d=1; // beginning of the month

     cur_month_length = days_in_month(m,y); // will give the number of days in a given month
     while (cur_month_length - d < n){  // we can increment the full month. 1 Jan -> 1 Feb -> 1 Mar->...
       n -= cur_month_length;

       //  go to the next month: 1 Jan -> 1 Feb -> 1 Mar->...
       ++m; // next month
       if (m==Month::jan)  // check if we wrapped into a new year
         y++;

       cur_month_length = days_in_month(m,y); // prepare for the next iteration
     }

     // once we are here, the remaining n should be small enough to keep us within a given month.
     // d =1
     d+= n;
   }

 }

 int Date:: days_in_month(const Month& mth, int year ) // returns the number of days in a given month. We only use year for Month::feb to determine a leap year
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

   int year = n/12;
   int num_month = n % 12; // this should be between 0 and 11

   if (num_month<0) { // support the negative n as well.
     year -=1; // year was already negative
     num_month += 12; // and now we adjusted num_month (num_month is positive) and the old code should work
   }

   int original_day = d; // need to save it, otherwise add_year can modify for 29 Feb
   add_year(year); // this should add the whole number of years (or subtract). Possible side-effect - modifies 29Feb.
   d = original_day; // This step was only required for Feb 29.

   for (int i=0; i<num_month; i++) {
     ++m; // increment the month.
     if (m== Month::jan)
       ++y; // we wrapped into the next year.
   }

   int days_in_month = 31;  // most months have 31 days

   switch (m) {
   case Month::feb:   // the length of February varies
     days_in_month = (leapyear(y))?29:28;
     break;
   case Month::apr: case Month::jun: case Month::sep: case Month::nov:
     days_in_month = 30;  // the rest have 30 days
     break;
   }

   if (days_in_month<d)
     d = days_in_month; // set the last of the month
 }

 void Date::add_year(int n) // If you add a year to the last day of Feb, you will get a last day of Feb (depending on the leap year it will be 28 or 29)
 {
   //if (m==Month::feb && d==29 && !leapyear(y+n)) { // beware of leap years!
   //  m = Month::mar;
   //}

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
   return a.year()==b.year()
       && a.month()==b.month()
       && a.day()==b.day();
 }

 bool operator != (const Date& a, const Date& b)
 {
   return !(a==b);
 }

 ostream& operator << (ostream& os, const Date& d)
 {
   return os << '(' << d.year()
       << ',' << d.month()
       << ',' << d.day() << ')';
 }

 istream & operator >> (istream& is, Date& dd)
 {
   int y, m, d;
   char ch1, ch2, ch3, ch4;
   is >> ch1>> y >> ch2 >> m >> ch3 >> d >> ch4;
   //cout << "y = " << y<< endl;

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


} // Chrono




