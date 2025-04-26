// g++ -g -w -Wall -std=c++11 ch18.3.4_Moving_Good.C -o ch18.3.4_Moving_Good.exe 2>&1 | tee tmp.txt
// BAD case:
//   We will return vector from the function, and it will cause an extra Copy (=BAD).
// GOOD case:
//   we would not copy the data over (Move case)

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
  vector(const vector&);            // copy constructor: define copy
  vector& operator=(const vector&); // copy assignment
  ~vector() {delete[] elem;}

  vector (vector&& a);            // move constructor
  vector& operator=(vector&&);  // move assignment

  int size() const {return sz;}             // the current size
  double get(int n) const {return elem[n];} // access: read
  void set(int n, double v) {elem[n] = v;}  // access: write

  double& operator[](int i) {return elem[i];}
  const double& operator[](int i) const {return elem[i];}
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

void f() { // using copy constructor
  cout << "Function f begin \n";
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

  cout << "Trying to assign a vector to itself\n";
  vector w(5);
  w.set(0,10);
  w.set(4,14);
  cout << "w = " << w << endl;
  cout << "w is located at " << &w << endl;
  cout << "w[0] is located at " << &w[0] << endl;
  w = w; // self-assignment
  cout << "after self-assignment, w = " << w << endl;
  cout << "w is located at " << &w << endl;
  cout << "w[0] is located at " << &w[0] << endl;

  cout << "Function f end \n";
  cout << endl;
}

void f2() { // using copy assignment
  cout << "Function f2 begin \n";
  vector v(3); // define a vector of 3 elements
  v.set(0, 100.001);
  v.set(2, 2.22);
  vector v2(4);
  v2 = v; // assignment: what happens here? // right now, problem
  cout << "v = " << v << endl;
  cout << "v2 = " << v2 << endl;

  cout << "Trying to assign a vector to itself\n";
  vector w(5);
  w.set(0,10);
  w.set(4,14);
  cout << "w = " << w << endl;
  cout << "w is located at " << &w << endl;
  cout << "w[0] is located at " << &w[0] << endl;
  w = w; // self-assignment
  cout << "after self-assignment, w = " << w << endl;
  cout << "w is located at " << &w << endl;
  cout << "w[0] is located at " << &w[0] << endl;
  cout << "Function f2 end \n";
  cout << endl;
}

vector f3() {
  // return a vector (by value)
  // BAD case: we would have to copy all the data over (Copy case)
  // GOOD case: we would not copy the data over (Move case)
  cout << "Function f3 begin (Copy | Move case) \n";
  // constexpr int limit = 100;
  int limit = 100;
  vector v(limit);
  for (int i=0; i<limit; i++)
    v[i] = i + 0.1;

  cout << "v is located at " << &v << endl;
  cout << "v[0] is located at " << &v[0] << endl;
  cout << "Function f3. About to return a vector \n";
  cout << endl;
  return v;
}

int main()
{
  /*
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

  cout << "calling function f2()\n";
  f2();
  cout << "returned from function f2()\n";

  cout << endl;
  cout << "********************\n";
  cout << "calling f3(); Result will be dropped\n";
  f3();
  cout << "returned from function f3()\n";

*/

  cout << endl;
  cout << "********************\n";
  cout << "********************\n";
  cout << "calling\n vector v3 = f3(); \n Result will be assigned to a new vector\n Copy elision\n";
  vector v3 = f3();
  cout << "v3 is located at " << &v3 << endl;
  cout << "v3[0] is located at " << &v3[0] << endl;
  cout << "returned from function f3()\n";


  cout << endl;
  cout << "********************\n";
  cout << "********************\n";
  cout << "********************\n";

  vector v4(4);
  cout << "created v4(4)\n";
  cout << "v4 is located at " << &v4 << endl;
  cout << "v4[0] is located at " << &v4[0] << endl;
  cout << "calling\n v4=f3(); \nResult will be assigned to a new vector\n";
  v4 = f3();
  cout << "v4 is located at " << &v4 << endl;
  cout << "v4[0] is located at " << &v4[0] << endl;
  cout << "returned from function f3()\n";

}
