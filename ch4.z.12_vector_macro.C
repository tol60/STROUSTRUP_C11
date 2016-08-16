// find the prime numbers using eratosthenes method
// g++ -std=c++11 -g -o ch4.z.12_vector_macro.exe ch4.z.12_vector_macro.C  2>&1 | tee tmp.txt
/* The following code from std_lib_facilities.h seems to cause
 *
 * // trivially range-checked vector (no iterator checking):
template< class T> struct Vector : public std::vector<T> {
  using size_type = typename std::vector<T>::size_type;

#ifdef _MSC_VER
  // microsoft doesn't yet support C++11 inheriting constructors
  Vector() { }
  explicit Vector(size_type n) :std::vector<T>(n) {}
  Vector(size_type n, const T& v) :std::vector<T>(n,v) {}
  template <class I>
  Vector(I first, I last) : std::vector<T>(first, last) {}
  Vector(initializer_list<T> list) : std::vector<T>(list) {}
#else
  using std::vector<T>::vector; // inheriting constructor
#endif

  T& operator[](unsigned int i) // rather than return at(i);
  {
    if (i<0||this->size()<=i) throw Range_error(i);
    return std::vector<T>::operator[](i);
  }
  const T& operator[](unsigned int i) const
  {
    if (i<0||this->size()<=i) throw Range_error(i);
    return std::vector<T>::operator[](i);
  }
};

// disgusting macro hack to get a range checked vector:
#define vector Vector
 */
#include "std_lib_facilities.h"


int main ()
{
  vector <int> primes{2,3}; // will contain the prime numbers
  vector <bool> sieve;

  cout << "The size of sieve is " << sieve.size() << endl;
  for (bool b:sieve) {
    cout << "sieve element = " << b << endl;
  }

  for (int i=0; i<sieve.size(); i++) {
    bool bValue = sieve[i];
    cout << "sieve ["<<i << "] = "<< bValue << endl;
  }

  //cout << "sieve [1] = " << sieve[1]<<endl;

    return 0;
}


