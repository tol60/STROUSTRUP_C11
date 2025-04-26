// g++ -g -w -Wall -std=c++11 ch18.3.Copying.C -o ch18.3.Copying.exe 2>&1 | tee tmp.txt

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
 vector(const vector&);  // copy constructor: define copy
  ~vector() {delete[] elem;}

  int size() const {return sz;}             // the current size
  double get(int n) const {return elem[n];} // access: read
  void set(int n, double v) {elem[n] = v;}  // access: write

  double& operator[](int i) {return elem[i];}
  const double& operator[](int i) const {return elem[i];}
};


vector::vector(const vector& arg) // allocate elements, then initialize them by copying
  : sz{arg.sz},
    elem{new double[arg.sz]}
  {
    copy(arg.elem,arg.elem+sz,elem); // std::copy();
    cout << "copy constructor\n";
  }

ostream& operator<< (ostream&os, const vector& v) {
  for (int i=0; i<v.size(); i++)
    os << v.get(i) << ' ';
  return os;
}

void f() {
  vector v(3);    // define a vector of 3 elements
  v.set(2, 2.2);  // set v[2] to 2.2
  vector v2 = v;  // what happened here?// copy constructor
  cout << "v is located at " << &v << endl;
  cout << "v2 is located at " <<&v2 << endl;
  v.set(1,99);
  v2.set(0,88);
  cout << v.get(0) << ' ' << v2.get(1)<<endl;
  cout << "v = " << v << endl;
  cout << "v2 = " << v2 << endl;
  cout << endl;
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

  cout << "calling function f()\n";
  f();
  cout << "returned from function f()\n";
}
