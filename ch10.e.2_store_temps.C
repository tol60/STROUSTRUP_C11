//
/* Write a program that creates a file of data in the form of the temperature Reading type defined in 10.5.
 *   For testing, fill the  file with at least 50 "temperature readings". Call this program store_temps and the file it creates raw_temps.txt
 */
// g++ -std=c++11 -g ch10.e.2_store_temps.C  -o ch10.e.2_store_temps.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

struct Reading {      // a temperature reading
  int hour;           // hour after midnight
  double temperature; // in Fahrenhight
  Reading (): hour{0}, temperature{0.0} {}
};

ostream& operator<< (ostream& ost, const Reading & r){
  return ost<<r.hour << " " << r.temperature;
}

int main ()
{
  string fname = "raw_temps.txt";
  ofstream ost {fname};
  if(!ost) error ("can not open output file ",fname);

  Reading r;
  for (int i=0; i<50; ++i){
    r.hour = i;
    r.temperature = 10.1*i;
    ost << r << endl;
  }

  return 0;
}


