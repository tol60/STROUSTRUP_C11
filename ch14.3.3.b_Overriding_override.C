
/* ch14.3.3.b_Overriding_override
 * here we declare that the function is menat to override using the word override:
 * To illustrate run-time polymorphism = dynaic dispatch = run-time dispatch
   g++ -w -Wall -std=c++11 ch14.3.3.b_Overriding_override.C -o ch14.3.3.b_Overriding_override.exe

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

struct B {
  virtual void f() const  {cout <<" B::f ";}
  void g() const          {cout << "B::g ";} // non virtual
};

struct D:B{
  void f() const override {cout << "D::f ";} // overrides B::f
  //void g() const override {cout << "D::g ";} // error: no virtual B::g to override (as B::g is not virtual)
  //void g() override {cout << "D::g ";} // error: no virtual B::g to override
  void g() const {cout << "D::g ";}
};

struct DD:D {
  void f()    {cout << "DD::f ";} // does not override D::f (no const), but compiles
  //void f() override {cout << "DD::f ";} // error: does not ovrride D::f (no const)
  void g() const {cout << "DD::g ";}
};

void call (const B&b)
//a D was derived from B, so call() can accept D
// a DD is derived from D and a D is derived from B, so call() can accept a DD
{
  b.f();
  b.g();  // this is never overwritten, so this will always pring "B::g"
}

int main ()
{
  using namespace std;  // our graphics facilities are in Graph_lib namespace

  B b;
  D d;
  DD dd;
  cout << "Overriding Experiment call(b), call(d) and call(dd) produce: \n";
  call (b);
  call (d);
  call (dd);
  cout << endl;

  cout << "Now call the function directly T.b(), T.g(), where T = {b, d, dd}: \n";
  b.f();
  b.g();

  d.f();
  d.g();

  dd.f();
  dd.g();
  cout << endl;
}


