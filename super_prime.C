// find the super prime numbers using eratosthenes sieve method method
// g++  -g -o super_prime.exe super_prime.C  2>&1 | tee tmp.txt

//#include "std_lib_facilities.h"
#include<iostream>
#include<vector>    // this is where standard vector is defined
#include<cmath>     // we use sqrt function to calculate the limit (extra speed-up)
//#include<algorithm> // this is where sort is defined

using namespace std;  // if you don't want to type std::vector all the time

int main ()
{
  //vector <int> primes{2,3}; // will contain the prime numbers
  vector <int> primes; // will contain the prime numbers
  primes.push_back(2); // the first prime
  primes.push_back(3); // the second prime
  vector <bool> sieve;
  int limit = 2; // the top boundary
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
  //for (int p:primes) {
  //  cout << p << "\t";
  //}
  /*
  for (int p=0; p<primes.size(); ++p) {
    cout << primes[p] << "\t";
  }
  */
  cout << endl;
  cout << "We found " << primes.size() << " prime numbers between 2 and "<< limit<<endl;

  int NumPrimes = primes.size(); // number of primes found
  vector <int> super_primes;  // super primes
  for (int i=0; i<primes.size(); ++i) {
    int prime = primes[i]; // find a prime number, and then use it as an index
    if (prime <= NumPrimes){
      super_primes.push_back(primes[prime-1]);  // note that indexes in vector representation start with 0, so we need to subtract 1
    } else {
      break;  // break out of the loop, we exhausted all the primes we found.
    }
  }

  // print out super primes
  for (int p=0; p<super_primes.size(); ++p) {
    cout << super_primes[p] << "\t";
  }
  cout <<endl;
  cout << "We found " << super_primes.size() << " super prime numbers between 2 and "<< limit<<endl;

  return 0;
}


