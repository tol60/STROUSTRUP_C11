//
/* E4. Modify the store_temps program form Excerciser 2 to include a temperature suffix c for Celsius or f for Fahrenheit temperatures.
 *   Then modify the temp_stats program to test each temperature, converting the Celcius reading to Fahrenheit before putting them onto the vector.
 * E3. Write a program that reads the data from raw_temps.txt created in the exercise 2 into a vector and then
 *    calculates the mean and median temperatures in your data set.
 *    Call this program temp_stats
 * E2. Write a program that creates a file of data in the form of the temperature Reading type defined in 10.5.
 *   For testing, fill the  file with at least 50 "temperature readings". Call this program store_temps and the file it creates raw_temps.txt
 */
// g++ -std=c++11 -g ch10.e.4_temp_stats_C_F.C  -o ch10.e.4_temp_stats_C_F.exe 2>&1 | tee tmp.txt

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
  ifstream ist {fname};
  if(!ist) error ("can not open output file ",fname);

  vector<Reading> readings;
  vector <double> temps; // we will use this to sort temperatures to find the median later

  // read the file
  for (Reading r; ist>>r; ){

    if (r.ts == TempSys::c){ // if Celcius, convirt to Fahrenheight first
      r.temperature = 1.8*r.temperature + 32.0;
      r.ts = TempSys::f; // to be consistent
    }
    readings.push_back(r);
    temps.push_back(r.temperature);
  }
  int num_points = readings.size();


  // Stream states (cin.good) or (cin)
  // good() The operation succedded.
  // eof()  We hit end of input ("end of file").
  // fail() Something unexpected happened (we looked for a digit and found 'x')
  // bad()  Something unexpected and serious happened (e.g., a disk read error)
  if (ist) error ("At this point input stream can not bee in a good state");

  if (!ist) { // we get here (only) if the an input operation failed
    if (ist.bad()) error ("ist is bad"); // stream corrupted: let's get out of here!
    if (ist.eof()) {
      // no more input
      // this is often how we want a sequence of input operations to end
      if (!num_points) error ("The file was empty! No entries were read!");
    }
  }

  // find the Mean
  double sum=0.0;
  for (double d:temps){
    sum +=d;
  }
  double dMean = sum/num_points;

  // find the Median
  double dMedian = 0;
  std::sort(temps.begin(),temps.end()); // name is sorted now

  int indx = num_points/2; // integer division, 3/2 should return 1
  // 0 ; num_points = 1; ind = num_points/2 = 0;
  // 0 1; num points = 2; ind = num_points/2 = 1
  // 0 1 2; num_points = 3, ind = num_points/2 = 1
  // 0 1 2 3; num_points = 4, ind = num_points/2 = 2

  if (num_points%2){
    // odd number of points:
    // 0 ; num_points = 1; ind = num_points/2 = 0;
    // 0 1 2; num_points = 3, ind = num_points/2 = 1
    dMedian = temps[indx]; // integer division, 3/2 should return 1
  } else {
    // enven number of points 0 1 2 3 (need to find the average of values in 1 and 2)
    // 0 1; num points = 2; ind = num_points/2 = 1, dMedian = (v[1] + v[0])/2.0
    // 0 1 2 3; num_points = 4, ind = num_points/2 = 2, dMedian = (v[2] + v[1])/2.0
    dMedian = (temps[indx] + temps[indx-1])/2.0;
  }
  cout << "We read "<< num_points << " measurements" << endl;
  cout << "Mean temperature = " << dMean << endl;
  cout << "Median temperature = " << dMedian << endl;

  return 0;
}


