// g++ -g -w -Wall -std=c++11 ch18.e.2_findx.C -o ch18.e.2_findx.exe 2>&1 | tee tmp.txt
/* 1. Write a function, char* strdup (const char*), that copies a C-style string
 *    into memory it allocates on the free store. Do not use any standard library
 *    functions. Do not use subscripting; use the dereference operator * instead.
 * 2. Write a function, char* findx(const char* s, const char*x), that finds the first
 *    occurrence of the C-style string x in s. Do not use any standard library functions.
 *    Do not use subscripting; use the dereference operator* instead.
 */

#include <iostream>


using namespace std;

char* strdup (const char* aa){
  // 1. calculate the length of the input string
  // 2. allocate the memory
  // 3. do the copy


  // calculate the length of an input string
  const char* aa_2 = aa;
  int n=1; // to account for zero that terminates a C-style string
  while (*aa_2) {n++; aa_2++;}

  char* bb = new char[n];
  char* bb_2 = bb;

  while (*aa) {
    *bb_2 = *aa;
    aa++;
    bb_2++;
  }

  // copy the zero termination symbol (last one)
  *bb_2 = *aa;
  return bb;
}

char* findx(const char* s, const char* x) {
  if (!*s && !*x) // both strings are empty
    return (char *) s;
  while (*s)  // till we hit the end of the input string
  {
    // at this point *s is non-zero (not the end of the string)
    if (*s != *x)  { // trying to match the first character of x
      // the first character of x did not match, advance
      s++;
    } else {
      // the first character matched, see if we matched the rest of the symbols
      const char* s2 = s;
      const char* x2 = x;
      while (*s2 && *x2 && *s2 == *x2){
        s2++;
        x2++;
      }
      if (*x2) { // if we did not hit the end of the short line to match = mismatch
        s++; // advance the start location in the input string
      } else {
        return (char *) s; // full match found
      }
    }
  }
  return nullptr;
}

int main()
{
  cout << "*************************************\n";
  cout << "Inside main function \n";
  cout << "*************************************\n";

  char a[] = "What a nice day!";

  cout << "a = " << a << endl;

  char* b = strdup(a);
  cout << "char* b = strdup(a); produced: \n";
  cout << b << endl;
  delete[] b;

  cout << "***************\n";
  cout <<"char* findx(const char* s, const char* x)"<<endl;

  char* input = "at";
  char* ch = findx(a,input);
  cout << "input = " << input << endl;
  if (ch)
    cout << "output = " << ch << endl;
  else
    cout << "no match found" <<endl;

  input = "bat";
  ch = findx(a,input);
  cout << "input = " << input << endl;
  if (ch)
    cout << "output = " << ch << endl;
  else
    cout << "no match found" <<endl;

  input = a;
  ch = findx(a,input);
  cout << "input = " << input << endl;
  if (ch)
    cout << "output = " << ch << endl;
  else
    cout << "no match found" <<endl;

  input ="";
  cout << "ch = findx(input,input);"<<endl;
  ch = findx(input,input);
  cout << "input = " << input << endl;
  if (ch)
    cout << "output = " << ch << endl;
  else
    cout << "no match found" <<endl;





  cout << "*************************************\n";
  cout << "main() function is done\n";
  cout << "*************************************\n";
}
