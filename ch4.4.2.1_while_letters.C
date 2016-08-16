// prints letters (and the corresponding number) for letters 'a' to 'z'
// g++ -std=c++11 -g -o ch4.4.2.1_while_letters.exe ch4.4.2.1_while_letters.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"
int main ()
{
  char letter{'a'};
  while (letter <= 'z') {
    int number = letter;
    cout << letter << "\t" << number << endl;
    letter = char(++number);
  }
  return 0;
}
