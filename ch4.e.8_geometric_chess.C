// write a program to illustrate geometric sequence (grain on the chess board example).
// g++ -std=c++11 -g -o ch4.e.8_geometric_chess.exe ch4.e.8_geometric_chess.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"


int main ()
{
  int square{1}; // keep the track of a square we are on;
  int grain_on_square{1}; // keep the track of the grain on a current square
  int sum {0}; // grain on all previous squares

  int target_grain{0};

  cout << "Please enter the amount of grain you wish to get via geometric chess board award:\n";
  cin >> target_grain;
  target_grain = abs(target_grain);
  cout << "I see you want to get " << target_grain << " grains.\n";
  while (sum < target_grain)
  {
    cout << "Square " << square << " contains " << grain_on_square << endl;
    sum += grain_on_square; // count the current square into the total

    // prepare for the next iteration
    ++square; // increment the square number
    grain_on_square *=2; // the next square will contain twice as much corn as the previous one
  }
  --square; // we prepared for the next iteration but never executed it. roll back for reporting

  cout << "It would require you " << square << " squares to acheave your goal of " << target_grain<<". In fact, you will amass " << sum << endl;

  return 0;
}


