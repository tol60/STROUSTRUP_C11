//
/* 3 Define a class Arrow, which draws a line with an arrowhead (Four days)
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
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch13.e.3_arrow.C \
           `fltk-config --ldflags --use-images` -o ch13.e.3_arrow.exe 2>&1 | tee tmp.txt

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

  Simple_window win {pt, 600, 400,"ch13.e.3_arrow"};  // make a simple window, {top_left, width, hight, title}

  Point A{100,100};
  Point B{200, 200};
  Point C{100,200};
  Point D{200,100};

  Arrow arr{A,B};  // this is our first Arrow
  win.attach(arr);

  Point dispOne{0,40};
  A += dispOne;
  B += dispOne;
  C += dispOne;
  D += dispOne;

  Arrow arrOne{A,B,10,4};
  arrOne.set_color(Color::red);
  arrOne.set_style(Line_style::dash);
  win.attach(arrOne);

  /*
  Closed_polyline poly_rect;
  poly_rect.add(Point{100,50});
  poly_rect.add(Point{200,50});
  poly_rect.add(Point{200,100});
  poly_rect.add(Point{100,100});
  poly_rect.set_fill_color(Color::green);
  poly_rect.add(Point{50,75});
  win.attach(poly_rect);
*/

  Arrow arrTwo{A,C,20,8};
  arrTwo.set_color(Color::yellow);
  arrTwo.set_style(Line_style::dash);
  arrTwo.set_fill_color(Color::blue);
  win.attach(arrTwo);

  Arrow arrThree{D,B,10,4};
  arrThree.set_color(Color::green);
  win.attach(arrThree);

  Text t{Point{50,390},"ch13.e.3_arrow use example"};
  t.set_color(Color::blue);
  win.attach(t);

  win.wait_for_button();  // display!


}


