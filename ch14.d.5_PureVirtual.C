
/* ch14.d.5_PureVirtual
 * D5. Add a pure firtual function calle pvf() to B1 and try to repeat 1-4. Explain the result.
 * D4. Now define a functon called f() fod D1 and repeat 1-3. Explain the result.
 * D3. Define a reference to B1 (a B1&) and initialize that to the D1 object you just defined. Call vf() and f() for that reference
 * D2. Derive a class D1 from B1 and override vf(). Make a D1 object and call vf() and f() for it.
 * D1. Define a class B1 with a virtual fnction vf() and a non-virutal function f().
 *   Define both of these functions within class B1. Implement each fuction to output its name (e.g., B1::vf()). Make the functions public.
 *   Make a B1 object and call each function.
 *
   g++ -w -Wall -std=c++11 ch14.d.5_PureVirtual.C -o ch14.d.5_PureVirtual.exe

https://groups.google.com/forum/#!topic/ppp-public/BtlzdWGuQpQ
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE

The following steps were needed to compile under Linux:
5. Graph.h line 10: Uncomment #include "std_lib_facilities.h"

when you get to 12.6 Open_Polyline:
https://groups.google.com/forum/#!searchin/ppp-public/error$3A$20%E2%80%98Graph_lib$3A$3AOpen_polyline$3A$3AOpen_polyline(std$3A$3Ainitializer_list%3CGraph_lib$3A$3APoint%3E)%E2%80%99$20is$20protected%7Csort:relevance/ppp-public/ezLMuJkQrJk/dBX3Edh1BgAJ
http://en.cppreference.com/w/cpp/utility/initializer_list
Shape::Shape(initializer_list<Point> lst)
{  // add() the Points to this Shape
  for (Point p:lst)
    //points.push_back(p);
    add(p);
}
Polygon needs explicit declaration similar to the Shape::Shape(initializer_list<Point> lst), as the Polygon::add(Point p) performs extra cheker

   //g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch13.e.19_Star.C \
           `fltk-config --ldflags --use-images` -o ch13.e.19_Star.exe 2>&1 | tee tmp.txt

Note:
fltk-config --ldflags --use-images
-L/usr/local/lib -lfltk_images -lpng -lz -lfltk_jpeg -lfltk -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11

convert Stepa_mod.JPG -resize 10% test.JPG
*/

//#include "std_lib_facilities.h"

#include<iostream>  using namespace std;

using namespace std;

class B1 {               // abstract base class
public:
  virtual void pvf() = 0; // pure virtual
  virtual void vf() {cout << "B1::vf()\n";} // virtual function
  void f() {cout << "B1::f()\n";} // regular function
};

class D1: public B1 {
public:
  void pvf() override {cout << "D1::pvf()\n";}
  void vf() override { cout << "D1::vf()\n";}
  void f() { cout << "D1::f()\n";}
};

int main ()
{
  using namespace std;  // our graphics facilities are in Graph_lib namespace

  cout<< "\n As B1 is abstract, can not create an object\n";
  //B1 b1;
  //b1.vf();
  //b1.f();

  cout<< "\n  Calling d1.vf(), d1.f() and d1.pvf():\n";
  D1 d1;
  d1.vf();
  d1.f();
  d1.pvf();

  cout<< "\n  B1& bref = d1; Calling bref.vf(), bref.f() and bref.pvf():\n";
  B1& bref = d1; // reference (base class) to derived object
  bref.vf();
  bref.f();
  bref.pvf();
}


