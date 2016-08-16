// Converts a string three into a number 3. Works for 0..4
// g++ -std=c++11 -g -o ch3.e.9_spell_numbers.exe ch3.e.9_spell_numbers.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"
int main ()
{
  cout<< "Please enter \"zero\" - \"four\" (lower case):\n";
  string number{""};
  int conv_numb{0};
  while (cin >> number) {
    // do the conversion
    conv_numb = -1; // to flag that we did not recognize the number
    if (number == "zero") {
      conv_numb = 0;
    } else if (number == "one"){
      conv_numb = 1;
    } else if (number == "two"){
      conv_numb = 2;
    } else if (number == "three"){
      conv_numb = 3;
    } else if (number == "four"){
      conv_numb = 4;
    }

    // output the result
    if (conv_numb < 0) {
      cout << "Input: \""<< number << "\" not a number I know\n";
    } else {
      cout << "A number \"" << number << "\" is: "<< conv_numb<<"\n";
    }
  }
  return 0;
}


