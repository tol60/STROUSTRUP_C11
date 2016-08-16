// Calculator First attempt
// g++ -std=c++11 -g -o ch6.3.1_calc_first_attempt.exe ch6.3.1_calc_first_attempt.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"
int main ()
{
  cout << "Please enter expression (we can handle + and -): ";
  int lval = 0;
  int rval;
  char op;
  int res;
  cin >> lval >> op >> rval;  // read something like 1 + 3

  if (op=='+')
    res = lval + rval;  // addition
  else if (op=='-')
    res = lval - rval;  // subtraction

  cout << "Result: " << res << '\n';
  return 0;
}
