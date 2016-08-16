// The difference between declarations and definitions;
/*
 Declaration
  is a statement that introduces a variable into a scope
  - Specifying a type for what is named (e.g. a variable or a function)
  - Optionally specifying an initializer (e.g. an initializer value or a function body.
 Definition - a Declaration that (also) fully specifies the entity declared.

 A definition specifies exactly what a name refers to. In particular,
  a definition of a variable sets aside memory for that variable. Consequently,
  you can not define something twice.

 For a variable,
   a declaration supplies the type,
   but only the definitions supplies the object (the memory).
 For a function,
   a declaration provides the type (argument types plus return type),
   but only the definition supplies a function body (the executable statements).
*/
// g++ -std=c++11 -g -o ch8.2.0.declaration_definition.exe ch8.2.0.declaration_definition.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

double sqrt (double);  // declaration
double sqrt (double d) {/* */} // definition
// double sqrt (double d) {/* */} // error: double definition

double sqrt (double);  // another declaration of sqrt
double sqrt (double);  // yet another declaration of sqrt
// int sqrt (double); // error: inconsistent declaration of sqrt

int main ()
{
  double sqrt(double); // no function body here => declaration that is not definition
  extern int a; // "extern plus no initializer" means "not definition"

  //extern int a = 4; // g++ -std=c++11 -g -o ch8.2.0.declaration_definition.exe ch8.2.0.declaration_definition.C  2>&1 | tee tmp.txt

  int b; // definition
  // int b; // error: double definition

  int x = 7; // definition
  extern int y; // declaration, not a definition
  extern int y; // another declaration (not a definition)
}
