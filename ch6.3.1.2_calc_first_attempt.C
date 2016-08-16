// Calculator First attempt
// g++ -std=c++11 -g -o ch6.3.1.2_calc_first_attempt.exe ch6.3.1.2_calc_first_attempt.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"
int main ()
{
  cout << "Please enter expression (we can handle +,-,*,and /)\n";
  cout << "add an x to end expression (e.g., 1+2*3x): ";
  int lval = 0;
  int rval;
  cin>>lval;  // read leftmost operand
  if (!cin) error ("no first operand");
  for (char op;cin>>op;) { // read operator and right-hand operand repeatedly
    if (op!='x') cin>>rval;
    if(!cin) error("no second operand");
    switch(op){
    case '+':
      lval += rval; // add: lval = lval + rval
      break;
    case '-':
      lval -= rval; // subtract: lval = lval - rval
      break;
    case '*':
      lval *= rval; // multiply: lval = lval * rval
      break;
    case '/':
      lval /= rval; // divide: lval = lval / rval
      break;
    default:  /// not another operator: print result
      cout << "Result: " << lval << endl;
      return 0;
    }
  }
  error("bad expression");
}
