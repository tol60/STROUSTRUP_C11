//
/* D1. Start a program. Declare an integer birth_year and assign it the year you were born.
 * D2. Output your birth_year in decimal, hexadecimal and octal form
 * D3. Label each value with the name of the base used.
 * D4. Did you line up your output in columns using the tab character? If not, do it
 * D5. Now output your age.
 * D6. Was there a problem? What happened? Fix your output to decimal
 * D7. Go back to 2 and cause your output to show the base for each output.
 */
// g++ -std=c++11 -g ch11.d.7_Output.C  -o ch11.d.7_Output.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

int main ()
{
  int birth_year = 1975;
  int age = 41;
  cout << "Birth year: \n";
  cout << showbase;
  cout << "\t As decimal \t" << dec << birth_year << endl;
  cout << "\t As hexadecimal\t" << hex << birth_year << endl;
  cout << "\t As octal \t" << oct << birth_year << endl;

  cout.unsetf(ios::oct);
  cout << "The age is " << age <<endl;
  return 0;
}


