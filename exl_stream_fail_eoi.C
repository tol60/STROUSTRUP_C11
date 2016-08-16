/* Trying to see if we can detect cin.eof() status
 *
 *   Note:
 *     int n=0;
 *     cin>>n;
 *
 *     If I terminate cin( enter "Ctrl+D" - Unix or "Ctrl+Z" - Windows)  the cin end up in BOTH the fail state, and  in the eof() state.
 */

// g++ -std=c++11 -g exl_stream_fail_eoi.C  -o exl_stream_fail_eoi.exe 2>&1 | tee tmp.txt

#include <iostream>
using namespace std;


void cin_state(const string& msg) {
  // Stream states:
  // good() The operations succeeded.
  // eof()  We hit end of input ("end of file"). Ctrl-Z - Windows, Ctrl-D - Linux
  // fail() Something unexpected happened (e.g., we looked for a digit and found 'x')
  // bad() Something unexpected and serious happened (e.g., a disk read error)
  //
  // Note:
  // if cin.bad() it is also cin.fail()
  // if cin.eof() it is also cin.fail() (vefify)

  cout << msg << "cin is in ";
  bool StateRecognized = false;
  if (cin) { // cin.good()
    cout <<"a good() state\t";
    StateRecognized = true;
  }
  if (cin.fail()) {
    cout <<"a fail() state\t";
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
    cerr << "ERROR: cin_state function: Internal Error \n";
}

int main ()
{
  operator<<(cout, "Hallow world\n");  // takes ostream& as a first argument and returns it again as its rturn value;
  operator<<(cout, "We can stack operators. First one") << ", Second One\n";

  cout << "Experimenting with char loop.\n";
  cout << "As long as you enter a character (and then Enter), we will remain in the loop\n";
  cout << "Once you terminate input stream by pressing Ctrl-Z on Windows, or Ctrl-D on Linux, the program exits\n";
  cout << "Want to make sure that when we exit, stream is both in fail() and eof() states\n";
  cout << endl;
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

  return 0;
}


