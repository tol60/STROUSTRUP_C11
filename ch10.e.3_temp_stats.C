//
/* E3. Write a program that reads the data from raw_temps.txt created in the exercise 2 into a vector and then
 *    calculates the mean and median temperatures in your data set.
 *    Call this program temp_stats
 * E2. Write a program that creates a file of data in the form of the temperature Reading type defined in 10.5.
 *   For testing, fill the  file with at least 50 "temperature readings". Call this program store_temps and the file it creates raw_temps.txt
 */
// g++ -std=c++11 -g ch10.e.3_temp_stats.C  -o ch10.e.3_temp_stats.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

struct Reading {      // a temperature reading
  int hour;           // hour after midnight
  double temperature; // in Fahrenhight
  Reading (): hour{0}, temperature{0.0} {}
  Reading (int h, double temp): hour{h}, temperature{temp} {}
};

ostream& operator<< (ostream& ost, const Reading & r){
  return ost<<r.hour << " " << r.temperature;
}

istream & operator>> (istream & is, Reading &r){
     int hour;
     double temp;
     is >> hour >> temp;

     if (!is) return is;

      r= Reading(hour,temp); // update Point p

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


