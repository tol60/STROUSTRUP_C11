// Convert Celcius to Kelvin
// g++ -std=c++11 -g -o ch5.e.2_celsius2K_error_main.exe ch5.e.2_celsius2K_error_main.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

constexpr double abs_zero = -273.15;

double ctok(double c)
{
  double k = c - abs_zero;
  return k;
}

int main ()
{
  double c = 0;
  cout << "Please enter the temperature in Celcius to be converted to Kelvin:\n";
  if (cin >> c) {
    cout << "You entered " << c << " degrees Celcius\n";
    if (c< abs_zero) {
      cout << "Error detected: the input temperature can not be below absolute zero "
          << abs_zero <<". Terminating\n";
    } else {
      double k = ctok(c);
      cout << "Is equivalent to "<< k << " degrees Kelvin\n";
    }
  } else {
    cout << "You input was not recognized\n";
  }
  return 0;
}


