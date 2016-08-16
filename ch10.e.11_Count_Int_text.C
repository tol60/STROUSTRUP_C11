/* Write a program that produces the sum of all the whitespace-separated integers in a text file. For example, "bears: 17 elephants 9 end" should output 26
   Extra complication:
     if you have "- 17" minus space 17 treat it as a positive 17
     if you have "-17" minus 17 treat it as a negative 17
 */

// g++ -std=c++11 -g ch10.e.11_Count_Int_text.C  -o ch10.e.11_Count_Int_text.exe 2>&1 | tee tmp.txt
 
#include "std_lib_facilities.h"


int main ()
{
  cout << "Please enter the file name. The program will try to count the sum of all integers (space separated) in the file\n";
  cout << ">>";
  string fname;
  cin >> fname;
  ifstream ist {fname};
  if(!ist) error ("can not open input file ",fname);
  ist.exceptions(ist.exceptions()|ios_base::badbit);

  int sum = 0 ; // global counter
  char ch;
  bool neg = false;
  while (ist.get(ch)) { // unformatted input (to catch '-' and "- 7"
    switch (ch) {
    case '-':
      neg = true; // now fall down to process (if the next character is a digit
      break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      ist.unget();
      int num;
      ist >> num;
      if (neg) num = -num; // handle negatives
      sum += num;
      neg = false; // prepare for the next iteration
      break;
    default:
      neg = false;
      break;
    }
  }
  cout << "The total number of integers (accounting for the sign), is: " << sum << endl;
  return 0;
}


