// Look at the headache-inducing last example of 8.4. Indent it properly and explain the meaning of each construct.
// Note that the example doesn't do anything meaningful; it is pure obfuscation/

/*
// dangerously ugly code
struct X {
void f(int x) {
struct Y {
int f() { return 1;} int m; };
int m;
m=x; Y m2;
return f(m2.f());}
int m; void g(int m) {
if (m) f(m+2); else {
g(m+2); }}
X() {} void m3() {
}

void main() {
X a; a.f(2); }
};

 */
// g++ -std=c++11 -g -o ch9.e.4_obfuscation.exe ch9.e.4_obfuscation.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

struct X {
  void f(int x) {
    struct Y {
      int f() { return 1;}
      int m;
    };
    int m;
    m=x; Y m2;
    return f(m2.f());
  }
  int m;
  void g(int m) {
    if (m)
      f(m+2);
    else {
      g(m+2);
    }
  }
  X() {}
  void m3() {
  }

  void main() {
    X a;
    a.f(2);
  }
};


