// illustrate "Rock, Paper, Scissors" game
// g++ -std=c++11 -g -o ch4.e.10_rock_paper_scissors.exe ch4.e.10_rock_paper_scissors.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"


int main ()
{
  const vector <string> outcomes_vec{"Rock", "Paper", "Scissors"};

  cout << "I will illustrate \"Rock, Paper, Scissors\" game.\n";
  cout << "Please input the number of random examples you'd like to see:\n";

  int num_examples{1};
  cin >> num_examples;
  cout << "You entered "<< num_examples << "examples.\n";
  for (int i=0; i<num_examples; ++i){
    // Randomly pick an outcome
    int selA = rand() % outcomes_vec.size(); // 0, 1, 2
    int selB = rand() % outcomes_vec.size(); // 0, 1, 2
    cout << "Iteration " << i <<": A " << outcomes_vec[selA] << ", \tB " << outcomes_vec[selB];

    if (selA == selB) {
      // draw
      cout << ". Results in a draw\n";
    } else {
      // selA != selB
      switch (selA) {
      case 0:
        // selA==0 - "Rock"
        if (selB == 1) {
          // selB == 1 => "Paper"
          cout << ". A looses: Paper wraps around the Stone\n";
        } else {
          // SelB == 2 => "Scissors"
          cout << ". A wins: Stone dulls the Scissors\n";
        }
        break;
      case 1:
        // selA == 1 - Paper
        if (selB == 0) {
          // selB==0 - "Rock"
          cout << ". A wins: Paper wraps around the Stone\n";
        } else {
          // SelB == 2 => "Scissors"
          cout << ". A looses: Scissors cut the Paper\n";
        }
        break;
      case 2:
        // selA == 2 - Scissors
        if (selB == 0) {
          // selB==0 - "Rock"
          cout << ". A looses: Stone dulls the Scissors\n";
        } else {
          // selB == 1 => "Paper"
          cout << ". A wins: Scissors cut the Paper\n";
        }
        break;
      }
    }
    // end of the loop

  }

  return 0;
}


