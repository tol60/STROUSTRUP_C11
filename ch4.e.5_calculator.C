// simple calculator
// g++ -std=c++11 -g -o ch4.e.5_calculator.exe ch4.e.5_calculator.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

int main ()
{
  cout << "Please enter two floating point numbers and an operation (+,-,*,/):\n";
  double arg1,arg2; // two arguments
  char oper; // operation we want to perform
  while (cin>> arg1 >> arg2 >> oper) {
    switch (oper) {
    case '+':
      cout << "The sum of " << arg1 << " and " << arg2 << " is " << arg1 + arg2 << endl;
      break;
    case '-':
      cout << "The difference of " << arg1 << " and " << arg2 << " is " << arg1 - arg2 << endl;
      break;
    case '*':
      cout << "The product of " << arg1 << " and " << arg2 << " is " << arg1 * arg2 << endl;
      break;
    case '/':
      cout << "The result of of " << arg1 << " by " << arg2 << " is " << arg1 / arg2 << endl;
      break;
    default :
      cout << "I did not recognize the operation \"" << oper << "\"" <<endl;
    }
  }

  return 0;
}


