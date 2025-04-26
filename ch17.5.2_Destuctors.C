// g++ -w -Wall -std=c++11 ch17.5.2_Destuctors.C -o ch17.5.2_Destuctors.exe 2>&1 | tee tmp.txt

#include <iostream>
#include <vector>

using namespace std;

template<class T> class Vector_ref{
  vector<T*> v;  // all pointers
  vector<T*> owned; // we would need to delete the objects pointed to by these pointers
public:
  Vector_ref(){}  // constructor
/*
  Vector_ref(T* a, T* b=0, T* c=0, T* d=0)
  {
      if (a) push_back(a);
      if (b) push_back(b);
      if (c) push_back(c);
      if (d) push_back(d);
  }
*/
  ~Vector_ref(){
    cout << "From destructor in Vector_ref. About to destroy owned objects" <<endl;
    for (int i=0; i<owned.size(); i++) delete owned[i];
    cout << "From destructor in Vector_ref. Finished" << endl;
  }

  void push_back(T& s) {v.push_back(&s);}
  void push_back(T* p) {v.push_back(p); owned.push_back(p);}

  T& operator[](int i) {return *v[i];}
  const T& operator[](int i) const {return *v[i];}
  int size() const {return v.size();}
};

class Shape {
public:
  Shape(){cout<<"Constructor Shape" << endl;}
  virtual ~Shape(){cout<<"Destructor Shape" << endl;}
  virtual string cl_type() const {return "I am of type Shape";}

  //Shape(const Shape&) = delete;  // prevent copying
  Shape(const Shape& ss) {
    class_name = ss.class_name;
    cout << "Copy constructor" <<  endl;
  }
  // Shape& operator = (const Shape&) = delete;  // prevent copy assignment
  /*
  Shape& operator = (const Shape& ss) {  // a bit clumsy. Not sure if there is a better way to represent this.
    cout << "Copy assignment" << endl;
    Shape new_sh(ss);
    return new_sh;
  }
  */
protected:
  string class_name {"Shape: top class"};
};

struct Circle : Shape {
  Circle(int rr) // constructor
  :r{ rr }
  {
    class_name = "Circle";
    cout<<"Constructor " << class_name << endl;
  }
  ~Circle(){cout<<"Destructor " << class_name << endl;}
  // string cl_type() const {return "I am of type " + class_name;}
  string cl_type() const override {return "I am of type Circle, class_name = " + class_name;}
private:
  int r;
};

struct Lines : Shape {
  Lines () // constructor
  {
    class_name = "Lines";
    cout<<"Constructor " << class_name << endl;
  }
  ~Lines(){cout<<"Destructor " << class_name << endl;}
  // string cl_type() const {return "I am of type " + class_name;}
  string cl_type() const override {return "I am of type Lines, class_name = " + class_name;}
};

void call(const Shape& sh)
{
  cout << "function call: " << sh.cl_type() << endl;
}

int main()
{
  cout << "This should demonstrate the destructor call order" << endl;
  Shape sh;
  Circle cir(4);
  cout << "cir: " << cir.cl_type() << endl;

  Lines ln;
  cout << "ln: " << ln.cl_type() << endl;

  cout << "calling: call(sh), call(cir), call(ln):"<< endl;
  call(sh);
  call(cir);
  call(ln);

  cout << endl << "Experiment with vec. vec[i].cl_type():" << endl;
  /* Experiment 1:
  vector <Shape> vec(5);
  vec[0] = sh;
  vec[1] = cir;
  vec[2] = ln;
  */
  /* Experiment 2:
  vector <Shape> vec;

  vec.push_back(sh);
  vec.push_back(cir);
  vec.push_back(ln);
  */

  /*
  // Experiment 3: To see how the vector grows (2^n)
  vector <Shape> vec;
  vec.push_back(sh);
  cout << "have completed one push_back of sh" << endl;
  vec.push_back(sh);
  cout << "have completed two push_backs of sh" << endl;
  vec.push_back(sh);
  cout << "have completed three push_backs of sh" << endl;
  vec.push_back(sh);
  cout << "have completed four push_backs of sh" << endl;
  vec.push_back(sh);
  cout << "have completed five push_backs of sh" << endl;
  vec.push_back(sh);
  cout << "have completed six push_backs of sh" << endl;
  vec.push_back(sh);
  cout << "have completed seven push_backs of sh" << endl;
  vec.push_back(sh);
  cout << "have completed eight push_backs of sh" << endl;
  vec.push_back(sh);
  cout << "have completed nine push_backs of sh" << endl;
  */

  // Experiment 4: Vec_ref
  Vector_ref<Shape> vec;
  vec.push_back(sh);
  vec.push_back(cir);
  vec.push_back(ln);
  cout << "Pushing new line into vec (=Vector_ref)"<<endl;
  vec.push_back(new Lines);

  cout << "vec.push_backs are done" << endl;
  for (int i=0; i<vec.size(); i++) {
    cout << "i = " << i << ", " << vec[i].cl_type() << endl;
  }




/*
  cout << endl<< "experiment with the Shape * p_sh = &vec[1];" << endl;
  Shape * p_sh = &vec[1];
  cout << "p_sh->cl_type() returned " << p_sh->cl_type() << endl;
  */
  cout << endl<< "main is done" << endl;
}
