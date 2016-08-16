/* Output your birth year in decimal, hexadecimal, and octal form. Label each value. Line up your output in columns using the tab character.
 * Now output your age.
 * Note:
 * cout << defaultfloat;  did not work!!
 */

// g++ -std=c++11 -g ch11.2.3_FloatingPoint_output.C  -o ch11.2.3_FloatingPoint_output.exe 2>&1 | tee tmp.txt
 
#include "std_lib_facilities.h"
#include <iostream>     // std::cout, std::hexfloat, std::defaultfloat


int main ()
{
  double d = 1234.56789;
  cout << d << "\t\t(defaultfloat)" << endl // \t\t to line up columns
      << fixed << d << "\t(fixed)" << endl
      << scientific << d << "\t(scientific)"<< endl;

  cout <<d<<endl;     // floating format sticks

 // cout << defaultfloat << d << "\t\t(defaultfloat)" << endl // \t\t to line up columns
 //       << fixed << d << "\t(fixed)" << endl
 //       << scientific << d << "\t(scientific)"<< endl;

  cout.unsetf(ios_base::floatfield); // C++98, The default notation (none) is a different floatfield value than either fixed or scientific. The default notation can be selected by calling str.unsetf(ios_base::floatfield).
  cout << d << "\t\t(defaultfloat)" << endl // \t\t to line up columns
        << fixed << d << "\t(fixed)" << endl
        << scientific << d << "\t(scientific)"<< endl;

  return 0;
}


