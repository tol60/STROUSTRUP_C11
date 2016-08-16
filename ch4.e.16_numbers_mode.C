// Find the mode = the number that appears most times
// g++ -std=c++11 -g -o ch4.e.16_numbers_mode.exe ch4.e.16_numbers_mode.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

int main ()
{
  vector <double> temps; // temperatures
  cout << "Please enter a distances between two cities:\n";
  for (double temp; cin >> temp;) // read into temp
    temps.push_back(temp);  // put temp into vector

  sort (temps);
  cout << "The smallest distance is " <<temps[0] << endl;  // as vector is sorted, should give min
  cout << "The largest distance is " <<temps[temps.size()-1] << endl; // as vector is sorted, should give max

  double mode{temps[0]};  // we assume this is the mode
  int mode_count{1}; // how many times we encountered the mode.

  // the candidate  -- implicit, but need to keep track of the count
  int cand_count{1}; // the current count for a candidate

  // as the vector is sorted, we can just check consecutive entries, increment the counts
  // we initialized with temps[0], so need to start with 1
  for (int i=1; i<temps.size(); ++i) {
    if (temps[i-1]==temps[i]){
      // the same number repeats. Increment the candidate count
      ++cand_count;
      if (cand_count > mode_count) {
        // we have a new winner.
        mode = temps[i]; //mode = cand;
        mode_count = cand_count;
      }
    } else {
      // we got a new number. Set it as a new candidate (we only track the count)
      cand_count = 1;  // as we detected a new number, it shows up at least once
    }
  }

  cout << "The mode (the number that appears most times) is " << mode << " and it appeared " << mode_count << " times\n";
  return 0;
}


