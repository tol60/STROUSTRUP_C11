/*  Write a program that accepts two file names and produces a new file that is the contents fo the first file followed
 * by the contents of the second; that is, the program concatenates the two files.
 *
 * Some interesting discussions on copying files at:
 * http://stackoverflow.com/questions/10195343/copy-a-file-in-a-sane-safe-and-efficient-way
 *
 */

// g++ -std=c++11 -g ch10.e.8_concatenate_files.C  -o ch10.e.8_concatenate_files.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"



int main ()
{
  cout << "The program will concatenate two files to produce the third one\n";
  cout <<"Please enter the first file name\n";
  string iname_one;
  if(!(cin >> iname_one) ) error("Your input was not recognized!");
  cout <<"The first file name is: " << iname_one << endl;
  ifstream ist_one{iname_one};
  if(!ist_one) error("can not open output file",iname_one);
  ist_one.exceptions(ist_one.exceptions()|ios::badbit); // throw for bad()

  cout <<"Please enter the second file name\n";
  string iname_two;
  if(!(cin >> iname_two) ) error("Your input was not recognized!");
  cout <<"The second file name is: " << iname_two << endl;
  ifstream ist_two{iname_two};
  if(!ist_two) error("can not open output file",iname_two);
  ist_two.exceptions(ist_two.exceptions()|ios::badbit); // throw for bad()

  cout <<"Please enter the resulting file name\n";
  string oname;
  if(!(cin >> oname) ) error("Your input was not recognized!");
  cout <<"The resulting file name is: " << oname << endl;

  ofstream ost{oname};
  if(!ost) error("can not open output file",oname);
  ost.exceptions(ost.exceptions()|ios::badbit); // throw for bad()

  // copy the first file
  char ch;
  ist_one.get(ch); // unformatted input
  while (ist_one){
    if(!(ost<< ch)) error("Failed ot write into file ", oname);
    ist_one.get(ch); // prepare for the next iteration (try to read the next symbol)
  }

  // copy the second file
  ist_two.get(ch); // unformatted input
  while (ist_two){
    if(!(ost<< ch)) error("Failed ot write into file ", oname);
    ist_two.get(ch); // prepare for the next iteration (try to read the next symbol)
  }

  return 0;
}


