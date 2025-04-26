// g++ -w -Wall -std=c++11 ch17.5.6_AccessToElements.C -o ch17.5.6_AccessToElements.exe 2>&1 | tee tmp.txt

#include <iostream>

using namespace std;

class vector {
  int sz;       // a size
  double* elem; // a pointer to the elements
public:
  vector(int s):sz{s}, elem{new double[s]} {/* */} // constructor
  ~vector(){delete[] elem;}                 // destructor
  
  int size() const {return sz;}             // the current size
  
  double get(int n) {return elem[n];}       // access: read
  void set(int n, double v) {elem[n] = v;}  // access: write
  
  double& operator[](int i) {return elem[i];}
  const double& operator[](int i) const {return elem[i];}
};

int main()
{
  cout << "Trying a simple vector class" << endl;
  vector vec(5);
  for (int i=0; i<vec.size(); ++i){
    vec.set(i,i*1.1);
  }  cout << "Function f2 end \n";
  cout << endl;
  for (int i=0; i<vec.size(); ++i)
    cout << "vec["<<i<<"] == " << vec.get(i) << endl;
  
  vec[1] = 5.7;
  vec[4] = vec[2];
  cout << "we just re-assigned vec[1] and vec[4]" << endl;
  for (int i=0; i<vec.size(); ++i)
      cout << "vec["<<i<<"] == " << vec.get(i) << endl;
  
  vector* pt = new vector(4);
  cout << "vector* pt = new vector(4)" << endl;
  cout << "pt->size() = " << pt->size() << endl;
  cout << "pt->get(3) = " << pt->get(3) << endl; 
  pt->set(3,7.5);
  cout << "pt->get(3) = " << pt->get(3) << endl; 
}
