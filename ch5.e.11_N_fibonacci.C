// Generate the first N Fibonacci numbers. Find the largest Fibonacci number that can be represented as an integer.
// g++ -std=c++11 -g -o ch5.e.11_N_fibonacci.exe ch5.e.11_N_fibonacci.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

int main ()
{
  cout << "Please enter the number of Fibonacci sequence you'd like to generate:\n";
  int N{0};
  cin >> N;
  if (!cin) {
    cout << "Your input was not recognized. Terminating\n";
    return 1; // error termination.
  } else {
    N=abs(N);
    cout << "You entered "<< N<< endl;
  }

  vector <int> Fnumbers = {1, 1}; // the first two numbers
  int ind = 0; // the
  int next = Fnumbers[ind] + Fnumbers[ind+1];
  // we will run till an integer can hold a new Fibonacci number (till we get an overflow)
  while (next>0) {
    Fnumbers.push_back(next);
    // prepare for the next iteration
    ++ind;
    next = Fnumbers[ind] + Fnumbers[ind+1];
  }

  int max_Fib = Fnumbers.size();
  cout << "Using int we can represent " << max_Fib << " Fibonacci numbers\n";
  cout << "The largest Fibonnaci number, that cab be represented by int is "<<Fnumbers[max_Fib - 1] << endl;
  if (N>max_Fib) {
    cout << "We can not produce "<<N << " Fibonacci numbers. We will print out "<< max_Fib << endl;
    N = max_Fib;
  }

  cout << "The first "<< N <<" numbers of the Fibonacci sequence:\n";
  for (int i=0; i<N; i++) {
    cout << "F["<<i+1<<"] = "<<Fnumbers[i] <<endl;
  }

  return 0;
}


