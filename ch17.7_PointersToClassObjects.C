// g++ -w -Wall -std=c++11 ch17.7_PointersToClassObjects.C -o ch17.7_PointersToClassObjects.exe 2>&1 | tee tmp.txt

#include <iostream>

using namespace std;

class vector {
  int sz;       // a size
  double* elem; // a pointer to the elements
public:
  vector(int s):sz{s}, elem{new double[s]} {cout<<"Vector constructor\n";} // constructor
  ~vector(){cout<<"Vector destructor\n";delete[] elem;}                 // destructor
  
  int size() const {return sz;}             // the current size
  
  double get(int n) {return elem[n];}       // access: read
  void set(int n, double v) {elem[n] = v;}  // access: write
  
  double& operator[](int i) {return elem[i];}
  const double& operator[](int i) const {return elem[i];}
};

int main()
{
  
  cout<< "vector* pt = new vector(4);" << endl;
  vector* pt = new vector(4);
  cout << "pt = " << pt << endl;
  cout << "Assign some elements"<<endl;
  pt->set(1,1.1);
  (*pt)[2]=2.2;
  pt->set(3,3.3);
  cout << "Vector was constructed" << endl;
  for (int i=0; i<pt->size(); ++i)
    cout << "pt->get(i) = " << pt->get(i) << endl;
  cout << endl << "About to delete pt" << endl;
  delete pt;

  cout << endl << "vector* pt_b = new vector(4);" << endl;
  vector* pt_b = new vector(4);
  cout << "pt_b = " << pt_b << endl;
  cout << "Did not do the assignments, but expect non-zero leftovers from prev exp" << endl;
  for (int i=0; i<pt_b->size(); ++i)
    cout << "pt_b->get(i) = " << pt_b->get(i) << endl;

  cout << "Will skip the deletion of the pointer. The Desturctor will NOT BE CALLED!"<< endl;
  cout << "end of test" << endl;
}
