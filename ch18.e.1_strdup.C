// g++ -g -w -Wall -std=c++11 ch18.e.1_strdup.C -o ch18.e.1_strdup.exe 2>&1 | tee tmp.txt
/* 1. Write a function, char* strdup (const char*), that copies a C-style string
 *    into memory it allocates on the free store. Do not use any standard library
 *    functions. Do not use subscripting; use the dereference operator * instead.
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

  cout << "*************************************\n";
  cout << "main() function is done\n";
  cout << "*************************************\n";
}
