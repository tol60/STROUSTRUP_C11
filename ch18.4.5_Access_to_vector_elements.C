// g++ -g -w -Wall -std=c++11 ch18.4.5_Access_to_vector_elements.C -o ch18.4.5_Access_to_vector_elements.exe 2>&1 | tee tmp.txt


#include <iostream>

using namespace std;

class vector {
  int sz;       // the size
  double* elem; // a pointer to the elements
public:
  explicit vector(int s) // constructor (s is the element count)
    :sz{s},elem{new double[s]} // uninitialized memory
  {
    for (int i=0; i<sz; ++i) elem[i]=0.0; // initialize
  }

  vector(initializer_list<double> lst)    //  initializer-list constructor
    :sz{lst.size()},elem{new double[sz]}  // uninitialized memory
    {
      copy(lst.begin(),lst.end(),elem);   // initialize (using std::copy())
    }
  vector(const vector&);            // copy constructor: define copy
  vector& operator=(const vector&); // copy assignment
  ~vector() {delete[] elem;}

  vector (vector&& a);            // move constructor
  vector& operator=(vector&&);  // move assignment

  int size() const {return sz;}             // the current size
  double get(int n) const {return elem[n];} // access: read
  void set(int n, double v) {elem[n] = v;}  // access: write

  double& operator[](int i) {return elem[i];}
  //const double& operator[](int i) const {return elem[i];}
  double operator[](int i) const {return elem[i];} // for a bigger structure should return const X& (const reference)

  // double operator[](int n) { return elem[n];} // return element (experiment, bugged)
  // double* operator[](int n) { return &elem[n];} // return element (works, but ugly)

};

// copy constructor: define copy
vector::vector(const vector& arg) // allocate elements, then initialize them by copying
  : sz{arg.sz},
    elem{new double[arg.sz]}
  {
    copy(arg.elem,arg.elem+sz,elem); // std::copy();
    cout << "copy constructor\n";
  }

// copy assignment
vector& vector::operator=(const vector& a) {
  // make this vector a copy of vector a
  double* p = new double[a.sz]; // allocate new space
  copy(a.elem,a.elem+a.sz,p);   // copy elements to newly allocated location
  delete[] elem;  // deallocate old space
  elem = p;       // now we can reset elem
  sz = a.sz;
  cout << "copy assignment \n";
  return *this; // return a self-reference
}

// move constructor
vector::vector (vector&& a)
  :sz{a.sz}, elem {a.elem}  // copy a's elem and sz
  {
    cout << "move constructor\n";
    a.sz = 0;         // make a the empty vecotr
    a.elem = nullptr;
  }

// move assignment
vector& vector::operator=(vector&& a)
{
  cout << "move assignment\n";
  delete[] elem;    // deallocate old space
  elem = a.elem;    // copy a's elem and sz
  sz = a.sz;
  a.elem = nullptr; // make a the empty vecotr
  a.sz = 0;
  return *this;     // return a self-reference
}

ostream& operator<< (ostream&os, const vector& v) {
  for (int i=0; i<v.size(); i++)
    os << v.get(i) << ' ';
  return os;
}

void f(const vector& cv ) {
  cout << "function f was called."<<endl;
  double d = cv[1]; // need to have const version of operator[] defined
  // cv[1] = 2.0;      // error, as it should be
}

void ff(const vector& cv, vector& v ) {
  cout << "function f was called."<<endl;
  double d = cv[1]; // need to have const version of operator[] defined
  // cv[1] = 2.0;      // error, as it should be
  double d2 = v[1];  // fine (uses the non-const[])
  v[1] = -3.0;       // fine (uses the non-const[])
}

int main()
{
  cout << "*************************************\n";
  cout << "Inside main function \n";
  cout << "*************************************\n";

  // double operator[](int n) { return elem[n];} // return element (experiment, bugged)
  // vector v(10);
  // double x = v[2];
  // v[3] = x;  // error: lvalue required as left operand of assignment

  // double* operator[](int n) { return &elem[n];} // return element (works, but ugly)
  // vector v(10);
  // for (int i=0;i<v.size(); ++i) { // works but too ugly
  //   *v[i]=i;
  //   cout << *v[i] << endl;
  // }

  // double& operator[](int n) {return elem[n];}
  vector v(10);
  for (int i=0;i<v.size(); ++i) { // works!
    v[i]=i; // v[i] returns a refence to element i
    cout << v[i] << endl;
  }

  ff (v,v);
  cout << "Vector v:\n";
  cout << v << endl;


  cout << "*************************************\n";
  cout << "main() function is done\n";
  cout << "*************************************\n";
}
