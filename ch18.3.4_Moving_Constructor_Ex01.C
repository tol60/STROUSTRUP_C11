// g++ -g -w -Wall -std=c++11 ch18.3.4_Moving_Constructor_Ex01.C -o ch18.3.4_Moving_Constructor_Ex01.exe 2>&1 | tee tmp.txt
// Example from en.cppreference.com
// Move Constructor

#include <string>
#include <iostream>
#include <iomanip>
#include <utility>

struct A
{
  std::string s;
  int k;
  A() : s("test"), k(-1) { std::cout<<"Default constructor A\n";}
  A(const A& o) : s(o.s), k(o.k) {std::cout << "Copy constructor A\n";}
  A(A&& o) noexcept :
      s(std::move(o.s)),        // explicit move of a member of class type
      //k(std::exchange(o.k, 0))  // explicit move of a member of non-class type
      k(std::move(o.k))
  {std::cout<< "Move constructor A\n"; }
};

A f(A a)
{
  std::cout<< "Entered function f\n";
  return a;
}

A g()
{
  std::cout<<"g func: entered function\n";
  A a;
  std::cout <<"g func: created a\n";
  return a;
}

int main()
{
  std::cout << "Trying to move A\n";
  A a1 = f(A()); // return by value move-constructs the target from the function parameter
  std::cout << "Before move, a1.s = \"" << a1.s << "\" a1.k = " <<a1.k << "\n";
  A a2 = std::move(a1);
  std::cout << "After move, a1.s = \"" << a1.s << "\" a1.k = " <<a1.k << "\n";

  std::cout << "Trying to experiment with g():";
  A b1 = g();

  std::cout << "\nExtra experiment, defining c1\n";
  A c1;
  std::cout << "Before the call, c1.s = \"" << c1.s << "\" c1.k = " <<c1.k << "\n";
  std::cout<< "calling A c2= f(c1):\n";
  A c2 = f(c1);
  std::cout << "After the call, c1.s = \"" << c1.s << "\" c1.k = " <<c1.k << "\n";
  std::cout << "After the call, c2.s = \"" << c2.s << "\" c2.k = " <<c2.k << "\n";
}
