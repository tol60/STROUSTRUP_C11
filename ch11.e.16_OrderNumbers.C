//
/* Ex16. Write a program to read a file of whitespace-separated numbers and output them in order (lowest value first), one value per line.
 * Write a value only once, and if it occurs more then once write the count of its occurrences on its line.
 * For example, 7 5 5 7 3 117 5 should give
 * 3
 * 5  3
 * 7  2
 * 117
 *
 */
// g++ -std=c++11 -g ch11.e.16_OrderNumbers.C  -o ch11.e.16_OrderNumbers.exe 2>&1 | tee tmp.txt

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

  vector <double> v;

  for (double num; ifs>>num; ){
    v.push_back(num);
  }

  sort(v.begin(),v.end());

  for (int i=0; i<v.size(); ) { // go over all the numbers
    ofs << setw(20)<< v[i];
    int cnt = 1;
    while (i+cnt < v.size() && v[i+cnt]==v[i])
      ++cnt; // count the doubles.
    if (cnt > 1)
      ofs << setw(20) << cnt << endl; // this number occurred multiple times
    else
      ofs << endl;  // this number occurred once

    i += cnt; // increment i for the next iteration
  }


  return 0;
}


