// find the prime numbers using division to verify if a number is a prime (slow method)
// g++ -g -o prime_numbers_divide.exe prime_numbers_divide.C  2>&1 | tee tmp.txt

//#include "std_lib_facilities.h"
#include<iostream>
#include<vector>    // this is where standard vector is defined
#include<cmath>     // we use abs function
//#include<algorithm> // this is where sort is defined

using namespace std;  // if you don't want to type std::vector all the time

int main ()
{
  //vector <int> primes {2}; // will contain the prime numbers
  vector <int> primes; // will contain the prime numbers
  primes.push_back(2); // the first prime number
  int limit = 2; // the top boundary
  cout << "Please enter the maximum number you want to test to find all the prime numbers: "<< endl;
  cin >> limit;
  limit = abs(limit);
  cout << "Trying to find all the prime numbers 2.."<< limit << endl;

  for (int i=3; i<=limit; i+=2) { // we know that any prime number above 2 will be odd
    // test a new number i to see if it is divisible by any other prime numbers
    bool prime_flag = true;
    //for (int p:primes) {
    for (int p=0; p<primes.size(); ++p) {
      if (i%primes[p] == 0) {
        // this is a multiple of a known prime number, continue to the next iteration
        prime_flag = false;
        break; // will stop the division loop
      }
    }
    if (prime_flag)
      primes.push_back(i);
  }

  // output the results
  cout << "The primes found:\n";
  //for (int p:primes) {
  for (int p=0; p<primes.size(); ++p) {
    cout << primes[p] << "\t";
  }
  cout << endl;
  cout << "We found " << primes.size() << " prime numbers between 2 and "<< limit<<endl;
  return 0;
}


