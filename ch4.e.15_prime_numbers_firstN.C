// find the prime numbers
// g++ -std=c++11 -g -o ch4.e.15_prime_numbers_firstN.exe ch4.e.15_prime_numbers_firstN.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"


int main ()
{
  vector <int> primes {2}; // will contain the prime numbers
  int limit{2}; // the top boundary
  cout << "Please enter the number of the smallest prime numbers you want to be found: "<< endl;
  cin >> limit;
  limit = abs(limit);
  cout << "Trying to find the first "<< limit << " prime numbers:" << endl;

  int i=3; // current number under test
  while (primes.size() < limit) {
    // test a new number i to see if it is divisible by any other prime numbers
    bool prime_flag = true;
    for (int p:primes) {
      if (i%p == 0) {
        // this is a multiple of a known prime number, continue to the next iteration
        prime_flag = false;
        break; // will stop the division loop
      }
    }
    if (prime_flag)
      primes.push_back(i);

    // prepere for the next iteration
    i+=2; // we know that any prime number above 2 will be odd
  }

  // output the results
  cout << "The primes found:\n";
  for (int p:primes) {
    cout << p << "\t";
  }
  cout << endl;
  cout << "We found " << primes.size() << " smallest prime numbers"<<endl;
  return 0;
}


