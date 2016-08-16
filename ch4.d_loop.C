// Inpurt a text an do simple manipulations
// g++ -std=c++11 -g -o ch4.d_loop.exe ch4.d_loop.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

int main ()
{
  cout << "Please enter distances as a floating point number and a unit (cm, m, in, ft):\n";
  double n1, min{0.0}, max{0.0};
  double sum{0.0};
  int num_entries{0};
  vector <double> elements; // keep all the elements (m)
  constexpr double in2cm_factor = 2.54; // in to cm
  constexpr double ft2in_factor = 12.0; // ft to in
  constexpr double ft2cm_factor = in2cm_factor * ft2in_factor; // ft to cm
  constexpr double m2cm_factor = 100.0; // m to cm
  string unit{""};
  bool first_iter = true;
  while (cin >> n1 >> unit) {
    bool error_flag = false;
    cout << "You entered: "<< n1 << unit;

    // convert all the units to cm
    if (unit== "cm") {
      // n1 = n1; // do not need extra conversion
    } else if (unit== "in") {
      n1 = n1 * in2cm_factor;
    } else if (unit== "ft") {
      n1 = n1 * ft2cm_factor;
    } else if (unit== "m") {
      n1 = n1 * m2cm_factor;
    } else {
      cout << " The unit " << unit <<" was not recognized\n";
      error_flag = true;
    }

    // convert to meters
    n1 = n1 / m2cm_factor;

    // if we did not recognize the unit, skip modifications.
    if (! error_flag) {
      if (first_iter) {
        min = max = n1;
        first_iter = false;
        cout << "\nThe first iteration. Setting min = "<< min << ", max = " << max << endl;
      } else {
        if (n1 < min){
          cout << ". The smallest value so far.";
          min = n1;
        } else if (n1 > max){
          cout << ". The largest value so far.";
          max = n1;
        }
        cout << endl;
      }

      sum += n1; // keep track of the sum entered so far
      ++num_entries; // keep track of the number of values entered.
      elements.push_back(n1);
    }
  }

  cout << "\nTotals:\n";
  cout << "The smallest value = " << min << "m\n";
  cout << "The largest value = " << max << "m\n";
  cout << "You entered " << num_entries << " values\n";
  cout << "The sum = "<< sum << "m\n";

  sort(elements);

  // print the elements
  for (int i=0; i<elements.size(); ++i ) {
    cout << "Element[" << i << "] = " << elements[i] << "m\n";
  }
  return 0;
}


