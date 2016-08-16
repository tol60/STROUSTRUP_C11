//
/* D1. Start a program. Declare an integer birth_year and assign it the year you were born.
 */
// g++ -std=c++11 -g ch11.d.1_Output.C  -o ch11.d.1_Output.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

int main ()
{
  int birth_year = 1975;

  cout << "Birth year: \n";
  cout << showbase;
  cout << "\t As decimal " << dec << birth_year << endl;
  cout << "\t As hexadecimal " << hex << birth_year << endl;
  cout << "\t As octal " << oct << birth_year << endl;

  return 0;
}


