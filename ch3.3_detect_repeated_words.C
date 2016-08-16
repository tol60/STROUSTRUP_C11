// Detect repeating words from a string of standard input
// g++ -std=c++11 -g -o ch3.3_detect_repeated_words.exe ch3.3_detect_repeated_words.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"
int main ()
{
  cout << "Please enter your text line to find repeated words:\n";
  int number_of_words = 0;
  string previous = " "; // cin drops spaces, so this will not match any character we get
  string current; // current word
  while (cin >> current ){ // read one word at a time (from a stream of words)
    ++number_of_words;
    if (previous == current)
      cout << "word number " << number_of_words
        << " repeated: " << current << endl;
    previous = current;
  }
  return 0;
}
