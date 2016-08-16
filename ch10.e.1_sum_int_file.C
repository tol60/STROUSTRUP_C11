//
/* Write a program that produces the sum of all the numbers in a file of whitespace-separated integers.
 */
// g++ -std=c++11 -g ch10.e.1_sum_int_file.C  -o ch10.e.1_sum_int_file.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

int main ()
{
  // prompt the user for the entrance:
  cout << "Please enter the file name: \n";
  string iname;
  cin >> iname;
  ifstream ist{iname}; // ist is an input for the file named name
  if (!ist) error ("can't open input file ", iname);

  vector <int> numbers;
  int sum = 0;
  for (int i; ist >> i; ){
    numbers.push_back(i); // not really necessary for this case
    sum +=i;
  }

  cout << "Numbers read from " << iname << " file:" << endl;
  for (int i:numbers){
    cout << i << " ";
  }
  cout << endl;

  cout << "The sum of all the integers = " << sum << endl;
  return 0;
}


