//
/* 2. Draw a box with rounded corners. Define a class Box, consisting of four lines and four arcs.
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
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch13.e.2_round_box.C \
           `fltk-config --ldflags --use-images` -o ch13.e.2_round_box.exe 2>&1 | tee tmp.txt

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

  Simple_window win {pt, 600, 400,"ch13.e.2_round_box"};  // make a simple window, {top_left, width, hight, title}

  Point A{100,100};
  int r=5;

  Rectangle sq{A,2*r*5,2*r*5};
  sq.set_fill_color(Color::blue);
  win.attach(sq);
  Arc ar{Point{A.x+r*5,A.y+r*5},r*5,r*5,180,90};
  //Arc ar{Point{A.x+r*5,A.y+r*5},r*5,r*5,90,180};
  ar.set_fill_color(Color::blue);
  win.attach(ar);


  int half = 5*r;
  Point B{100,200};
  Point C{100+half,200};
  Rectangle rec{C,half,2*half};
  rec.set_color(Color::invisible);
  rec.set_fill_color(Color::blue);
  win.attach(rec);

  Arc br{Point{B.x+r*5,B.y+r*5},r*5,r*5,180,90};
  //Arc ar{Point{A.x+r*5,A.y+r*5},r*5,r*5,90,180};
  br.set_color(Color::red);
  br.set_fill_color(Color::blue);
  win.attach(br);

  Line ln1{Point{B.x+r*5-1,B.y+1},Point{B.x+r*5-1,B.y+r*5}};
  ln1.set_color(Color::blue);
  // win.attach(ln1); // this one will cover one of the white lines (top left corner, vertical)

  Point D{100+half,300};
  r = 5 * r;
  Vector_ref<Arc> arcs; // to store corner arcs
/*
  arcs.push_back(new Arc{D,r,r,180,90}); // left top corner
  arcs.push_back(new Arc{D,r,r,90,0}); // right top corner
  arcs.push_back(new Arc{D,r,r,180,270}); // left bottom corner
*/

//  arcs.push_back(new Arc{D,r,r,180,175}); // left top corner
//  arcs.push_back(new Arc{D,r,r,90,0}); // right top corner
  arcs.push_back(new Arc{D,r,r,180,270}); // left bottom corner


  for (int i=0; i<arcs.size(); ++i) {
    arcs[i].set_color(Color::red);
    arcs[i].set_fill_color(Color::blue);
    win.attach(arcs[i]);
  }

  /*
  Ellipse el{Point{A.x+r*5,A.y+r*5},r*5,r*5};
  el.set_fill_color(Color::yellow);
  win.attach(el);
*/
  RoundedBox rb{Point{200,200}, 200,100, 20};
  rb.set_fill_color(Color::yellow);
  //rb.set_fill_color(Color::blue);


  rb.set_color(Color::red);
  //rb.set_color(Color::Transparency::invisible); // this effectively will destroy the underlying color
  //rb.set_color(Color::Transparency::visible); // this will effectively destroy the underlying color
  win.attach(rb);






  Text t{Point{50,390},"RoundedBox use example"};
  t.set_color(Color::blue);
  win.attach(t);

  win.wait_for_button();  // display!


}


