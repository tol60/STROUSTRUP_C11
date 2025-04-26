// g++ -w -Wall -std=c++11 ch17.3.1_Pointers.C -o ch17.3.1_Pointers.exe 2>&1 | tee tmp.txt

#include <iostream>
#include <vector>

using namespace std;

void sizes(char ch, int i, int*p, double d, double* pd, string s, string* ps, bool b, bool* pb)
{
  cout << "the size of char is " << sizeof(char) <<' ' << sizeof (ch) << endl;
  cout << "the size of int is " << sizeof(int) <<' ' << sizeof (i) << endl;
  cout << "the size of int* is " << sizeof(int*) <<' ' << sizeof (p) << endl;
  cout << "the size of double is " << sizeof(double) <<' ' << sizeof (d) << endl;
  cout << "the size of double* is " << sizeof(double*) <<' ' << sizeof (pd) << endl;
  cout << "the size of string is " << sizeof(string) <<' ' << sizeof (s) << endl;
  cout << "the size of string* is " << sizeof(string*) <<' ' << sizeof (ps) << endl;
  cout << "the size of bool is " << sizeof(bool) <<' ' << sizeof (b) << endl;
  cout << "the size of bool* is " << sizeof(bool*) <<' ' << sizeof (pb) << endl;
}

int main()
{
  cout << "Hello, world!" << endl;
  int x = 17;
  int* pi = &x;     // pointer to int

  double e = 2.71828;
  double* pd = &e;  // pointer to double

  char ch = 'F';
  char* pc = &ch;   // pointer to char

  string str = "hello";
  string* ps = &str;

  bool b = false;
  bool* pb = &b;

  // vector<int> v = {1,2,3,4,5,6,7,8,9,10,11};
  vector<int> v (1000);
  cout << "the size of vector<int>(1000) is " << sizeof(v) << endl;

  cout << "pi=="<< pi << "; contents of pi==" << *pi << endl;
  cout << "pd=="<< pd << "; contents of pd==" << *pd << endl;
  cout << "pc=="<< pc << "; contents of pc==" << *pc << endl;
  cout << "ps=="<< ps << "; contents of ps==" << *ps << endl;
  cout << "pb=="<< pb << "; contents of pb==" << *pb << endl;

  sizes(ch, x, pi, e, pd, str, ps, b, pb);  // calling the function

  // pc = &str; // ERROR: can't assign string* to char*

  *pi = 27;
  *pd = 3.14159;
  *pd = *pi;

  // int i = pi; // ERROR: can't assign an int* to an int
  // pi =7;     // ERROR: cant' assign an int to an int*
  // pc = pi;   // ERROR:can't assign an int* to char*

  // pc = static_cast <char*> (pi);  // ERROR: int* and char* are not related pointer types (could convert to void*)
  pc = reinterpret_cast <char*> (pi); // OK: reinterpret_cast allows conversion of unrelated pointer types

  // pi = pd; // ERROR: can't assign double* to an int*
  // pi = static_cast<int*> (pd); // ERROR: double* and int* are not related pointer types (could convert to void*)
  pi = reinterpret_cast<int*> (pd); // OK: reinterpret_cast allows conversion of unrelated pointer types
  pi = (int*) pd;  // C-style cast


}
