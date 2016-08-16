// using vector holding the ten string values "zero", "one", ... "nine" convert digit to corresponding spelled out value.
// Example: 7 => "seven".
// Have the same input loop, convert spelled-out numbers into their digit form
// g++ -std=c++11 -g -o ch4.e.7_calculator_digit.exe ch4.e.7_calculator_digit.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

// string2digit will take a string, representing a digit as spelled out word or a number. Example: "four" or "4"
// Output:
//  if result >=0 gives the digit we recognized
//  if result <= - did not recognize the input
int string2digit (string input) {
  vector <string> dig2string {"zero","one","two", "three","four","five", "six","seven","eight","nine"};
  int answer = -1;  // if recognize the entry will set a value >=0;
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
        //cout << "You entered a string " << input << " which represents a number " << i << endl;
        break; // terminate the for loop
      }
    }

    // handle the case where we did not recognize the input
    if (i>=dig2string.size()) {
      cout << "Sorry, I did not understand your entry: "<< input<<endl;
    } else {
      answer = i;  // recognized a sting input: Example: "five"
    }
  }

  if (index>=0) {
    // detected a single digit
    //string answer_str = dig2string[index];
    //cout << "You entered a digit " << input << " which is a number " << answer_str<< endl;
    answer = index; // recognized a digit input. Example: "5"
  }

  return answer; // Note, if the entry was not recognized, should return -1 (set at the beginning of the function)
}

int main ()
{
  cout << "Please enter two digits and an operation (+,-,*,/)\n";
  cout << "Digits can be entered as a word or a number. Please enter the space in between. Example \"three + 5\"\n";
  string str_arg1,str_arg2; // two arguments
  char oper; // operation we want to perform
  while (cin>> str_arg1 >> oper >> str_arg2 ) {
    double arg1 = string2digit(str_arg1);
    double arg2 = string2digit(str_arg2);
    if (arg1>=0 && arg2>=0) {
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
    cout << "Enter a new entry or type ctrl+D:\n";
  }
  return 0;
}


