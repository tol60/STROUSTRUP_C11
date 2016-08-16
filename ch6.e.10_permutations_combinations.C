// Program asks the user of two numbers and asks if the user wants permutations or combination.
// P(a,b) = a!/ (a-b)!  // permutations
// C(a,b) = P(a,b)/b!   // combinations
// g++ -std=c++11 -g -o ch6.e.10_permutations_combinations.exe ch6.e.10_permutations_combinations.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

// compute a! = a*(a-1)*..3*2*1
// 0!=1
double factorial (int a) {
  if (a < 0 ) error ("factorial expects non-zero input");
  double result = 1; // default value for a=0;

  while (a>1) {
    result *= a;
    if (result <0) error ("factorial detected an overflow");
    a--;
  }
  return result;
}

int main ()
{
  try {
    cout << "The program asks for two numbers and then if we want to calculate permutations or combinations !\n";
    while (1) {
      char choice =' ';
      bool choice_not_made = true;
      while (choice_not_made) {
        cout << "Would you like to compute permutations[p] or combinations[c] of two numbers (q to terminate)?";
        cin >> choice;
        if (choice=='q') {
          cout << "Terminating by your request\n";
          break;
        } else if (choice == 'p' || choice == 'c') {
          choice_not_made = false; // we did figure out what function the user wants us to calculate
        }
      }
      if (choice =='q') {
        break;  // terminating - need to break out loop as well
      }

      int a, b; // the input
      cout << "Please enter the first number (the large one): ";
      cin >> a;
      if (a<=0) error("we expect positive input for a");

      cout << "Please enter the second number (smaller one): ";
      cin >> b;
      if (b<0) error ("we expect non-zero input for b");

      if (b>a) error ("b can not exceed a");

      // this computes combinations
      double result = factorial(a)/factorial(a-b);
      if (choice == 'c') {
        result /= factorial(b);
        cout << "C(";
      } else {
        cout << "P(";
      }
      cout << a <<", " << b <<") = " << result << endl;
    }
  }
  catch (exception& e) {
      //if (*e.what()=='x') {
      //  cout << "\nDetected request for early termination\n";
      //  return 0;
      //}
      cerr << "error: " << e.what() << '\n';
      //keep_window_open();
      return 1;
  }
  catch (...) {
      cerr << "Oops: unknown exception!\n";
      //keep_window_open();
      return 2;
  }
  return 0;
}


