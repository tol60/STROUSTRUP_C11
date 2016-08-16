// detects if an integer is even or odd
// g++ -std=c++11 -g -o ch3.e.8_even_odd.exe ch3.e.8_even_odd.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"
int main ()
{
  cout<< "Please enter an integer numbe(s):\n";
  int number{0};

  while (cin >> number) {
    if (number % 2) {
      cout << "A number " << number << " is odd\n";
    } else {
      cout << "A number " << number << " is even\n";
    }
  }
  return 0;
}


