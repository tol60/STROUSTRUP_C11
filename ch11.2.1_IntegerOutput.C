/* Output your birth year in decimal, hexadecimal, and octal form. Label each value. Line up your output in columns using the tab character.
 * Now output your age.
 */

// g++ -std=c++11 -g ch11.2.1_IntegerOutput.C  -o ch11.2.1_IntegerOutput.exe 2>&1 | tee tmp.txt
 
#include "std_lib_facilities.h"


int main ()
{
  int year = 1975;
  int age = 41;
  cout << showbase;
  cout << year << '\t' << hex << year << '\t' << oct << year << endl;
  cout << dec << age << '\t' << hex << age << '\t' << oct << age << endl;

  return 0;
}


