//
/* Write a program called multi_input.cpp that prompts the user to enter several integers in any combination of octal, decimal or hexadecimal,
 * using the 0 and 0x base suffixes; interpret the numbers correctly; and convert them to decimal form.
 * Then your program should output the values in properly spaced columns like this:
 *    0x43 hexadecimal  converts to  67 decimal
 *    0123 octal        converts to  83 decimal
 *      65 decimal      converts to  65 decimal
 */
// g++ -std=c++11 -g ch11.e.4_multi_input.C  -o ch11.e.4_multi_input.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

enum class NumBase { dec, hex, oct};
const vector<string> num_base_tbl {"decimal", "hexadecimal", "octal"};
ostream& operator << (ostream& os, NumBase nb) {
  return os << num_base_tbl[int(nb)];
}

struct StorageCont {
  NumBase num_base; // base that was recorded on the input
  int num_value; // value
  string str; // initial string
  StorageCont (NumBase nb, int val, string str) :num_base{nb}, num_value{val}, str{str} {};
};

vector <StorageCont> stor_cont; // we will use this to store the entries

int main ()
{
  cout << "Please enter several numbers in decimal, hexadecimal and octal." <<endl
      << "Start the number with 0 to indicate octal, 0x to indicate hexadecimal"<<endl
      << "Once done, type Ctrl+D to terminate input (Ctrl+Z on windows)" << endl;
  /*
  int d = 0;
  cin.unsetf(ios::dec); // do not assume decimal (so that 0x can mean hex)
  while (cin>> d) {
    cout << "\t You entered " << d << endl;
  }
  */

  string str;
  char ch;
  while (cin>> str) {

    cout << "You entered: "<< str << endl;

    istringstream is{str};

    NumBase base = NumBase::dec;
    int num = 0;

    is.get(ch);  // get the first char to interrogate to see if it starts with 0 or 0x

    if (!is) {
      cout << "empty string detected. Terminating" << endl;
      break;
    }

    if (! isdigit(ch)) {
      cout << "You entered \""<< str<< "\" which is not a number. Terminating" << endl;
      break;  // unrecognized symbol
    }

    if (ch == '0'){ // can have decimal 0, start of an octal number, or start of hex number (0x)
      if (is.get(ch)) { // Do we have another digit?
        if (tolower(ch) == 'x') { // should be hexadecimal
          base = NumBase::hex;
        } else {
          base = NumBase::oct;
        }
      } else { // no digit after => decimal 0

      }
    }

    // we determined the base.
    istringstream conv_stream {str};
    conv_stream.unsetf(ios::dec); // do not assume decimal (so that 0x can mean hex)
    conv_stream>> num;  // this should contain the number.
    if (! conv_stream) {
      cout<< "Conversion failed. This is not a number. Terminating." << endl;
      break;
    }
    stor_cont.push_back(StorageCont(base, num, str));
    //    cout << str<< "\t" << base << " converts to " << setw(8) << num << " decimal" << endl;
  }

  for (StorageCont cont:stor_cont ){
    cout << cont.str<< "\t" << cont.num_base <<"\t";
    if (cont.num_base != NumBase::hex)
      cout << "\t"; // an extra tab to align the table
    cout << "converts to " << setw(8) << cont.num_value << " decimal" << endl;
  }
  return 0;
}


