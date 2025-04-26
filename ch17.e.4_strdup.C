// g++ -Wall -std=c++11 ch17.e.4_strdup.C -o ch17.e.4_strdup.exe 2>&1 | tee tmp.txt
/* EX4: Write a function, char* strdup(const char*), that copies a C-style string into memory it allocates on the free store.
 * Do not use any standard library functions
 *
 * Ex3: Write a function, void to_lower(char* s), that replaces all uppercase characters
 * in the C-style string s with their lowercase equivalents. For Example, Hello, World!, becomes hello, world!
 * Do not use any standard library functions. A C-style string is a zero-terminated array of characters,
 * so if you find a char with the value of 0 you are at the end.
 */


#include <iostream>
#include <vector>

using namespace std;

char* strdup(const char* s) {
  int n=0;
  while(s[n++]); // count the characters // even if the line is empty, it will return 1 (accounting for \0 symbol)
  char* result = new char[n]; // allocate the new string
  cout << "reserving " << n << " bytes" << endl;
  // copy full string (including \0 termination symbol
  for (int i=0; i<n; i++)
    result[i]=s[i];
  return result;
}

void to_lower(char* s) {
  while (*s) {
    if (*s >= 'A' &&  *s <= 'Z')
      *s = char(*s -'A' + 'a');
    s++; // advance to next symbol
  }
}

int main()
{
  //char* str = "Hello, world!"; // this would be a constant string
  char str[] = "Hello, world!";
  //char str[] = "H";
  char couple_lett[] = "ab";
  //char long_line[] = "1234567890ABCDEF1234567890ABCDEF";// with the \0 (string termination) should bring us to 0x21 size
  //char long_line[] = "1234567890ABCDEF1234567890ABCDE"; // with the \0 (string termination) should bring us to 0x20 size
  //char long_line[] = "1234567890ABCDEF1234567890ABCD"; // with the \0 (string termination) should bring us to 0x19 size
  //char long_line[] = "1234567890ABCDEF1234567890";// 26+1 = 27 = 0x1B, but for some reason did not fit into 0x20 hole
  //char long_line[] = "12345678901234567890ABCDEF"; // 26+1 = 27 = 0x1B, but for some reason did not fit into 0x20 hole
  //char long_line[] = "12345678901234567890ABCD"; // 24+1=25 = 0x19 // did not fit in 0x20 hole
  // *******************************
  //
  //********************************
  char long_line[] = "12345678901234567890ABC"; // 23+1=24 = 0x18, // it did fit in the 0x20 hole
  //char long_line[] = "12345678901234567890"; // 20+1=21 = 0x15 fit in the 0x20 hole
  //char long_line[] = "1234567890ABCDE"; // with the \0 (string termination) should bring us to 0x10 size
  //char long_line[] = "1234567890ABCDEF"; // with the \0 (string termination) should bring us to 0x11 size
  //char long_line[] = "1234567890ABCDEF1"; // with the \0 (string termination) should bring us to 0x12 size
  //*str = 'X';
  //*(str+1) = 'Y';
  cout << "String: " << str << endl;
  to_lower(str);
  cout << "string: " << str << endl;
  cout << "the location of the str = " << (void*) str<< endl;

  const char* const_str = "ConstString"; // constant string
  //const char* const_str = "C"; // constant string
  cout << "about to duplicate const_str = " << const_str << endl;
  char* dup = strdup(const_str);// this reserves a location of 0x20, more then we need.
  cout << "const_str = " << const_str<< endl;
  cout << "the location of the const_str = " << (void*) const_str<< endl;

  cout << "dup = " << dup << endl;
  cout << "the location of the dup = " << (void*) dup<< endl;

  cout << "about to duplicate str = " << str << endl;
  char* dup_hello = strdup(str);
  cout << "dup_hello = " << dup_hello << endl;
  cout << "the location of the dup_hello = " << (void*) dup_hello<< endl;

  delete[] dup;
  cout << "about to duplicate couple_lett = " << couple_lett << endl;
  char* dup_couple_lett = strdup(couple_lett);
  cout << "dup_couple_lett = " << dup << endl;
  cout << "the location of the dup_couple_lett = " << (void*) dup_couple_lett<< endl;
  delete[] dup_couple_lett;

  cout << "about to duplicate long_line = " << long_line << endl;
  char* dup_long_line = strdup (long_line);
  cout << "dup_long_line = " << dup_long_line << endl;
  cout << "the location of the dup_long_line = " << (void*) dup_long_line<< endl;
  cout << "The size of char is " <<sizeof(char)<<endl;

  delete[] dup_hello;
  delete[] dup_long_line;
}
