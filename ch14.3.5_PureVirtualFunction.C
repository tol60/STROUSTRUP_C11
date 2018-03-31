
/* ch14.3.5_PureVirtualFunction
 * virtual void f()=0
   g++ -w -Wall -std=c++11 ch14.3.5_PureVirtualFunction.C -o ch14.3.5_PureVirtualFunction.exe

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

class B {               // abstract base class
public:
  virtual void f() = 0; // pure virtual function
  virtual void g() = 0; // pure virtual function
};

class D1 : public B {
public:
  void f() override { cout << "D1->f()\n";}
  void g() override { cout << "D1->g()\n";}
};

// Note that unless all pure virtual functions are overridden, the resulting class is still abstract:
class D2 : public B {
public:
  virtual void f() override { cout << "D2->f() override\n";}
  // no g(), so still an abstract class
};

class D3 : public D2 {
public:
  void g() override {cout << "D3->g() override\n";}
};

int main ()
{
  using namespace std;  // our graphics facilities are in Graph_lib namespace

  // B b; // error: B is abstract

  D1 d1;  // OK
  cout << "Calling functions on d1:\n";
  d1.f();
  d1.g();

  // D2 d2; // error: D2 is (still) abstract

  D3 d3; // OK
  cout << "Calling functions on d3:\n";
  d3.f();
  d3.g();
}


