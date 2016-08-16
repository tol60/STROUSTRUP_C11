 /* write a gramma for a bitwise logical expressions.
  * A bitwise logic expression is much like an arithmetic expression except that the operators are
  * !(not), ~ (complement), & (and), ^ (exclusive or) and | (or)
  * ! and ~ are prefix unary operators.
  * An ^ binds tighter than an | (just as * binds tighter then +) so that x|y^z means x|(y^z)
  * The & operator binds tighter than ^ so that x^y&z means x^(y&z).
  */
// g++ -std=c++11 -g -o ch6.e.7_binary_grammar.exe ch6.e.7_binary_grammar.C  2>&1 | tee tmp.txt

// Grammar:
/*
Expression:
  Term
  Expression | Term
Term:
  Subset
  Term ^ Subset
Subset:
  Block
  Subset "&" Block
Block:
  Primary
  "!" Primary
  "~" Primary
Primary:
  Number
  "("Expression")"   // grouping

Number: floating-point-literal
*/
#include "std_lib_facilities.h"



int main ()
try
{
    cout << "This test describes the grammar only (no code implemented).\n";
    cout << "!(not), ~ (complement), & (and), ^ (exclusive or) and | (or)\n";
    //keep_window_open();
}
catch (exception& e) {
    if (*e.what()=='x') {
      cout << "\nDetected request for early termination\n";
      return 0;
    }
    cerr << "error: " << e.what() << '\n';
    //keep_window_open();
    return 1;
}
catch (...) {
    cerr << "Oops: unknown exception!\n";
    //keep_window_open();
    return 2;
}


