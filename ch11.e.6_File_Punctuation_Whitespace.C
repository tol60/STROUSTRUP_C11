//
/* Write a program that replaces punctuation with whitespace.
 * Consider . (dot), ; (semicolon), , (comma), ? (question mark), - (dash), ' (single quote) punctuation characters
 * Don't modify characters within a pair of double quotes.
 * Example:
 *   "- don't use the as-if rule."
 *   Becomes:
 *   "  don t use the as if rule "
 */
// g++ -std=c++11 -g ch11.e.6_File_Punctuation_Whitespace.C  -o ch11.e.6_File_Punctuation_Whitespace.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"


int main (int argc, char * argv[])
{
  cout << "There are " << argc << " arguments" << endl;
  for (int i=0; i<argc; i++){
    cout << "\t Argument[" << i <<"] is " << argv[i] << endl;
  }

  if (argc !=3)
    error ("we expect 2 file arguments, got", argc);

  ifstream inFile{argv[1]};
  ofstream outFile{argv[2]};

  if (! inFile)
    error ("Can not open a file", argv[1]);

  const string puncts = ".;,?-'"; // the characters (within semicolumn
  string line; // we will read one line at a time
  bool b_double_quote = false; // if true, we are inside double quotes, bypass modifications
  while (getline(inFile,line)) { // when we read the line, it is missing '\n' = endl now
    // modify the line
    for (char& ch:line) {
      if (ispunct(ch)) {
        // ispunct(c): is not a letter, digit, whitespace or individual control character
        // we restrict it further

        // first keep track of double quotes
        if (ch == '"')
          b_double_quote = ! b_double_quote;

        if (!b_double_quote) {  // only modify the string if not within double quotes
          for (char psymb:puncts) {
            if (ch == psymb){
              // match found. Do some work!
              ch = ' '; // was a reference, so we do modify line here
              break;
            }
          }
        }
      }
    }

    // do not forget to write the modified line out
    outFile << line << endl;  // extra endl (which we lost when we used getline
  }

  return 0;
}


