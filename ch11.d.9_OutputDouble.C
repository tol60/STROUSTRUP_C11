//
/* D9. Write some code to print the number 1234567.89 three times, first using defaultfloat, then fixed, then scientific forms.
 * Which output form presents the user with the most accurate representation? Explain why.
 */
// g++ -std=c++11 -g ch11.d.9_OutputDouble.C  -o ch11.d.9_OutputDouble.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"


int main ()
{
  double d_num = 1234567.89;
  cout << "The number 1234567.89 printed 3 times:" << endl;
  //cout << "\t defaultfloat "<< defaultfloat << d_num << endl;
  //cout << "\t hexfloat "<< std::defixhexfloat << d_num << endl;
  cout << "\t default: " << d_num << endl;
  cout << "\t fixed "<< fixed << d_num << endl;
  cout << "\t scientific "<< scientific << d_num << endl;

  cout << "Tryint to revert back to default" << endl;
  cout.unsetf(ios::scientific);
  cout << "\t default: " << d_num << endl;
  return 0;
}


