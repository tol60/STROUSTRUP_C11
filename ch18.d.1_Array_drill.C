// g++ -g -w -Wall -std=c++11 ch18.d.1_Array_drill.C -o ch18.d.1_Array_drill.exe 2>&1 | tee tmp.txt
/* Array drill
 * 1. Define a global int array ga of ten ints initialized to 1,2,4,8, 16, etc.
 * 2. Define a function f() taking an int array argument and an int argument indicating
 *    the number of elements in the array.
 * 3. In f():
 *    a. Define a local int aray la of ten ints.
 *    b. Copy the values from ga into la
 *    c. print out the elements of la
 *    d. Define a pointer p to int and initialize it with an array allocated on the free store
 *       with the same number of elements as the argument array.
 *    e. Copy the values from the argument array into the free-store array.
 *    f. Print the elements of the free-store array
 *    g. Deallocate the free-store array.
 *  4. In main():
 *    a. Call f() with ga as its argument
 *    b. Define an array aa with  ten elements, and initialize it with the first ten
 *       factorial values (1, 2*1, 3*2*1,4*3*2*1, etc.).
 *    c. Call f() with aa as its argument
 */

#include <iostream>

using namespace std;

int ga[10] = {1,2,4,8,16,32,64,128,256,512};

void f(const int ar[], int n) // int ar[] <=> int* ar
{
  int la[10]; // a. Define a local int aray la of ten ints.

  // b. Copy the values from ga into la
  for (int i=0; i<10; ++i) {
    la[i] = ga[i];
  }

  // c. print out the elements of la
  for (int i=0; i<10; ++i )
    cout << "la["<<i<<"] = "<< la[i] << endl;

  // d. Define a pointer p to int and initialize it with an array allocated on the free store
  //       with the same number of elements as the argument array.
  int* p = new int[n];

  // e. Copy the values from the argument array into the free-store array.
  for (int i=0; i<n; ++i)
     p[i] = ar[i];

  // f. Print the elements of the free-store array
  for (int i=0; i<n; ++i)
    cout << "p["<<i<<"] = "<< p[i] << endl;

  // g. Deallocate the free-store array.
  delete[] p;

}

int main()
{
  cout << "*************************************\n";
  cout << "Inside main function \n";
  cout << "*************************************\n";

  //  a. Call f() with ga as its argument
  f(ga,10);

  // b. Define an array aa with  ten elements, and initialize it with the first ten
  //       factorial values (1, 2*1, 3*2*1,4*3*2*1, etc.).
  int aa[10];
  int fac = 1;
  for (int i=0; i<10; ++i) {
    fac *= i+1;
    aa[i] = fac;
  }

  // c. Call f() with aa as its argument
  f(aa,10);

  cout << "*************************************\n";
  cout << "main() function is done\n";
  cout << "*************************************\n";
}
