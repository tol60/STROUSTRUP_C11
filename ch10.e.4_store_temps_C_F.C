//
/* E4. Modify the store_temps programe form Excerciser 2 to include a temperature suffix c for Celsius or f for Fahrenheit temperatures.
 *   Then modify the temp_stats program to test each temperature, converting the Celcius reading to Fahrenheit before putting them onto the vector.
 * E2. Write a program that creates a file of data in the form of the temperature Reading type defined in 10.5.
 *   For testing, fill the  file with at least 50 "temperature readings". Call this program store_temps and the file it creates raw_temps.txt
 */
// g++ -std=c++11 -g ch10.e.4_store_temps_C_F.C  -o ch10.e.4_store_temps_C_F.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"


enum class TempSys {
  c, // Celsius
  f // Farenhight
};
const vector <char> TempSys_tbl = {'C','F'}; // we use the fact that the table only contains capitals in the input operator
ostream& operator <<(ostream& os, const TempSys& sys){
  return os << TempSys_tbl[int(sys)];
  //return os << int(m);
}

istream& operator>> (istream& is, TempSys& sys) {
  char ch;
  is >> ch;
  if (!is) return is;

  // find the system symbol in the table
  for (int i=0; i<TempSys_tbl.size(); ++i){
    if ( toupper(ch)== toupper(TempSys_tbl[i]) ) {
      sys = TempSys(i);
      return is;
    }
  }

  // if we got to this point, it means we did not recognize the temperature designator
  is.clear(ios_base::failbit);   // set the fail bit
  return is;
}

struct Reading {      // a temperature reading
  int hour;           // hour after midnight
  double temperature; // in Fahrenhight
  TempSys ts; // temperature system (Celsius/Farenhight)
  Reading (): hour{0}, temperature{0.0}, ts{TempSys::c} {}
  Reading (int h, double temp, TempSys sys): hour{h}, temperature{temp}, ts{sys} {}
};

ostream& operator<< (ostream& ost, const Reading & r){
  // 23 45.6F
  return ost<<r.hour << " " << r.temperature << r.ts;
}

istream & operator>> (istream & is, Reading &r){
     int hour;
     double temp;
     TempSys sys;
     is >> hour >> temp >> sys;

     if (!is) return is;

      r= Reading(hour,temp, sys); // update Point p

     return is;
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
    if (i%3 == 0)
      r.ts = TempSys::c; // Celcius 1 out of 3
    else
      r.ts = TempSys::f; // Farenhite 2 out of 3

    ost << r << endl;
  }

  return 0;
}


