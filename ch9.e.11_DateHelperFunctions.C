// Ex 11: Design and implement a set of useful helper functions for the Date class with functions such as
/*
 next_workday() (assume that any day that is not a Saturday or a Sunday is a workday) and
 week_of_year() (assume that week 1 is the week with January 1 in it and that the first day of a week is a Sunday)
 */
// Ex 10: Implement leap year from $9.8 (Chrono.h)
// g++ -std=c++11 -g -o ch9.e.11_DateHelperFunctions.exe ch9.e.11_DateHelperFunctions.C Chrono.C  2>&1 | tee tmp.txt
 
#include "std_lib_facilities.h"

#include "Chrono.h"


int main ()
{

  Chrono::Month mm {Chrono::Month::jan};
  cout << "mm = " << mm << endl;
  Chrono::Date today {2015,Chrono::Month::dec,30};
  Chrono::Date date_A {2013,Chrono::Month::nov,9};
  Chrono::Date date_B {2013,Chrono::Month::jan,31};
  Chrono::Date date_C1 {2016,Chrono::Month::jan,1};
  Chrono::Date date_C2 {2016,Chrono::Month::jan,2};
  Chrono::Date date_C3 {2016,Chrono::Month::jan,3};
  Chrono::Date date_C4 {2016,Chrono::Month::jan,4};
  Chrono::Date date_C5 {2016,Chrono::Month::jan,5};
  Chrono::Date date_C6 {2016,Chrono::Month::jan,6};
  Chrono::Date date_C7 {2016,Chrono::Month::jan,7};
  Chrono::Date date_C8 {2016,Chrono::Month::jan,8};
  Chrono::Date date_C29 {2016,Chrono::Month::jan,29};
  Chrono::Date date_C30 {2016,Chrono::Month::jan,30};
  Chrono::Date date_C31 {2016,Chrono::Month::jan,31};
  Chrono::Date date_CF1 {2016,Chrono::Month::feb,29}; // this is ok, as a leap year
  Chrono::Date date_CF2 {2016,Chrono::Month::feb,28}; // this is ok, as a leap year

  Chrono::Date date_D1 {2017,Chrono::Month::jan,1};
  //Chrono::Date date_DF1 {2017,Chrono::Month::feb,29}; // error: not a leap year!, 29 Feb does not exist

  Chrono::Date date_E1 {2017,Chrono::Month::dec,1};


  cout << "Date today = " << today << endl;
  cout << "Date date_A = " << date_A << endl;
  cout << "Date date_B = " << date_B << endl;
  cout << "Date date_C1 = " << date_C1 << endl;
  cout << "Date date_C2 = " << date_C2 << endl;

  cout << "\nTesting new functions:\n";

  // vector<Chrono::Date> testDates = {today, date_A, date_B, date_C1, date_C2,date_C3,date_C4,date_C5,date_C6,date_C7,date_C8}; // we will test these dates
  // vector<Chrono::Date> testDates = {date_C1}; // we will test these dates
  // vector<Chrono::Date> testDates = {date_C2}; // we will test these dates
  // vector<Chrono::Date> testDates = {date_C1, date_C2}; // we will test these dates
  // vector<Chrono::Date> testDates = {date_C1, date_D1}; // we will test these dates
  // vector<Chrono::Date> testDates = {date_C1,date_E1};
  // vector<Chrono::Date> testDates = {date_C1,date_E1,date_C29,date_C30,date_C31,date_CF2,date_CF1};
  // vector<Chrono::Date> testDates = {date_CF1}; // we will test these dates There was a problem with add_month for this day. After a year, it went to 28 for all the months
  // vector<Chrono::Date> testDates = {date_C1, date_C2,date_C3,date_C4,date_C5,date_C6,date_C7,date_C8}; // we will test these dates
  // vector<Chrono::Date> testDates = {date_C1, date_C2,date_C3,date_C4,date_C5,date_C6,date_C7,date_C8,date_D1,date_E1,date_C29,date_C30,date_C31,date_CF2,date_CF1}; // we will test these dates


  // you might want to use the following set:
  // vector<Chrono::Date> testDates = {date_C1,date_E1,date_C29,date_C30,date_C31,date_CF2,date_CF1};
  vector<Chrono::Date> testDates = {date_C1};
  Chrono::Date test_date;
  for (auto date:testDates){
    cout << "Date " << date << endl;
    // test add_day
    for (int i=-64; i<64; i++) {
      test_date  = date;
      test_date.add_day(i);
      cout  << "\t add_day(" <<i<<") = " << test_date << endl;
    }

    // test add_month
    for (int i=-13; i<25; i++) {
      test_date  = date;
      test_date.add_month(i);
      cout  << "\t add_month(" <<i<<") = " << test_date << endl;
    }

    // test year
    for (int i=-9; i<9; i++) {
      test_date  = date;
      test_date.add_year(i);
      cout  << "\t add_year(" <<i<<") = " << test_date << endl;
    }
  }



  for (auto date:testDates){
    cout << "Date " << date << endl;
    cout << "\t is week number " << week_of_year(date) << endl;
    cout << "\t day of the week " << day_of_week(date) << endl;
    cout << "\t Next work day " << next_workday(date) << endl;
    for (int i=0; i<57; i++){
      Chrono::Date test_date(date);
      test_date.add_day(i*7); // want to skip by one week;
      cout << "Date " << test_date << endl;
      cout << "\t is week number " << week_of_year(test_date) << endl;
      cout << "\t day of the week " << day_of_week(test_date) << endl;
      cout << "\t Next work day " << next_workday(test_date) << endl;
    }
    cout << endl;

  }

  Chrono::Date date = {1970,Chrono::Month::jan,1};
  cout << "Date " << date << endl;
  cout << "\t is week number " << week_of_year(date) << endl;
  cout << "\t day of the week " << day_of_week(date) << endl;
  cout << "\t Next work day " << next_workday(date) << endl;

  cout << "Test complete!\n";

  return 0;
}


