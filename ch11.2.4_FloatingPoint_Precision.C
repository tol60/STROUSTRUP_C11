/* Write some code to print the number 1234567.89 three times, first using defaulfloat, then fixed, then scientific.
 * Which output form presents the user with the most accurate presentation? Explain why.
 * Note:
 * cout << defaultfloat;  did not work!!
 */

// g++ -std=c++11 -g ch11.2.4_FloatingPoint_Precision.C  -o ch11.2.4_FloatingPoint_Precision.exe 2>&1 | tee tmp.txt
 
#include "std_lib_facilities.h"


int main ()
{
  double d = 1234567.89;
  cout << d << "\t\t(defaultfloat)" << endl // \t\t to line up columns
      << fixed << d << "\t(fixed)" << endl
      << scientific << d << "\t(scientific)"<< endl;

  cout <<d<<endl;     // floating format sticks
  cout.unsetf(ios_base::floatfield); // C++98, The default notation (none) is a different floatfield value than either fixed or scientific. The default notation can be selected by calling str.unsetf(ios_base::floatfield).

  cout << endl;

  d= 1.3;
  cout << d << "\t\t(defaultfloat)" << endl // \t\t to line up columns
      << fixed << d << "\t(fixed)" << endl
      << scientific << d << "\t(scientific)"<< endl;
  cout <<d<<endl;     // floating format sticks
  cout << endl;

  d= 1234.56789;
  cout << d << "\t\t(defaultfloat)" << endl // \t\t to line up columns
      << fixed << d << "\t(fixed)" << endl
      << scientific << d << "\t(scientific)"<< endl;
  cout <<d<<endl;     // floating format sticks
  cout << endl;

  cout << "Setting precision to 5\n";
  cout << setprecision(5);
  cout.unsetf(ios_base::floatfield); // C++98, The default notation (none) is a different floatfield value than either fixed or scientific. The default notation can be selected by calling str.unsetf(ios_base::floatfield).
  cout << d << "\t\t(defaultfloat)" << endl // \t\t to line up columns
        << fixed << d << "\t(fixed)" << endl
        << scientific << d << "\t(scientific)"<< endl;
  cout <<d<<endl;     // floating format sticks
  cout << endl;

  cout << "Setting precision to 8\n";
  cout << setprecision(8);
  cout.unsetf(ios_base::floatfield); // C++98, The default notation (none) is a different floatfield value than either fixed or scientific. The default notation can be selected by calling str.unsetf(ios_base::floatfield).
  cout << d << "\t\t(defaultfloat)" << endl // \t\t to line up columns
        << fixed << d << "\t(fixed)" << endl
        << scientific << d << "\t(scientific)"<< endl;
  cout <<d<<endl;     // floating format sticks
  cout << endl;

  cout << "Setting precision to 2\n";
  cout << setprecision(2);
  cout.unsetf(ios_base::floatfield); // C++98, The default notation (none) is a different floatfield value than either fixed or scientific. The default notation can be selected by calling str.unsetf(ios_base::floatfield).
  cout << d << "\t\t(defaultfloat)" << endl // \t\t to line up columns
        << fixed << d << "\t(fixed)" << endl
        << scientific << d << "\t(scientific)"<< endl;

  return 0;
}


