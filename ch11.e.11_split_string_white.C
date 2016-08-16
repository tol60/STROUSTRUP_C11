//
/* Ex11. Write a function vector<string> split (const string& s, const string& w) that returns
 * a vector of whitespace-separated substrings from the argument s, where whitespace is defined as "ordinary whitespace" plus the characters in w.

 * Ex10. Write a function vector<string> split(const string& s) that returns a vector of whitespace-separated substrings from the argument s.
 *
 */
// g++ -std=c++11 -g ch11.e.11_split_string_white.C  -o ch11.e.11_split_string_white.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

// this function will tell if char matches any chars in white
bool is_whitespace(char c, const string& white)
{
  for (char w: white)
    if (c == w) return true;
  return false;
}

vector<string> split(const string& s) {
  vector <string> v;
  istringstream istr{s};
  for (string str; istr>>str; ) {
    v.push_back(str);
  }
  return v;
}

vector<string> split(const string& s, const string& white) { // w - defines extra "white spaces"
  vector <string> v;
  istringstream istr{s};
  for (string str; istr>>str; ) {
    //v.push_back(str);
    // now we might have to split this one based on the string w
    bool b_extra_whites = false;
    for (char& ch: str)
      if (is_whitespace(ch, white)) {
        ch = ' ';   // convert to space
        b_extra_whites = true;
      }
    if (!b_extra_whites) {
      v.push_back(str);
    } else {
      // we put extra whites. So we need to rescan this part of the string again.
      istringstream i_sec_str{str};
      for (string ss; i_sec_str>> ss; )
        v.push_back(ss);
    }
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

  string white = "*/,-.";
  vector <string> spl_str_white = split(str,white);
  cout << endl<< "Split string using whites: \""<< white<< "\" is:" << endl;
  for (string s:spl_str_white)
    cout << s << endl;



  return 0;
}


