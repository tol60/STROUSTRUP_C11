//
/* Ex9. Split the binary I/O program from $11.3.2 into two:
 * one program that converts an ordinary text file into binary (txt2bin) and
 * one program that reads binary and converts it to text (bin2txt)
 * Test these programs by comparing a text file with what you get by converting it to binary and back
 * Binary files.
 * Example that reads and writes binary files of integers.
 *
 * http://courses.cs.vt.edu/~cs2604/fall00/binio.html#nonchar
 *     #include <fstream.h>
    ...
    class Data {
        int    key;
        double value;
    };

    Data x;
    Data *y = new Data[10];

    fstream myFile ("data.bin", ios::in | ios::out | ios::binary);
    myFile.seekp (location1);
    myFile.write ((char*)&x, sizeof (Data));
    ...
    myFile.seekg (0);
    myFile.read ((char*)y, sizeof (Data) * 10);
 *
 */
// g++ -std=c++11 -g ch11.e.9_bin2txt.C  -o ch11.e.9_bin2txt.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"


int main ()
{
  // open an istream for binary input from a file:
  cout << "Please enter input file name (binary format):\n";
  string iname;
  cin >> iname;
  ifstream ifs{iname, ios_base::binary}; // note: stream mode
            // binary tells the stream not to try anything clever with the bytes
  //ifstream ifs{iname}; // text file

  if(!ifs) error ("can't open input file ", iname);

  // open an ostream for binary output to a file:
  cout << "Please enter output file name (text format):\n";
  string oname;
  cin >> oname;
  //ofstream ofs{oname, ios_base::binary}; // note: stream mode
            // binary tells the stream not to try anything clever with the bytes
  ofstream ofs{oname}; // text file
  if(!ofs) error ("can't open output file ", oname);

  vector <char> v;

  // read from the binary file:
  //for (int x; ifs.read(as_bytes(x),sizeof(int));) // note: reading bytes
  //  v.push_back(x);
  for (char x; ifs.read((char*)&x,sizeof(char));) // note: reading bytes
    v.push_back(x);

  // .. do something with v ..

  //for (char x:v)
  //  ofs.write((char *)&x,sizeof(char)); // note: writing bytes
  for (char x:v)
    ofs.put(x);

  return 0;
}


