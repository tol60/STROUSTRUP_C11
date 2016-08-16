// Program reads digits and composes them into integers.
// For example, 123 is read as the characters 1,2 and 3. The program should output 123 as 1 hundred and 2 tens and 3 ones.
// The number should be output as an int value. Handle numbers with one, two, three or four digits.
// Hint: to get the integer value of 5 from the character '5' subtract '0', that is, '5'-'0'==5.
// g++ -std=c++11 -g -o ch6.e.9_read_digits.exe ch6.e.9_read_digits.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

int main ()
{
  cout << "The program will read integer and composes them into integers !\n";
  cout << "Example:\n";
  cout << "123 is read as the characters 1,2 and 3.\n";
  cout << "The program should output 123 as 1 hundred and 2 tens and 3 ones.\n";
  cout << "The program handles numbers with one, two, three or four digits.\n";

  const int max_num_digits = 4;

  vector <int> input; // store the input
  while (1) {
    cout << "Please enter a new number:\n";
    input.clear();
    char ch;
    while (cin>>ch){
      if (ch>='0' && ch<= '9') {
        int digit = ch - '0';
        input.push_back(digit);
      } else {
        break; // exit the input loop
      }
    }

    cout << "You entered: ";
    for (auto d:input){
      cout << d;
    }
    cout << endl;

    int num_digits = input.size();
    if (num_digits > max_num_digits) {
      cout << "The input contains " << num_digits << " digits. We only support " << max_num_digits <<endl;
      //error ("Unsupported number of digits");
      break;
    }

    cout << "\tIt is ";
    for (int i=0; i<num_digits; i++) {
      cout << input[i];
      string str="";
      switch (num_digits - i) {
      case 4:
        str = "thousand";
        break;
      case 3:
        str = "hundreed";
        break;
      case 2:
        str = "tens";
        break;
      case 1:
        str = "ones";
        break;
      }
      cout << " " << str << " ";
    }
    cout <<endl;
  }

  return 0;
}


