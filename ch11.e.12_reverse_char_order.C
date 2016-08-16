//
/* Ex12. Reverse the order of characters in a text file. For example asdfghjkl becomes lkjhgfdsa.
 * Warning: There is no really good, portable and efficient way of reading a file backwards. *
 */
// g++ -std=c++11 -g ch11.e.12_reverse_char_order.C  -o ch11.e.12_reverse_char_order.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"



int main ()
{
  cout << "The program will reverse the order of chars in a text file"<< endl;
  cout << "Please enter input file name:\n";
  string iname;
  cin >> iname;
  ifstream ifs(iname); // text file
  if (!ifs) error ("can't open input file", iname);

  cout << "Please enter output file name:\n";
  string oname;
  cin >> oname;
  ofstream ofs(oname); // text file
  if (!ofs) error ("can't open output file", oname);

  vector<char> v_char;
  for (char ch; ifs.get(ch);)
    v_char.push_back(ch);

  for (int i = v_char.size()-1; i>=0; --i)
    ofs << v_char[i];



  return 0;
}


