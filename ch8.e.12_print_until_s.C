// EX12: Inprove print_until_s() from 8.5.2. Test it.
// Then write a print_until_ss() that prints until it sees a second occurrence of its quit argument

// g++ -std=c++11 -g -o ch8.e.12_print_until_s.exe ch8.e.12_print_until_s.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

// print till you find a quit symbol
void print_until_s(const vector<string>& v, const string& quit)
{
  for (string s:v){
    if (s==quit) return;
    cout << s << endl;
  }
}

// print till you find a quit symbol two times
void print_until_ss(const vector<string>& v, const string& quit)
{
  bool match_found = false;
  for (string s:v){
    if (s==quit) {
      if (match_found)
        return;  // second match
      else
        match_found = true; // first match
    }
    cout << s << endl;
  }
}

int main ()
{
  vector <string> v {"one", "two = 2", "three", "four", "three","five","three"};
  cout <<"print_until_ss \n";
  print_until_s (v, "three");
  cout <<endl;

  cout <<"print_until_ss \n";
  print_until_ss (v, "three");
  return 0;
}
