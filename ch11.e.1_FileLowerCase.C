//
/* Write a program that reads a a text file and converts its input to all lower case, producing a new file.
 */
// g++ -std=c++11 -g ch11.e.1_FileLowerCase.C  -o ch11.e.1_FileLowerCase.exe 2>&1 | tee tmp.txt

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

  for (char ch; inFile.get(ch);){
    //cout << ch;
    //cout << char(tolower(ch));
    outFile << char(tolower(ch));
  }

  return 0;
}


