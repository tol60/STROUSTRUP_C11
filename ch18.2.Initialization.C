// g++ -w -Wall -std=c++11 ch18.2.Initialization.C -o ch18.2.Initialization.exe 2>&1 | tee tmp.txt

#include <iostream>

using namespace std;

class vector {
  int sz;       // the size
  double* elem; // a pointer to the elements
public:
  vector(int s) // constructor (s is the element count)
    :sz{s},elem{new double[s]} // uninitialized memory
  {
    for (int i=0; i<sz; ++i) elem[i]=0.0; // initialize
  }

  vector(initializer_list<double> lst)    //  initializer-list constructor
    :sz{lst.size()},elem{new double[sz]}  // uninitialized memory
    {
      copy(lst.begin(),lst.end(),elem);   // initialize (using std::copy())
    }
  ~vector() {delete[] elem;}
  int size() const {return sz;}
  double get(int i) const {return elem[i];}
};

ostream& operator<< (ostream&os, const vector& v) {
  for (int i=0; i<v.size(); i++)
    os << v.get(i) << ' ';
  return os;
}

int main()
{
  vector va(5);
  cout << "va = {"<< va << "}\n";

  vector vb{-1.1, 2.2, 3};
  cout << "vb = {"<< vb << "}\n";

  // some trivia questions:
  double a[4] = {1.1,2.22,3.33,4.444};
  double b = 2[a];  // E1[E2] = *(E1+E2) = *(E2+E1) = E2[E1]
  cout << "b = " << b << endl;
}
