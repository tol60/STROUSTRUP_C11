//
/* Ex10. Write a function vector<string> split(const string& s) that returns a vector of whitespace-separated substrings from the argument s.
 *
 */
// g++ -std=c++11 -g ch11.e.10_split_string.C  -o ch11.e.10_split_string.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

vector<string> split(const string& s) {
  vector <string> v;
  istringstream istr{s};
  for (string str; istr>>str; ) {
    v.push_back(str);
  }
  return v;
}

int main ()
{
  cout << "Please enter a string you want split:\n";
  string str;
  getline(cin,str);

  vector<string> spl_str = split(str);
  cout << "Split string:"<< endl;
  for (string s:spl_str)
    cout << s << endl;



  return 0;
}


