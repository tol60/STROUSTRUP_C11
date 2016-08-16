// write a program to illustrate geometric sequence (grain on the chess board example). Try to fill out the full board
// g++ -std=c++11 -g -o ch4.e.9_geometric_chess_full.exe ch4.e.9_geometric_chess_full.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"


int main ()
{
  double square{1}; // keep the track of a square we are on;
  double grain_on_square{1}; // keep the track of the grain on a current square
  double sum {0}; // grain on all previous squares

  constexpr int top_square{64};

  cout << "I will illustrate the geometric chess board:\n";
  for(square=1; square <=top_square; square++)
  {
    sum += grain_on_square; // count the current square into the total
    cout << "Square " << square << " contains " << grain_on_square << " sum = "<< sum << endl;

    // prepare for the next iteration
    grain_on_square *=2; // the next square will contain twice as much corn as the previous one
  }

  cout << "You will amass " << sum << endl;

  return 0;
}


