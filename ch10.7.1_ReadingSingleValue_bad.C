/* This version handles both an out-of-range input and an input of the wrong type locally
 *   (Messy Example, not recommended - bad example)
 */
// g++ -std=c++11 -g ch10.7.1_ReadingSingleValue_bad.C  -o ch10.7.1_ReadingSingleValue_bad.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"



int main ()
{
  cout << "Please enter an integer in the range 1 to 10 (inclusive):\n";
  int n = 0;
  while (true) {
    cin>>n;
    if (cin) {  // we got an integer; now check it
      if (1<=n && n<=10) break; // check the range
      cout <<"Sorry "
          << n << " is not in the [1:10] range; please try again\n";
    } else if( cin.fail() ) { // we found something that was not an integer
      cin.clear();  // set the state back to good()
                    // we want to look at the characters
      cout <<"Sorry, that was not a number; please try again\n";
      for (char ch; cin>>ch && !isdigit(ch);) // throw away non-digits
        /* nothing */ ;
      if (!cin)
        error("no input"); // we did not find a digit: give up
      cin.unget(); // put the digit back, so that we can read the number
    } else {
      error("no input: eof or bad: give up"); // eof or bad give up
    }
  }
  cout << "We accepted a value of n = "<< n << endl;


  return 0;
}


