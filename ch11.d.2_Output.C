//
/* D1. Start a program. Declare an integer birth_year and assign it the year you were born.
 * D2. Output your birth_year in decimal, hexadecimal and octal form
 * D3. Label each value with the name of the base used.
 * D4. Did you line up your output in columns using the tab character? If not, do it
 */
// g++ -std=c++11 -g ch11.d.2_Output.C  -o ch11.d.2_Output.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

int main ()
{
  int birth_year = 1975;

  cout << "Birth year: \n";
  cout << showbase;
  cout << "\t As decimal \t" << dec << birth_year << endl;
  cout << "\t As hexadecimal\t" << hex << birth_year << endl;
  cout << "\t As octal \t" << oct << birth_year << endl;

  return 0;
}


