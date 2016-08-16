/* The problem is a "sort of works" experiment to demonstrate and input of an integer between 1 and 10
 *   In case the user enters character, the loop is terminated, and a value of zero (outside the range)
 *   is passed to the program
 *   Example:
 *   Ex1:
 *      if you enter 't', the program will use n=0 (outside of [1,10] range)
 *   EX2:
 *      if you send "end of file" from the keyboard (Ctrl+Z on Windows, and Ctrl+D on Unix)
 */
// g++ -std=c++11 -g ch10.7_ReadingSingleValue.C  -o ch10.7_ReadingSingleValue.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"



int main ()
{
  cout << "Please enter an integer in the range 1 to 10 (inclusive):\n";
  int n = 0;
  while (cin>>n) { // read
    if (1<=n && n<=10) break; // check the range
    cout <<"Sorry "
        << n << " is not in the [1:10] range; please try again\n";
  }
  cout << "We accepted a value of n = "<< n << endl;

  cout << endl<<endl;
  cout << "The same logic, but without using the break construct\n";
  n = 0;
  while (cin>>n && !(1<=n && n<=10)) { // read and check range
    cout <<"Sorry "
        << n << " is not in the [1:10] range; please try again\n";
  }
  cout << "We accepted a value of n = "<< n << endl;

  return 0;
}


