// guess a number between 1 and 100
// g++ -std=c++11 -g -o ch4.e.4_guessing_game.exe ch4.e.4_guessing_game.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

int main ()
{
  cout << "Please pick a number between 1 and 100. I will try to guess it\n";

  int min{1}, max{100};  // min <= N <=max
  int step{0}; // keep track of the number of questions
  while (max-min > 0) {
    int new_numb = (max + min + 1)/2;
    cout << "Q"<< ++step <<": Is the number less then " << new_numb << "? (y/n)\n";
    char ch; // will be used to enter the response
    for (ch =' '; ch != 'y' && ch != 'n'; cin >> ch) {;} // should enter y/n
    if (ch=='y'){
      max = new_numb - 1;  // N < new_numb; // min <= N <=max
    } else {
      min = new_numb;
    }
  }

  // at this point min=max = the number selected
  cout << "After " << step << " steps I believe your number is " << max << endl;

  return 0;
}


