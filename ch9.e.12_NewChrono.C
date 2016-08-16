// Ex 12: Change the representation of a Date to be the number of days sinse January 1, 1970 (known as day 0), represented as a long int,
/*
  re-implement the functions from $9.8. (Put in Chrono2.h) Be sure to reject dates outside the range we can represent that way (feel free to reject days before day 0,
  i.e, no negative days.
 */

// Ex 11: Design and implement a set of useful helper functions for the Date class with functions such as
/*
 next_workday() (assume that any day that is not a Saturday or a Sunday is a workday) and
 week_of_year() (assume that week 1 is the week with January 1 in it and that the first day of a week is a Sunday)
 */
// Ex 10: Implement leap year from $9.8 (Chrono.h)
// g++ -std=c++11 -g -o ch9.e.12_NewChrono.exe ch9.e.12_NewChrono.C Chrono2.C  2>&1 | tee tmp.txt
 
#include "std_lib_facilities.h"

#include "Chrono2.h"


int main ()
{

  Chrono2::Month mm {Chrono2::Month::jan};
  cout << "mm = " << mm << endl;

  Chrono2::Date date_Zero {0};
  Chrono2::Date date_One {1};
  Chrono2::Date date_Two {2};
  Chrono2::Date date_NegOne {-1};

  Chrono2::Date date_Zero_F {1970,Chrono2::Month::jan,1};
  Chrono2::Date date_Zero_F_Year1 {1971,Chrono2::Month::jan,1};
  Chrono2::Date date_Zero_F_Year2 {1972,Chrono2::Month::jan,1};
  Chrono2::Date date_Zero_F_Year3 {1973,Chrono2::Month::jan,1};
  Chrono2::Date date_Zero_F_Year4 {1974,Chrono2::Month::jan,1};
  Chrono2::Date date_Zero_F_Year5 {1975,Chrono2::Month::jan,1};

  Chrono2::Date date_Zero_Z_Year1(date_Zero);
  date_Zero_Z_Year1.add_year(1);

  Chrono2::Date date_Zero_Z_Year2(date_Zero);
  date_Zero_Z_Year2.add_year(2);

  Chrono2::Date date_Zero_Z_Year3(date_Zero);
  date_Zero_Z_Year3.add_year(3);

  Chrono2::Date date_Zero_Z_Year4(date_Zero);
  date_Zero_Z_Year4.add_year(4);

  Chrono2::Date date_Zero_Z_Year5(date_Zero);
  date_Zero_Z_Year5.add_year(5);

  Chrono2::Date today {2015,Chrono2::Month::dec,30};
  Chrono2::Date date_A {2013,Chrono2::Month::nov,9};
  Chrono2::Date date_B {2013,Chrono2::Month::jan,31};
  Chrono2::Date date_C1 {2016,Chrono2::Month::jan,1};
  Chrono2::Date date_C2 {2016,Chrono2::Month::jan,2};
  Chrono2::Date date_C3 {2016,Chrono2::Month::jan,3};
  Chrono2::Date date_C4 {2016,Chrono2::Month::jan,4};
  Chrono2::Date date_C5 {2016,Chrono2::Month::jan,5};
  Chrono2::Date date_C6 {2016,Chrono2::Month::jan,6};
  Chrono2::Date date_C7 {2016,Chrono2::Month::jan,7};
  Chrono2::Date date_C8 {2016,Chrono2::Month::jan,8};
  Chrono2::Date date_C29 {2016,Chrono2::Month::jan,29};
  Chrono2::Date date_C30 {2016,Chrono2::Month::jan,30};
  Chrono2::Date date_C31 {2016,Chrono2::Month::jan,31};
  Chrono2::Date date_CF1 {2016,Chrono2::Month::feb,29}; // this is ok, as a leap year
  Chrono2::Date date_CF2 {2016,Chrono2::Month::feb,28}; // this is ok, as a leap year

  Chrono2::Date date_D1 {2017,Chrono2::Month::jan,1};
  //Chrono2::Date date_DF1 {2017,Chrono2::Month::feb,29}; // error: not a leap year!, 29 Feb does not exist

  Chrono2::Date date_E1 {2017,Chrono2::Month::dec,1};

  cout << "Date date_Zero = " << date_Zero << endl;
  cout << "Date date_One = " << date_One << endl;
  cout << "Date date_Two = " << date_Two << endl;
  cout << "Date date_NegOne = " << date_NegOne << endl;

  cout << "Date date_Zero_F = " << date_Zero_F << ", int repr =" << date_Zero_F.zero_day()<< endl;
  cout << "Date date_Zero_F_Year1 = " << date_Zero_F_Year1 << ", int repr =" << date_Zero_F_Year1.zero_day()<< endl;
  cout << "Date date_Zero_F_Year2 = " << date_Zero_F_Year2 << ", int repr =" << date_Zero_F_Year2.zero_day()<< endl;
  cout << "Date date_Zero_F_Year3 = " << date_Zero_F_Year3 << ", int repr =" << date_Zero_F_Year3.zero_day()<< endl;
  cout << "Date date_Zero_F_Year4 = " << date_Zero_F_Year4 << ", int repr =" << date_Zero_F_Year4.zero_day()<< endl;
  cout << "Date date_Zero_F_Year5 = " << date_Zero_F_Year5 << ", int repr =" << date_Zero_F_Year5.zero_day()<< endl;

  cout << "Date today = " << today << ", int repr =" << today.zero_day()<< endl;
  cout << "Date date_A = " << date_A << endl;
  cout << "Date date_B = " << date_B << endl;
  cout << "Date date_C1 = " << date_C1 << endl;
  cout << "Date date_C2 = " << date_C2 << endl;

  cout << "\nTesting new functions:\n";

  // vector<Chrono2::Date> testDates = {today, date_A, date_B, date_C1, date_C2,date_C3,date_C4,date_C5,date_C6,date_C7,date_C8}; // we will test these dates
  // vector<Chrono2::Date> testDates = {date_C1}; // we will test these dates
  // vector<Chrono2::Date> testDates = {date_C2}; // we will test these dates
  // vector<Chrono2::Date> testDates = {date_C1, date_C2}; // we will test these dates
  // vector<Chrono2::Date> testDates = {date_C1, date_D1}; // we will test these dates
  // vector<Chrono2::Date> testDates = {date_C1,date_E1};
  // vector<Chrono2::Date> testDates = {date_C1,date_E1,date_C29,date_C30,date_C31,date_CF2,date_CF1};
  // vector<Chrono2::Date> testDates = {date_CF1}; // we will test these dates There was a problem with add_month for this day. After a year, it went to 28 for all the months
  // vector<Chrono2::Date> testDates = {date_C1, date_C2,date_C3,date_C4,date_C5,date_C6,date_C7,date_C8}; // we will test these dates
   vector<Chrono2::Date> testDates = {date_C1, date_C2,date_C3,date_C4,date_C5,date_C6,date_C7,date_C8,date_D1,date_E1,date_C29,date_C30,date_C31,date_CF2,date_CF1}; // we will test these dates


/*
  // you might want to use the following set:
  //vector<Chrono2::Date> testDates = {date_C1,date_E1,date_C29,date_C30,date_C31,date_CF2,date_CF1};
  //vector<Chrono2::Date> testDates = {date_Zero, date_Zero_Z_Year1, date_Zero_F, date_Zero_F_Year1,date_Zero_F_Year2,date_Zero_F_Year3,date_Zero_F_Year4,date_Zero_F_Year5, date_C1};
  vector<Chrono2::Date> testDates = {date_Zero, date_Zero_F, date_Zero_F_Year1,date_Zero_F_Year2,date_Zero_F_Year3,date_Zero_F_Year4,date_Zero_F_Year5, date_C1};

  Chrono2::Date test_date;
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
      cout  << "\t add_month(" <<i<<") = " << test_date << ", int repr =" << test_date.zero_day()<< endl;
    }

    // test year
    for (int i=-9; i<9; i++) {
      test_date  = date;
      test_date.add_year(i);
      cout  << "\t add_year(" <<i<<") = " << test_date << ", int repr =" << test_date.zero_day()<< endl;
    }


//    // test add_month
  //  for (int i=-1; i<2; i++) {
  //    test_date  = date;
  //    test_date.add_month(i);
  //    cout  << "\t add_month(" <<i<<") = " << test_date << ", int repr =" << test_date.zero_day()<< endl;
  //  }

  }
*/


  for (auto date:testDates){
    cout << "Date " << date << endl;
    cout << "\t is week number " << week_of_year(date) << endl;
    cout << "\t day of the week " << day_of_week(date) << endl;
    cout << "\t Next work day " << next_workday(date) << endl;
    for (int i=0; i<57; i++){
      Chrono2::Date test_date(date);
      test_date.add_day(i*7); // want to skip by one week;
      cout << "Date " << test_date << endl;
      cout << "\t is week number " << week_of_year(test_date) << endl;
      cout << "\t day of the week " << day_of_week(test_date) << endl;
      cout << "\t Next work day " << next_workday(test_date) << endl;
    }
    cout << endl;

  }


  cout << "Test complete!\n";

  return 0;
}


