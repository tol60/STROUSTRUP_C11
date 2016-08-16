// Enter the first name and age (in years)
// g++ -std=c++11 -g -o ch3.3_name_age.exe ch3.3_name_age.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"
int main ()
{
  cout << "Please enter your first name and age (years)\n";
  string first_name = "???";
  double age = -1.0;
  cin >> first_name >> age; // read string followed by an integer
  age = age * 12; // convert into months
  cout << "Hallo, " << first_name << " (age " << age <<" months)\n";
  return 0;
}
