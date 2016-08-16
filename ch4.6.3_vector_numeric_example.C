// Compute mean and median temperatures
// g++ -std=c++11 -g -o ch4.6.3_vector_numeric_example.exe ch4.6.3_vector_numeric_example.C  2>&1 | tee tmp.txt

//#include "std_lib_facilities.h"
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

template<typename C>
  // requires Container<C>()
void sort(C& c)
{
  std::sort(c.begin(), c.end());
}


int main ()
{
  vector <double> temps; // temperatures
  cout << "Please enter temperatures:\n";
  for (double temp; cin >> temp;) // read into temp
    temps.push_back(temp);  // put temp into vector


  // compute mean temperature
  double sum = 0.0;
  for (double x:temps) sum += x;
  cout << "Average temperature:" << sum/temps.size() << endl;

  // compute median temperature:
  sort (temps);
  int size = temps.size();
  double median; // will put the median value in there
  if (size & 1) {
    // odd size, so the value in the middle will be median: [0 1 2]. 1 = 3/2
    median = temps[size/2];
  } else {
    // even size, so we average two values that are in the middle: [0 1 2 3] => (1+2)/2 =1.5
    median = (temps[size/2] + temps[size/2 - 1]) / 2.0;
  }
  cout << "Median temperature: " << median << endl;


  return 0;
}


