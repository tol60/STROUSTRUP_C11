// g++ -Wall -std=c++11 ch17.e.5_findx.C -o ch17.e.5_findx.exe 2>&1 | tee tmp.txt
/* EX5 Write a function char* findx (const char*s, const char*x), that finds the first occurrence of the C-style string x in s.
 *
 * EX4: Write a function, char* strdup(const char*), that copies a C-style string into memory it allocates on the free store.
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

char* findx (const char* s, const char* x){
  int len_s=0;
  while(s[len_s++]); // gives the length of s, including \0 termination character
  int len_x=0;
  while(x[len_x++]); // gives the length of x, including \o termination character
  if (len_x>len_s || len_x == 1)  // guarantees no match (as the x is too long, or empty length=1)
    return (char*) &s[len_s]; // return pointer to the termination symbol of s
  for (int i=0; i< len_s-len_x + 1; i++) { // pick a starting location of s to try
    int j=0; // index into j
    while (s[i+j]==x[j] && j < len_x - 1) // we do not want to compare the terminating symbol('\0') of x
      j++;
    if (j==len_x-1)  // we do not want to compare the terminating symbol ('\0') of x
      return (char*) &s[i];  // match found;
  }

  // searched everything, did not find the match
  return (char*) &s[len_s]; // return pointer to the termination symbol of s
}

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
  char str[] = "Hello, world!";
  //const char* x = "!";
  char x[] = "d";
  cout << "str = " << str << endl;
  cout << "x = " << x << endl;
  cout << "findx(str,x) returned: " << findx(str,x) << endl;

  const char* y = "o";
  cout << "str = " << str << endl;
  cout << "y = " << y << endl;
  cout << "findx(str,y) returned: " << findx(str,y) << endl;

  char z[] = "h";
  cout << "str = " << str << endl;
  cout << "z = " << z << endl;
  cout << "findx(str,z) returned: " << findx(str,z) << endl;

  z[0]= 'H';
  cout << "str = " << str << endl;
  cout << "z = " << z << endl;
  cout << "findx(str,z) returned: " << findx(str,z) << endl;

  cout << "findx(z,z) returned: " << findx(z,z) << endl;
  cout << "findx(str,str) returned: " << findx(str,str) << endl;

}
