//
/* 5. Define the functions from exercise 4 for a Circle and an Ellipse. Place the connections points on or outside the shape, but no outside the bounding rectangle.
 *    (15:50-18:44) - 3 hours
 * 4. Define functions n(), s(), e(), w(), center(), ne(), se(), sw() and nw(). Each takes a Rectangle argument and returns a Point.
 *    These functions define "connection points" on and in the rectangle. For example, nw(r) is the northwest (top left) corner of a Rectangle called r
 *    (12:30 - 14:00 (an hour and a half) )
 * 3. Define a class Arrow, which draws a line with an arrowhead (Four days)
 * 2. Draw a box with rounded corners. Define a class Box, consisting of four lines and four arcs.
 * 1. Define a class Arc, which draws a part of an ellipse. Hint:: fl_arc()

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
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch13.e.5_ellipse_connection_points.C \
           `fltk-config --ldflags --use-images` -o ch13.e.5_ellipse_connection_points.exe 2>&1 | tee tmp.txt

Note:
fltk-config --ldflags --use-images
-L/usr/local/lib -lfltk_images -lpng -lz -lfltk_jpeg -lfltk -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11

convert Stepa_mod.JPG -resize 10% test.JPG

14:10
*/

//#include "std_lib_facilities.h"

//#include <FL/Fl.H>
//#include <FL/Fl_Box.H>
//#include <FL/Fl_Window.H>

#include "Simple_window.h"  // get access to our window library
//#include "Window.h"
#include "Graph.h"          // get access to our graphics library facilities



int main ()
{
  using namespace Graph_lib;  // our graphics facilities are in Graph_lib namespace

  constexpr Point pt{100,100};    // to become top left corner of window

  Simple_window win {pt, 600, 400,"ch13.e.5_ellipse_connection_points"};  // make a simple window, {top_left, width, hight, title}

  Point A{100,100};
  Point B{400, 200};
  /*
  int a = 50;
  int b = 100;
  */
  int a = 200;
  int b = 50;

  Ellipse r{B, a, b};
  win.attach(r);

  Point NW{nw(r)};
  Point SW{sw(r)};
  Point NE{ne(r)};
  Point SE{se(r)};

  Point N{n(r)};
  Point S{s(r)};
  Point E{e(r)};
  Point W{w(r)};



  cout << "Input Circle:\n"
 //     << "Point A: " << A << endl
      << "Point B: " << B << endl
      << "a = " << a << endl
      << "b = " << b << endl
      << endl;
  cout << "NW: " << NW<<endl;
  cout << "SW: " << SW<<endl;
  cout << "SE: " << SE<<endl;
  cout << "NE: " << NE<<endl;
  cout << endl;

  cout << "N: " << N<<endl;
  cout << "S: " << S<<endl;
  cout << "E: " << E<<endl;
  cout << "W: " << W<<endl;
  cout << endl;

  Lines lns;
  lns.add(Point{B.x -a, B.y},Point{B.x+a,B.y});
  lns.add(Point{B.x, B.y-b},Point{B.x,B.y+b});
  win.attach(lns);

/*
  Point pArrBase{B};
  pArrBase += Point{a, b};
  Arrow arrSE {pArrBase,SE};
  */
  Arrow arrSE{B,SE};
  arrSE.set_color(Color::blue);
  win.attach(arrSE);


  Text t{Point{50,390},"ch13.e.5_ellipse_connection_points use example"};
  t.set_color(Color::blue);
  win.attach(t);

  win.wait_for_button();  // display!


}


