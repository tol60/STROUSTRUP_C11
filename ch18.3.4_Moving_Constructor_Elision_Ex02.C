// g++ -g -w -Wall -std=c++11 ch18.3.4_Moving_Constructor_Elision_Ex02.C -o ch18.3.4_Moving_Constructor_Elision_Ex02.exe 2>&1 | tee tmp.txt
// Example from en.cppreference.com
// Move Constructor

#include <iostream>
#include <vector>

struct Noisy
{
  Noisy() {std::cout << "constructed\n";}
  Noisy(const Noisy&) {std::cout<< "copy-constructed\n";}
  Noisy(Noisy&&) {std::cout << "move-constructed\n";}
  ~Noisy() {std::cout << "destructed\n";}
};

std::vector<Noisy> f() {
  std::vector<Noisy> v = std::vector<Noisy>(3); // copy elision when initializing v
                                                // from a temporary (until C++17)
                                                // from a prvalue (since C++17)
  return v; // NRVO from v to the result object (not guaranteed, even in C++17)
            // if optimization is disabled, the move constructor is called
            // NRVO = "Named Return Value Optimization
}

void g(std::vector<Noisy> arg) {
  std::cout << "arg.size() = " << arg.size() << '\n';
}


int main()
{
  std::vector<Noisy> v = f(); // copy elision in initialization of v
                              // from the temporary return by f() (until C++17)
                              // from a prvalue f() (since C++17)

  g(f());                     // copy elision in initialization of v
                               // from the temporary return by f() (until C++17)
                               // from a prvalue f() (since C++17)
}
