//
/* Binary files.
 * Example that reads and writes binary files of integers.
 */
// g++ -std=c++11 -g ch11.3.2_BinaryFile.C  -o ch11.3.2_BinaryFile.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"


int main ()
{
  // open an istream for binary input from a file:
  cout << "Please enter input file name (binary format):\n";
  string iname;
  cin >> iname;
  ifstream ifs{iname, ios_base::binary}; // note: stream mode
            // binary tells the stream not to try anything clever with the bytes
  if(!ifs) error ("can't open input file ", iname);

  // open an ostream for binary output to a file:
  cout << "Please enter output file name (binary format):\n";
  string oname;
  cin >> oname;
  ofstream ofs{oname, ios_base::binary}; // note: stream mode
            // binary tells the stream not to try anything clever with the bytes
  if(!ofs) error ("can't open output file ", oname);

  vector <int> v;

  // read from the binary file:
  for (int x; ifs.read(as_bytes(x),sizeof(int));) // note: reading bytes
    v.push_back(x);

  // .. do something with v ..

  for (int x:v)
    ofs.write(as_bytes(x),sizeof(int)); // note: writing bytes

  return 0;
}


