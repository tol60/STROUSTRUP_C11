/* FIXED: Added extra checker to detect eof() in get_int()
 *    originally, you needed to enter two "Ctrl-Z" on Windows or "Ctrl-D" on Linux
 *
 * This version handles both an out-of-range input and an input of the wrong type locally
 *   We separate logically different functions into its own functions
 *
 *   Note:
 *     int n=0;
 *     cin>>n;
 *
 *     If I enter "Ctrl+D" the cin end up in BOTH fail() and eof() state.
 */

// g++ -std=c++11 -g ch10.7.1_ReadingSingleValue_good_FIXED.C  -o ch10.7.1_ReadingSingleValue_good_FIXED.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

// the code for recovering after seeing a "bad" (i.e., unexpected) character:
void skip_to_int() // utility function
{
  if( cin.fail() ) { // we found something that was not an integer or eof()
    if (cin.eof())  // if cin.eof(), it is also cin.fail()
      error("Eof detected. Throw an error");

    cin.clear();  // set the state back to good()
    // we want to look at the characters
    for (char ch; cin>>ch;) {// throw away non-digits
      //if (isdigit(ch) || ch=='.') {
      if (isdigit(ch) ) {
        cin.unget(); // put the digit back, so that we can read the number
        return;
      }
    }
  }
  error ("no input. stream is in a bad state"); // bad: give up
}

void cin_state(const string& msg) {
  // Note: cin can be in both cin.fail() and cin.eof() state
  cout << msg << "cin is in ";
  bool StateRecognized = false;
  if (cin) { // cin.good()
    cout <<"a good state\t";
    StateRecognized = true;
  }
  if (cin.fail()) {
    cout <<"a fail state\t";
    StateRecognized = true;
  }
  if (cin.eof()) {
    cout << "a eof() state\t";
    StateRecognized = true;
  }
  if (cin.bad()) {
    cout << "a bad() state\t";
    StateRecognized = true;
  }

  if (!StateRecognized)
    error ("cin_state function: Internal Error");
}

int get_int() // read an int from cin
{
  int n=0;
  while (true) {
    if (cin>>n) return n;
    //cin_state("get_int function point ZZ00");

    cout << "Sorry, that was not a number; please try again\n";
    skip_to_int();
  }
}

int get_int(int low, int high) // read an int in [low:high] from cin
{
  cout << "Please enter an integer in the range "
      << low << " to " << high << " (inclusive):\n";
  while (true) {
    int n = get_int();
    if (low <= n && n<=high) return n;
    cout << "Sorry, "
        << n << " is not in the [" << low <<':' << high << "] range; please try again\n";
  }
}

int main ()
{
  try {
    int n = get_int(1,10);
    cout << "n: " << n << endl;
  }
  catch(runtime_error& e) {
    cerr << e.what() << endl;
    cerr << "clearing all cin errors\n";
    cin.clear();
  }
  catch(...) {
    cerr << "Oops: unknown exception!\n";
    return 2;
  }

  try {
    int m = get_int(2,300);
    cout << "m: " << m << endl;
  }
  catch(runtime_error& e) {
    cerr << e.what() << endl;
    cerr << "clearing all cin errors\n";
    cin.clear();
  }
  /* Example (intermediary version) that uses skip_to_int() function

  cout << "Please enter an integer in the range 1 to 10 (inclusive):\n";
  int n = 0;
  while (true) {
    cin>>n;
    if (cin) {  // we got an integer; now check it
      if (1<=n && n<=10) break; // check the range
      cout <<"Sorry "
          << n << " is not in the [1:10] range; please try again\n";
    } else {
      // saw something other then digit
      cout < "Sorry, that was not a number; please try again\n";
      skip_to_int();
    }
  }
  cout << "We accepted a value of n = "<< n << endl;
  */

  return 0;
}


