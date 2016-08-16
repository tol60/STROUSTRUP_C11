/* Trying to see if we can detect cin.eof() status
 *
 *   Note:
 *     int n=0;
 *     cin>>n;
 *
 *     If I terminate cin( enter "Ctrl+D" - Unix or "Ctrl+Z" - Windows)  the cin end up in BOTH the fail state, and  in the eof() state.
 */

// g++ -std=c++11 -g ch10.7.1_B_Status_eof.C  -o ch10.7.1_B_Status_eof.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

void skip_to_int() // utility function
{
  if( cin.fail() ) { // we found something that was not an integer
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
  error ("no input"); // eof or bad: give up
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

    if (!cin.fail())
      error("get_int error, no input"); // eof or bad give up
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
  cout << "Experimenting with char loop\n";
  char ch;
  while (true) {
    cin>>ch;
    cin_state("After entering c char, ");
    cout << endl;
    if (cin.eof()) {
      cout << "cin.eof() detected!! Terminating\n";
      break;
    }

  }
  /*
  int n = get_int(1,10);
  cout << "n: " << n << endl;

  int m = get_int(2,300);
  cout << "m: " << m << endl;
  */
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


