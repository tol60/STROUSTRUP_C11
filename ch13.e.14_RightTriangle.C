//
/*   14. Define a right triangle class. Make an octagonal shape out of eight right triangles of different colors.
 *   13. Draw the color matrix from 13.10, but without lines around each color.

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
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch13.e.14_RightTriangle.C \
           `fltk-config --ldflags --use-images` -o ch13.e.14_RightTriangle.exe 2>&1 | tee tmp.txt

Note:
fltk-config --ldflags --use-images
-L/usr/local/lib -lfltk_images -lpng -lz -lfltk_jpeg -lfltk -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11

convert Stepa_mod.JPG -resize 10% test.JPG
*/

//#include "std_lib_facilities.h"

//#include <FL/Fl.H>
//#include <FL/Fl_Box.H>
//#include <FL/Fl_Window.H>

#include "Simple_window.h"  // get access to our window library
//#include "Window.h"
#include "Graph.h"          // get access to our graphics library facilities

/*
std::ostream& operator<< (std::ostream &os, Graph_lib::Point p)
{
  return os << '(' << p.x << '; ' << p.y << ')';   // output (x; y)
}
*/

int main ()
{
  using namespace Graph_lib;  // our graphics facilities are in Graph_lib namespace

  constexpr Point pt{100,100};    // to become top left corner of window
  Simple_window win {pt, 600, 400,"ch13.e.14_RightTriangle"};  // make a simple window, {top_left, width, hight, title}


  // Define a right triangle class.
  // Make an octagonal shape out of eight right triangles of different colors.
  // Three layers: 3+2+3 = 8 triangles total
  //   1. three triangles (top layer)
  //   2. two triangles to get rectangle (middle layer)
  //   3. three triangles (bottom layer)
  constexpr Point ptAnch{100,50}; // we will start from this point (as an anchor)
  constexpr int sz = 100; // the representative size we will use in the construction
  Vector_ref<Right_triangle> os; // os = octagonal shape

  //   1. three triangles (top layer)
  Point pt1 = ptAnch + Point{0, sz};
  Point pt2 = ptAnch + Point{sz, 0};
  Point pt3 = ptAnch + Point{2*sz,sz};
  os.push_back(new Right_triangle{pt1,pt2,pt3}); // right angle up
  win.attach(os[os.size()-1]);

  // replace one point, the other two points the same
  pt1 = ptAnch + Point{3*sz, 0};
  os.push_back(new Right_triangle{pt1,pt2,pt3}); // right angle down
  win.attach(os[os.size()-1]);

  // replace one point, the other two points the same
  pt2 = ptAnch + Point{4*sz, sz};
  os.push_back(new Right_triangle{pt1,pt2,pt3}); // right angle down
  win.attach(os[os.size()-1]);


  //   2. two triangles to get rectangle (middle layer
  // we will reuse one point from the last drawing (pt2)
  pt1 = ptAnch + Point{0, 2*sz};
  // pt2 - reuse // pt2 = ptAnch + Point{4*sz, sz};
  pt3 = ptAnch + Point{0, sz};  // this point was actually used to draw the very first triangle, but was overwritten

  os.push_back(new Right_triangle{pt1,pt2,pt3}); // right angle down
  win.attach(os[os.size()-1]);

  // we only need to move one point (pt3):
  pt3 = ptAnch + Point{4*sz, 2*sz};
  os.push_back(new Right_triangle{pt1,pt2,pt3}); // right angle down
  win.attach(os[os.size()-1]);


  //   3. three triangles (bottom layer)
  // we will re-use one porint from the last drawing (pt1)
  // pt1 -reuse //  pt1 = ptAnch + Point{0, 2*sz};
  pt2 = ptAnch + Point{sz, 3*sz};
  pt3 = ptAnch + Point{2*sz, 2*sz};
  os.push_back(new Right_triangle{pt1,pt2,pt3}); // right angle down
  win.attach(os[os.size()-1]);

  // replace one point, the other two points the same
  pt1 = ptAnch + Point{3*sz, 3*sz};
  os.push_back(new Right_triangle{pt1,pt2,pt3}); // right angle down
  win.attach(os[os.size()-1]);

  // replace one point, the other two points the same
  pt2 = ptAnch + Point{4*sz, 2*sz};
  os.push_back(new Right_triangle{pt1,pt2,pt3}); // right angle down
  win.attach(os[os.size()-1]);

  // Color triangles into different colors:
  vector<Color> colVec = {Color::blue, Color::cyan, Color::green, Color::red, Color::yellow, Color::white, Color::dark_cyan, Color::dark_green};
  for (int i=0; i<os.size(); i++)
    os[i].set_fill_color(colVec[i]);

/* Debug of the new features
  Right_triangle rtr{Point{100,100}, Point{200,200}, Point{300,100}};
  rtr.set_color(Color::red);
  rtr.set_fill_color(Color::yellow);
  win.attach (rtr);

  Point pA {200,200};
  Point pB {3,200};
  Point pC {10,300};
  std::cout << "pA = " << pA << endl;
  std::cout << "pB = " << pB << endl;
  std::cout << "pC = " << pC << endl;
  //Right_triangle trA{pA,pB,pC}; // this is not a right triangle, and would throw an exception at run time
  //win.attach(trA);

  Point pSum = pA+pB;
  cout << "pSum = pA + pB = " << pSum <<endl;

  Point pDiff = pA-pB;
  cout <<  "pDiff = pA - pB = " << pDiff <<endl;

  cout << "dot product = pB * pC = " << pB * pC << endl;

  pA = pA+pB;
  cout << "pA = pA+pB = " << pA << endl;
*/


  win.wait_for_button();  // display!


}


