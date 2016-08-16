// prints letters (and the corresponding number) for letters 'a' to 'z'
// g++ -std=c++11 -g -o ch4.4.2.3_for_letters.exe ch4.4.2.3_for_letters.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"
int main ()
{
  for (char letter = 'a'; letter <= 'z'; ++letter)
    cout << letter << "\t" << int (letter) << endl;

  for (char letter = 'A'; letter <= 'Z'; ++letter)
    cout << letter << "\t" << int (letter) << endl;

  for (char letter = '0'; letter <= '9'; ++letter)
    cout << letter << "\t" << int (letter) << endl;
  return 0;
}
