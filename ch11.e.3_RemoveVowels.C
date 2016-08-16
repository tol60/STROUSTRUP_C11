//
/* Write a program that removes all vowels from a file.
 * For example, "Once upon a time!", will become "nc pn tm!".
 * Surprisingly often, the result is still readable; try it on your friends.
 *  Input:
 *  1. File for input
 *  2. File for output
 */
// g++ -std=c++11 -g ch11.e.3_RemoveVowels.C  -o ch11.e.3_RemoveVowels.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

const string vowels {"aeiou"}; // we only keep lower case version
bool is_vowel (char ch) {
  ch = tolower(ch); // make sure we compare lower case version
  for (char v:vowels)
    if (ch == v) return true;
  return false;
}

int main (int argc, char * argv[])
{
  const int NUM_ARG_EXPECTED = 3;
  /*
  cout << "There are " << argc << " arguments" << endl;
  for (int i=0; i<argc; i++){
    cout << "\t Argument[" << i <<"] is " << argv[i] << endl;
  }
  */

  if (argc !=3) {
    cout << "\t The program takes two file names," << endl
        << "removes vowels from the first file and puts it into the second file" << endl;
    error ("we expect 2 file arguments, got", argc);
  }
  string inFile_name {argv[1]};
  string outFile_name {argv[2]};
  ifstream inFile{inFile_name};
  ofstream outFile{outFile_name};
  cout << "\t The program will try to remove vowels from  \"" << inFile_name << "\" and puts the result into \"" << outFile_name << "\"" << endl;

  if (! inFile)
    error ("Can not open a file", inFile_name );
  if (! outFile)
    error ("Can not open a file", outFile_name );

  for (char ch; inFile.get(ch);)
    if (! is_vowel(ch))
      outFile << ch;

  return 0;
}


