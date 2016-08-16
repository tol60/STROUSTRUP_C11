// EX13: Write a function that takes a vector<string> arguments and
/*
     returns a vector<int> containing the number of characters in each string.
     Also find the longest and the shortest string and the lexicographically first and last string.
     How many separate function would you use for these tasks?
*/

// g++ -std=c++11 -g -o ch8.e.13_string_vector_count.exe ch8.e.13_string_vector_count.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"
struct extriemes_S {
  string shortest; // or lexicographically first
  string longest; // or lexicographically last
};

// takes a vector of strings, and returns lexicographically first and last string (via extriemes_S structure)
extriemes_S lexi_extriemes (const vector<string>& str_v){
  extriemes_S result{"",""}; // first/last strings
  if (str_v.size() == 0)
    return result;  // if the input was empty

  // we are guaranteed that the vector contains at least one element
  result.shortest = result.longest = str_v[0];
  for (int i=1; i<str_v.size(); ++i){ // start from the second element (index 1)
    const string & str = str_v[i]; // trying to use a reference

    // check if extremes need to be updated
    if (str<result.shortest)
      result.shortest = str;

    if (str>result.longest)
      result.longest = str;
  }
  return result;
}

/*
// takes a vector of strings, and return a vector of int (number of symbols in a string)
void string_v_count (const vector<string>& str_v, vector<int> & count_v) {
  count_v.clear();
  for (auto s:str_v)
    count_v.push_back(s.length());
}
*/


// takes a vector of strings, and return a vector of int (number of symbols in a string).
// Also returns the shortest and the longest string
extriemes_S string_v_count (const vector<string>& str_v, vector<int> & count_v) {
  extriemes_S result{"",""}; // shortest/longest strings
  count_v.clear();
  if (str_v.size() == 0)
    return result;  // if the input was empty

  // we are guaranteed that the vector contains at least one element
  result.shortest = result.longest = str_v[0];
  int min = str_v[0].length();
  int max = min;
  count_v.push_back(min); // record the very first string length (index 0)
  for (int i=1; i<str_v.size(); ++i){ // start from the second element (index 1)
    const string & str = str_v[i]; // trying to use a reference
    int len = str.length();
    count_v.push_back(len); // record the length

    // check if extremes need to be updated
    if (len<min){
      result.shortest = str;
      min = len;
    }
    if (len>max) {
      result.longest = str;
      max = len;
    }
  }

  return result;
}

// A function prints a vector of strings (the label first) to cout
void print(const string& str, const vector<string>& v) {
  cout << str;  // label
  for (int i=0; i<v.size(); i++)
    cout << "\"" <<v[i]<<"\" ";

  cout << endl; // get to a new line after we complete the output
}

// A function prints a vector of int (the label first) to cout
void print(const string& str, const vector<int>& v) {
  cout << str;  // label
  for (int i=0; i<v.size(); i++)
    cout << v[i]<<" ";

  cout << endl; // get to a new line after we complete the output
}

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
  // EX13:
  vector <string> v {"one", "two = 2", "three", "abcd", "four", "three", "dc", "five","two = 1", "two = 5","three"};
  vector <int> cnt_v;
  extriemes_S extr = string_v_count(v, cnt_v);
  print("v = ", v);
  print("cnt_v = ", cnt_v);
  cout << "The shortest string is: \"" << extr.shortest << "\"\n";
  cout << "The longest string is: \"" << extr.longest << "\"\n";
  extr = lexi_extriemes(v);
  cout << "Lexicographically first string is: \"" << extr.shortest << "\"\n";
  cout << "Lexicographically last string is: \"" << extr.longest << "\"\n";

  /* Ex12
  vector <string> v {"one", "two = 2", "three", "four", "three","five","three"};

  cout <<"print_until_ss \n";
  print_until_s (v, "three");
  cout <<endl;

  cout <<"print_until_ss \n";
  print_until_ss (v, "three");
  */
  return 0;
}
