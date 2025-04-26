// g++ -g -w -Wall -std=c++11 ch18.4.2_Debugging_constructors_and_destructors.C -o ch18.4.2_Debugging_constructors_and_destructors.exe 2>&1 | tee tmp.txt
// BAD case:
//   We will return vector from the function, and it will cause an extra Copy (=BAD).
// GOOD case:
//   we would not copy the data over (Move case)

#include <iostream>
#include <vector>

using namespace std;



// #############################################
struct X {  // simple test class
  int val;

  void out(const string&s, int nv)
  { cerr<<this <<"->"<<s<<":"<<val<<"("<<nv<<")\n";}

  X() {out("X()",0);val=0;}                       // default constructor
  X(int v) {out("X(int)",v); val=v;}

  X(const X& x){ out("X(X&)",x.val); val=x.val; } // copy constructor
  X& operator=(const X&a)                         // copy assignment
  {out("X::operator=()",a.val); val = a.val; return *this;}

  X(X&& x) {out("X(X&&) move constructor", x.val); val=x.val;} // move constructor
  X& operator=(X&& a)                                          // move assignment
  {out("X::operator=(X&&) move assignment", a.val); val=a.val; return *this;}

  ~X(){out("~X()",0);}                             // destructor
};

X glob(2); // a global variable
X copy(X a) {return a;}
X copy2(X a){X aa = a; return aa;}
X& ref_to(X& a){return a;}
X* make(int i) {X a(i); return new X(a);}
struct XX {X a; X b;}; // declaration of the structure. By itself, does not trigger X constructors
int main()
{
  cout << "*************************************\n";
  cout << "Inside main() function\n";
  cout << "*************************************\n";
  X loc{4}; // local variable
  X loc2{loc}; // copy constructor
  cout << "*************\n";
  cout << "loc = X{5}\n";
  loc = X{5}; // copy assignment

  cout << "*************\n";
  cout << "loc2 = copy(loc); // call by value and return\n";
  loc2 = copy(loc); // call by value and return
  cout << "*************\n";
  cout << "loc2 = copy2(loc); // call by value and return\n";
  loc2 = copy2(loc); // call by value and return

  cout << "*************\n";
  cout << "X loc3 {6}; \n";
  X loc3 {6};

  cout << "*************\n";
  cout << "X& r = ref_to(loc); // call by reference and return reference\n";
  X& r = ref_to(loc); // call by reference and return reference

  cout << "*************\n";
  cout << "delete make(7);\n";
  delete make(7);

  cout << "*************\n";
  cout << "delete make(8);\n";
  delete make(8);

  cout << "*************\n";
  cout << "vector<X> v(4);   // default values \n";
  vector<X> v(4);   // default values

  cout << "*************\n";
  cout << "X loc4; \n";
  X loc4;

  cout << "*************\n";
  cout << "X* p = new X{9};  // an X on the free store\n";
  X* p = new X{9};  // an X on the free store

  cout << "*************\n";
  cout << "delete p;\n";
  delete p;


  cout << "*************\n";
  cout << "X* pp = new X[5];  // an array of Xs on the free store\n";
  X* pp = new X[5];  // an array of Xs on the free store

  cout << "*************\n";
  cout << "delete[] pp;\n";
  delete[] pp;

  cout << "*************************************\n";
  cout << "main() function is done\n";
  cout << "*************************************\n";
}
