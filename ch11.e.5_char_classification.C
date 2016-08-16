//
/* Write a program that reads strings and for each string outputs the character classification of each character,
 * as defined by the character classification presented in 11.6/ Note that a character can have several classifications (e.g., x is both a letter and an alphanumeric)
 */
// g++ -std=c++11 -g ch11.e.5_char_classification.C  -o ch11.e.5_char_classification.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

int main ()
{
  cout << "Please enter a string line. Try to include numbers, tab, \'_\', ... " <<endl
      << "The code will give a C designation for each character"<<endl
      << "Once done, type Ctrl+D to terminate input (Ctrl+Z on windows)" << endl;

  string line;
  char ch;
  while (getline(cin,line) ){
    cout << "You entered: "<< line << endl;
    for (const char& ch: line) {
      cout << '\"'<< ch << '\"' << "code " << int(ch)<< " or " << (unsigned int) (ch) << ": " << endl;
      const string classif_tab = "\t"; // single tab for each classification
      if (isspace(ch)) cout << classif_tab << "isspace(c): is whitespace (\' \', '\\t', '\\n', etc.)"<< endl;
      else cout << classif_tab << '\t'<<"isspace(c) failed" << endl;
      if (isalpha(ch)) cout << classif_tab << "isalpha(c): is a letter ('a',..'z','A',..'Z') (note: not '_')" << endl;
      else cout << classif_tab << '\t'<<"isalpha(c) failed" << endl;
      if (isdigit(ch)) cout << classif_tab << "isdigit(c): is a decimal digit ('0'..'9')" << endl;
      else cout << classif_tab << '\t'<<"isdigit(c) failed" << endl;
      if (isxdigit(ch)) cout << classif_tab << "isxdigit(c): is a hexadecimal digit (decimal digit or 'a'..'f' or 'A'..'F')" << endl;
      else cout << classif_tab << '\t'<<"isxdigit(c) failed" << endl;
      if (isupper(ch)) cout << classif_tab << "isupper(c): is an uppercase letter" << endl;
      else cout << classif_tab << '\t'<<"isupper(c) failed" << endl;
      if (islower(ch)) cout << classif_tab << "islower(c): is a lowercase letter" << endl;
      else cout << classif_tab << '\t'<<"islower(c) failed" << endl;
      if (isalnum(ch)) cout << classif_tab << "isalnum(c): is a letter or a decimal digit" << endl;
      else cout << classif_tab << '\t'<<"isalnum(c) failed" << endl;
      if (iscntrl(ch)) cout << classif_tab << "iscntrl(c): is a control character (ASCII 0..31 and 127)" << endl;
      else cout << classif_tab << '\t'<<"iscntrl(c) failed" << endl;
      if (ispunct(ch)) cout << classif_tab << "ispunct(c): is not a letter, digit, whitespace or individual control character" << endl;
      else cout << classif_tab << '\t'<<"ispunct(c) failed" << endl;
      if (isprint(ch)) cout << classif_tab << "isprint(c): is printable (ASCII) ' '..'~'" << endl;
      else cout << classif_tab << '\t'<<"isprint(c) failed" << endl;
      if (isgraph(ch)) cout << classif_tab << "isgraph(c): is isalpha(c) or isdigit(c) or ispunct(c) (note: not space)" << endl;
      else cout << classif_tab << '\t'<<"isgraph(c) failed" << endl;

    }
  }
  return 0;
}


