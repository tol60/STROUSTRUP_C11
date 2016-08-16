//
/* Ex13. Reverse the order of words (defined as whitespace_separated strings) in a file.
 * For Example, Norwegian Blue parrot becomes parrot Blue Norwegian.
 * You are alowed to assume that all the strings from the file will fit into memory at once
 *
 * Ex12. Reverse the order of characters in a text file. For example asdfghjkl becomes lkjhgfdsa.
 * Warning: There is no really good, portable and efficient way of reading a file backwards. *
 */
// g++ -std=c++11 -g ch11.e.13_reverse_word_order.C  -o ch11.e.13_reverse_word_order.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"



int main ()
{
  cout << "The program will reverse the order of words in a string from a text file"<< endl;
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

  for (string line; getline(ifs, line); ){
    istringstream is{line};
    vector<string> v;
    for (string word; is>>word; )
      v.push_back(word);

    // ouput in the opposite order:
    for (int i=v.size()-1; i>=0; --i)
      ofs << v[i] << ' ';
    ofs << endl; // line termination.
  }



  return 0;
}


