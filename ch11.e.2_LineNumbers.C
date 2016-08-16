//
/* Write a program that given a file name and a word outputs each line that contains that word together with the line number. Hint getline().
 */
// g++ -std=c++11 -g ch11.e.2_LineNumbers.C  -o ch11.e.2_LineNumbers.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

bool is_word_present(const string& word, const string& line ) // check if a word is present in a line
{
  istringstream is {line};
  string str;
  while (is >> str){
    if (str == word) {
      return true;
    }
  }
  return false;
}

int main (int argc, char * argv[])
{
  /*
  cout << "There are " << argc << " arguments" << endl;
  for (int i=0; i<argc; i++){
    cout << "\t Argument[" << i <<"] is " << argv[i] << endl;
  }
  */

  if (argc !=3) {
    cout << "\t The program takes a file name and a word," << endl
        << "outputs the lines containing the word with the line numbers" << endl;
    error ("we expect 2 file arguments, got", argc);
  }
  ifstream inFile{argv[1]};
  string str{argv[2]};
  cout << "\t Looking for word \"" << str << "\"" << endl;

  if (! inFile)
    error ("Can not open a file", argv[1]);

  int  line_num = 1; // will point to the line number of the next line to read.
  for (string str_line; getline(inFile,str_line);line_num++){
    if (is_word_present(str, str_line)){
      cout << line_num << ": " << str_line << endl;
    }
  }

  return 0;
}


