// g++ -w -Wall -std=c++11 ch17.e.3_to_lower.C -o ch17.e.3_to_lower.exe 2>&1 | tee tmp.txt
/* Write a function, void to_lower(char* s), that replaces all uppercase characters
 * in the C-style string s with their lowercase equivalents. For Example, Hello, World!, becomes hello, world!
 * Do not use any standard library functions. A C-style string is a zero-terminated array of characters,
 * so if you find a char with the value of 0 you are at the end.
 */


#include <iostream>
#include <vector>

using namespace std;

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

  *str = 'X';
  *(str+1) = 'Y';
  cout << "String: " << str << endl;
  to_lower(str);
  cout << "string: " << str << endl;
}
