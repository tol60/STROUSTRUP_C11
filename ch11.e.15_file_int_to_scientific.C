//
/* Ex15. Write a program that reads a file of whitespace-separated numbers and
 * outputs a file of numbers using scientific format and precision 8 in four fields of 20 characters per line.
 *
 */
// g++ -std=c++11 -g ch11.e.15_file_int_to_scientific.C  -o ch11.e.15_file_int_to_scientific.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"



int main ()
{
  const int numb_per_line = 4; // number of integers per line:
  cout << "The program will read a file of whitespace-separated numbers and generate a file of numbers using scientific format and precision 8 in four fields of 20 characters per line"<< endl;

  cout << "Please enter input file name:\n";
  string iname;
  cin >> iname;
  ifstream ifs(iname); // text file
  if (!ifs) error ("can't open input file", iname);

  cout << "Please enter output file name:\n";
  string oname;
  cin >> oname;
  ofstream ofs(oname); // text file
  if (!ofs) error ("can't open output file", iname);

  ofs << scientific << setprecision(8);
  int line_cnt = 0; // we will use it to count the number of char on the given line
  for (double num; ifs>>num; ){
    ofs << setw(20) << num;
    ++line_cnt;
    if (line_cnt == numb_per_line) {
      ofs << endl;
      line_cnt = 0;
    }
  }

  if (line_cnt) // we might need to output the final endl
    ofs << endl;

  return 0;
}


