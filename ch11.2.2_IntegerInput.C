/* Output your birth year in decimal, hexadecimal, and octal form. Label each value. Line up your output in columns using the tab character.
 * Now output your age.
 */

// g++ -std=c++11 -g ch11.2.2_IntegerInput.C  -o ch11.2.2_IntegerInput.exe 2>&1 | tee tmp.txt
 
#include "std_lib_facilities.h"


int main ()
{
  int a;
  int b;
  int c;
  int d;
  cout << "Please enter a decimal, hex, oct, oct numbers (1234 4d2 2322 2322) Expect to get back 1234 1234 1234 1234):\n";
  cin >> a >> hex >> b >> oct >> c >> d;
  cout << a << '\t' << b << '\t' << c << '\t' << d << endl;

  cout << endl;
  cin.unsetf(ios::oct);
  cout << "Enter 1234 0x4d2 02322 02322\n";
  cin >> a >> b >>  c >> d;
  cout << a << '\t' << b << '\t' << c << '\t' << d << endl;
  return 0;
}


