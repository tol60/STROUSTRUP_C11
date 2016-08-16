// take an argument and two operands
// g++ -std=c++11 -g -o ch3.e.11_count_pennies.exe ch3.e.11_count_pennies.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"
int main ()
{
  cout<< "Please enter the number of pennies (1-cent coins):";
  int pennies{0};
  cin >> pennies;

  cout<< "Please enter the number of nickels (5-cent coins):";
  int nickels{0};
  cin >> nickels;

  cout<< "Please enter the number of dimes (10-cent coins):";
  int dimes{0};
  cin >> dimes;

  cout<< "Please enter the number of quarters (25-cent coins):";
  int quarters{0};
  cin >> quarters;

  cout<< "Please enter the number of half dollars (50-cent coins):";
  int half_dollars{0};
  cin >> half_dollars;

  cout<< "Please enter the number of one-dollar coins (100-cent coins):";
  int one_dollars{0};
  cin >> one_dollars;

  int total{0};
  cout <<endl;
  if (pennies !=1) {
    cout << "You have " << pennies<<" pennies.\n";
  } else {
    cout << "You have " << pennies<<" penny.\n"; // just one penny
  }
  total += pennies;

  if (nickels !=1) {
    cout << "You have " << nickels<<" nickels.\n";
  } else {
    cout << "You have " << nickels<<" nickel.\n"; // just one nickel
  }
  total += 5*nickels;

  if (dimes !=1) {
    cout << "You have " << dimes<<" dimes.\n";
  } else {
    cout << "You have " << dimes<<" dime.\n"; // just one dime
  }
  total += 10 * dimes;

  if (quarters !=1) {
    cout << "You have " << quarters<<" quarters.\n";
  } else {
    cout << "You have " << quarters<<" quarter.\n"; // just one quarter
  }
  total += 25 * quarters;

  if (half_dollars !=1) {
    cout << "You have " << half_dollars<<" half dollars.\n";
  } else {
    cout << "You have " << half_dollars<<" half dollar.\n"; // just one half dollar
  }
  total += 50 * half_dollars;

  if (one_dollars !=1) {
    cout << "You have " << one_dollars<<" one-dollar coins.\n";
  } else {
    cout << "You have " << one_dollars<<" one-dollar coin.\n"; // just one penny
  }
  total += 100 * one_dollars;

  cout << "The value of all of your coins is "<< total << " cent";
  if (total != 1) {
    cout <<'s';  // plural for cents
  }
  // if we have more then a dollar, convert to dollars.
  if (total >=100) {
    cout << " ($" << total/100 <<"." << total%100<<")";
  }
  cout << ".\n";

  return 0;
}


