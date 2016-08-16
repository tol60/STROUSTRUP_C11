// Try to fix the problem that find min, max and average
// g++ -std=c++11 -g -o ch5.7_logic_errors.exe ch5.7_logic_errors.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

int main ()
{
  vector <double> temps; // temperatures
  cout << "Please enber a couple of temperatures\n";
  for (double temp; cin>>temp;)
    temps.push_back(temp);

  double sum = 0.0;
  double high_temp = temps[0];
  double low_temp = temps[0];

  for (double x: temps) {
    if (x>high_temp) high_temp = x; // find high
    if (x<low_temp) low_temp = x; // find low
    sum += x;
  }

  cout << "High temperature: " << high_temp << endl;
  cout << "Low temperature: " << low_temp << endl;
  cout << "Average temperature: " << sum/temps.size() << endl;
  return 0;
}


