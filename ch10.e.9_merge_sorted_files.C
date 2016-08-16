/*  Write a program that takes two files containing sorted whitespace-separated words and merges them, preserving order.
 *
 */

// g++ -std=c++11 -g ch10.e.9_merge_sorted_files.C  -o ch10.e.9_merge_sorted_files.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"



int main ()
{
  cout << "The program will take two files containing sorted whitespace-separated words and merges them, preserving order.\n";
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

  string st_one;
  string st_two;

  bool flag_one;
  bool flag_two;
  // it will be set to true if the write was successful
  flag_one = (ist_one>> st_one);
  flag_two = (ist_two>>st_two);

  while (flag_one && flag_two) { // we have input from both files
    if (st_one <= st_two) {  // move the file from the first file
      ost << st_one << ' ';
      flag_one = (ist_one>> st_one);
    } else {
      ost << st_two << ' ';
      flag_two = (ist_two>>st_two);
    }
  }

  // at this point we will have data from (at most) one file.
  if (flag_one) { // it means only words from the first file are left.
    ost << st_one << ' ';
    while (ist_one>> st_one)
      ost << st_one << ' ';
  }

  if (flag_two) {// it means only words from the second file are left.
    ost << st_two << ' ';
    while (ist_two>>st_two)
      ost << st_two << ' ';
  }

  return 0;
}


