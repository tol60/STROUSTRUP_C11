// Convert yen, euros and pounds into dollars
// g++ -std=c++11 -g -o ch4.4.1.1_selection_if_currency_conv.exe ch4.4.1.1_selection_if_currency_conv.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"
int main ()
{
  constexpr double yen_per_dollar = 120.25;
  constexpr double euro_per_dollar = 0.89;
  constexpr double pound_per_dollar = 0.66;
  cout << "Please enter the amount in (yen, eurous or pounds) you want to convert inot dollars.\n";
  cout << "Example: enter 35y\n";
  double amount = 0.0;
  char unit = 0;
  cin >> amount >> unit;
  if (unit == 'y') {
    cout << amount << " yen == " << amount * yen_per_dollar << " dollars."<< endl;
  } else if (unit == 'e') {
    cout << amount << " euros == " << amount * euro_per_dollar << " dollars." << endl;
  }  else if (unit == 'p') {
    cout << amount << " pounds == " << amount * pound_per_dollar <<  " dollars." << endl;
  } else {
    cout << "I do not recognize the currency " << unit << endl;
  }
  return 0;
}
