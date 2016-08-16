/* Make a simple table including the last name, first name, telephon number, and email address of 6 people
 * for Integers, we can set the minimum width of the output via setw() = "set field width"
 * Note:
 * cout << defaultfloat;  did not work!!
 */

// g++ -std=c++11 -g ch11.2.5_Fields.C  -o ch11.2.5_Fields.exe 2>&1 | tee tmp.txt
 
#include "std_lib_facilities.h"


int main ()
{
  int i = 123456;
  cout<< "This program will print "<<i << " several times (using different setw settings). Field size do not stick!!" << endl;
  cout << i << '|'            // no field used
      << setw(4) << i << '|'  // 123456 does not fit in a 4-char field
      << setw(8) << i << '|'  // set field width to 8
      << i << '|' << endl;    // field sizes do not stick

  double d = 1234.5;
  cout << d << '|'            // no field used
      << setw(4) << d << '|'  // 123456 does not fit in a 4-char field
      << setw(8) << d << '|'  // set field width to 8
      << d << '|' << endl;    // field sizes do not stick

  string str = "asdfg";
  cout << str << '|'            // no field used
      << setw(4) << str << '|'  // 123456 does not fit in a 4-char field
      << setw(8) << str << '|'  // set field width to 8
      << str << '|' << endl;    // field sizes do not stick

  // table
  const int lastName_Width = 10;
  const int firstName_Width = lastName_Width;
  const int phone_Width = 10;
  const int email_Width = 30;
  cout << setw(lastName_Width)<< "Andreev" << '|'
      <<setw(firstName_Width) << "Anatoli" << '|'
      << setw(phone_Width) << 4826153 << '|'
      << setw(email_Width) << "tol60@hotmail.com" << '|' << endl;
  cout << setw(lastName_Width)<< "Peterson" << '|'
      <<setw(firstName_Width) << "Brenton" << '|'
      << setw(phone_Width) << 4826873 << '|'
      << setw(email_Width) << "BrentonPeterson@hotmail.com" << '|' << endl;
  cout << setw(lastName_Width)<< "Peterson" << '|'
      <<setw(firstName_Width) << "Brenton" << '|'
      << setw(phone_Width) << 4826873 << '|'
      << setw(email_Width) << "BrentonPeterson@hotmail.com" << '|' << endl;
  cout << setw(lastName_Width)<< "Peterson" << '|'
      <<setw(firstName_Width) << "Brenton" << '|'
      << setw(phone_Width) << 4826873 << '|'
      << setw(email_Width) << "BrentonPeterson@hotmail.com" << '|' << endl;
  cout << setw(lastName_Width)<< "Peterson" << '|'
      <<setw(firstName_Width) << "Brenton" << '|'
      << setw(phone_Width) << 4826873 << '|'
      << setw(email_Width) << "BrentonPeterson@hotmail.com" << '|' << endl;
  cout << setw(lastName_Width)<< "Peterson" << '|'
      <<setw(firstName_Width) << "Brenton" << '|'
      << setw(phone_Width) << 4826873 << '|'
      << setw(email_Width) << "BrentonPeterson@hotmail.com" << '|' << endl;

  return 0;
}


