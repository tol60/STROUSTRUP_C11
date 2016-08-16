// find the prime numbers using eratosthenes sieve method method
// g++ -std=c++11 -g -o ch4.e.12_prime_numbers_eratos.exe ch4.e.12_prime_numbers_eratos.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"


int main ()
{
  vector <int> primes{2,3}; // will contain the prime numbers
  vector <bool> sieve;
  int limit{2}; // the top boundary
  cout << "Please enter the maximum number you want to test to find all the prime numbers: "<< endl;
  cin >> limit;
  limit = abs(limit);
  cout << "Trying to find all the prime numbers 2.."<< limit << endl;
  sieve.assign(limit+1,true); // we will set true for primes. skipping even numbers. +1 to account for extra 0 entry

  const int sqrt_limit = sqrt(limit)+1; // once the prime hits this limit we don't need to mark the sieve any more
  /*
  cout << "The size of sieve is " << sieve.size() << endl;
  for (bool b:sieve) {
    cout << "sieve element = " << b << endl;
  }

  for (int i=0; i<sieve.size(); i++) {
    bool bValue = sieve[i];
    cout << "sieve ["<<i << "] = "<< bValue << endl;
  }
  */
  //cout << "sieve [1] = " << sieve[1]<<endl;

  int new_prime = 3; // new prime was already marked as a prime
  while (new_prime < limit) {
    if (new_prime <= sqrt_limit) {
      // once we hit this limit, don't need to mark any more
      int incr = new_prime*2;
      // mark the multiples of a prime. skipping the multiples of two. We start eliminating with square of a new_prime. Lower multiples were marked already
      for (int i=new_prime * new_prime; i<=limit; i+= incr){
        sieve[i] = false; // this can not be a prime
      }
    }

    // now that we marked the multiples of a prime, find a new prime
    new_prime +=2;
    while ( new_prime <=limit && sieve[new_prime] == false){
      new_prime +=2; // we go over the odd numbers. the first candidate that
    }
    if (sieve[new_prime]== true) {
      primes.push_back(new_prime); // recored the new prime.
    }
  }

  // output the results
  cout << "The primes found:\n";
  for (int p:primes) {
    cout << p << "\t";
  }
  cout << endl;
  cout << "We found " << primes.size() << " prime numbers between 2 and "<< limit<<endl;
  return 0;
}


