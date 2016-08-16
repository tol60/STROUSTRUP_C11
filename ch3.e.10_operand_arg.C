// take an argument and two operands
// g++ -std=c++11 -g -o ch3.e.10_operand_arg.exe ch3.e.10_operand_arg.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"
int main ()
{
  cout<< "Please enter an operation (+,-,*,/) and two operands:\n";
  string operation{""};
  double op1{0.0}, op2{0.0};
  double result{0.0};
  while (cin >> operation>>op1>>op2) {
  //while (cin >> operation) {
    bool flag = true;
    if (operation == "+") {
      result = op1 + op2;
    } else if (operation == "-") {
      result = op1 - op2;
    } else if (operation == "*") {
      result = op1 * op2;
    } else if (operation == "/") {
      result = op1 / op2;
    } else {
      flag = false; // we did not recognize the operation.
    }

    if (flag) {
      // we recognized the operation
      cout << op1 << operation << op2 << "="<<result<<endl;
    } else {
      cout << "The operation \"" << operation<<"\" was not recognized\n";
    }
  }
  return 0;
}


