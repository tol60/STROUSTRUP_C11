// using vector holding the ten string values "zero", "one", ... "nine" convert digit to corresponding spelled out value.
// Example: 7 => "seven".
// Have the same input loop, convert spelled-out numbers into their digit form
// g++ -std=c++11 -g -o ch4.e.6_spell2digit.exe ch4.e.6_spell2digit.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

int main ()
{
  vector <string> dig2string {"zero","one","two", "three","four","five", "six","seven","eight","nine"};

  cout << "Please enter a digit (as a number or a spelled out word):\n";

  /* this works with chars as digits
  char ch;
  while (cin >> ch) {
    // warning: the length returns the number of bytes. Might not work in UTF8
    if (ch>='0' && ch<='9') {
      // detected a single digit
      string answer_str = dig2string[int(ch) - int('0')];
      cout << "You entered a digit " << ch << " which is a number " << answer_str<< endl;
    } else {
        cout << "Sorry, I did not understand your entry: "<< ch <<endl;
    }
  }
  */

  string input;
  while (cin >> input) {
    int index = -1; // used as an index and a flag. If >=0 - we entered a single digit, if <0 - entered a word or not recognized
    if (input == "0" ) {
      index = 0;
    } else if (input == "1") {
      index = 1;
    } else if (input == "2") {
      index = 2;
    } else if (input == "3") {
      index = 3;
    } else if (input == "4") {
      index = 4;
    } else if (input == "5") {
      index = 5;
    } else if (input == "6") {
      index = 6;
    } else if (input == "7") {
      index = 7;
    } else if (input == "8") {
      index = 8;
    } else if (input == "9") {
      index = 9;
    } else {
      // try to find a word in dig2string
      int i=0; // will be used as an iterator in the for loop as well as the flag
      for (; i<dig2string.size(); ++i ) {
        if (input == dig2string[i]) {
          cout << "You entered a string " << input << " which represents a number " << i << endl;
          break; // terminate the for loop
        }
      }

      // handle the case where we did not recognize the input
      if (i>=dig2string.size()) {
        cout << "Sorry, I did not understand your entry: "<< input<<endl;
      }
    }

    if (index>=0) {
      // detected a single digit
      string answer_str = dig2string[index];
      cout << "You entered a digit " << input << " which is a number " << answer_str<< endl;
    }
  }

  /*
  cout << "Please enter two floating point numbers and an operation (+,-,*,/):\n";
  double arg1,arg2; // two arguments
  char oper; // operation we want to perform
  while (cin>> arg1 >> arg2 >> oper) {
    switch (oper) {
    case '+':
      cout << "The sum of " << arg1 << " and " << arg2 << " is " << arg1 + arg2 << endl;
      break;
    case '-':
      cout << "The difference of " << arg1 << " and " << arg2 << " is " << arg1 - arg2 << endl;
      break;
    case '*':
      cout << "The product of " << arg1 << " and " << arg2 << " is " << arg1 * arg2 << endl;
      break;
    case '/':
      cout << "The result of of " << arg1 << " by " << arg2 << " is " << arg1 / arg2 << endl;
      break;
    default :
      cout << "I did not recognize the operation \"" << oper << "\"" <<endl;
    }
  }
  */
  return 0;
}


