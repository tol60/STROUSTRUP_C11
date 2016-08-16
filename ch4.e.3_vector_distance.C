// Compute mean distance between multiple cities
// g++ -std=c++11 -g -o ch4.e.3_vector_distance.exe ch4.e.3_vector_distance.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

int main ()
{
  vector <double> temps; // temperatures
  cout << "Please enter distances between the cities:\n";
  for (double temp; cin >> temp;) // read into temp
    temps.push_back(temp);  // put temp into vector

  // compute mean temperature
  double sum = 0.0;
  for (double x:temps) sum += x;
  cout << "The total distance:" << sum << endl;
  cout << "The mean distance between the two cities = " << sum/ temps.size() << endl;

  sort (temps);
  cout << "The smallest distance is " <<temps[0] << endl;  // as vector is sorted, should give min
  cout << "The largest distance is " <<temps[temps.size()-1] << endl; // as vector is sorted, should give max

  return 0;
}


