// g++ -w -Wall -std=c++11 ch17.d.1.C -o ch17.d.1.exe 2>&1 | tee tmp.txt

#include <iostream>
#include <vector>

using namespace std;

void print_array10(ostream& os, int* a) {
  for (int i=0; i<10; i++)
    os<< a[i] << "\t";
}

void print_array(ostream& os, int* a, int n) {
  for (int i=0; i<n; i++)
    os<< a[i] << "\t";
}

void print_vec(ostream& os, vector<int>& vec){
  for (int i=0; i<vec.size(); i++)
    os << vec[i] << "\t";
}

int factorial (int n){
  int tmp = n;
  cout << "factorial was called, tmp = "<< tmp << ", address of tmp (should be on the stack) is " << &tmp << endl;
  if (n==1)
    return 1;
  else
    return n*factorial(n-1);
}

int main()
{
  int* p = new int[10]{1,2,3,4,5,6,7,8,9,10};
  for (int i=0; i<10; i++)
    cout << p[i] <<"\t";
  cout << endl;
  print_array10(cout, p);
  cout << endl;
  delete[] p; // we do not need memory any more. free it

  int* pt_11 = new int[11]{100,101,102,103,104,105,106,107,108,109,110};
  for (int i=0; i<11; i++)
    cout << pt_11[i] << "\t";
  cout << endl;
  delete[] pt_11;

  int* pt_20 = new int[20]{100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119};
  print_array(cerr, pt_20, 20);
  cout << endl;
  delete[] pt_20;

  vector<int> vec = {100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119};
  cout<< "Printing vectors"<<endl;
  print_vec(cout, vec);
  cout<<endl;

  int x=7;
  int* p1 = &x;
  cout << "p1=" << p1 << ", *p1 = " << *p1 << endl;

  //int ar_sev[7] = {1,2,3,4,5,6,7};
  int* ar_sev = new int[7]{10,20,30,40,50,60,70};
  int* p2 = ar_sev;
  cout << "p2=" << p2 << ", *p2 = " << *p2 << endl;
  cout << "Printing the array at p2: ";
  print_array(cout, p2,7);
  cout << endl;

  int* p3 = p2;
  p2 = p1;
  p2 = p3;

  cout << "After the re-assignment" << endl;
  cout << "p1=" << p1 << ", *p1 = " << *p1 << endl;
  cout << "p2=" << p2 << ", *p2 = " << *p2 << endl;
  cout << "Printing the array at p2: ";
  print_array(cout, p2,7);
  cout << endl;

  delete[] p2;

  p1 = new int[10]{11,12,13,14,15,16,17,18,19,20};
  p2 = new int[10];
  for (int i=0;i<10;i++)
    p2[i] = p1[i];
  cout << "p1=" << p1 << ", *p1 = " << *p1 << endl;
  cout << "p2=" << p2 << ", *p2 = " << *p2 << endl;
  cout << "Printing the array at p2: ";
  print_array(cout, p2,10);
  cout << endl;

  delete[] p1;
  delete[] p2;

  vector<int> vec1 ={30,31,32,33,34,35,36,37,38,39};
  vector<int> vec2(10);
  for (int i=0; i<vec1.size(); i++) {
    vec2[i]=vec1[i];
  }
  cout << "vec2: ";
  for (int i=0; i<vec1.size(); i++)
      cout << vec[i] << '\t';
  cout << endl;

  cout << "Calling factorial(5) = " << factorial(5) << endl;

  cout << "size of int = " << sizeof(int) << endl;
  cout << "size of double = " << sizeof(double) << endl;
  cout << "size of bool = " << sizeof(bool) << endl;
}
