//
/*

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
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch13.8_Polygon.C \
           `fltk-config --ldflags --use-images` -o ch13.8_Polygon.exe 2>&1 | tee tmp.txt

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

int main ()
{
  using namespace Graph_lib;  // our graphics facilities are in Graph_lib namespace

  constexpr Point pt{100,100};    // to become top left corner of window

  Simple_window win {pt, 600, 400,"ch13.8_Polygon"};  // make a simple window, {top_left, width, hight, title}

/*
  Closed_polyline cpl={
      {100,100}, {150,200},{250,250},{300,200}
  };
  //cpl.add(Point{100,250});
  cpl.add({100,250});
  win.attach(cpl);
*/


  Polygon pgn={
      {100,100}, {150,200},{250,250},{300,200}
  };
  //pgn.add({100,250});  // this point should break it
  win.attach(pgn);


  /*
  // aandree 13 Nov 2016
  // we will need to explicitly declare the initializer_list constructor for Polygons.
  // It is ends up being derived from Shape, and therefore mimics the Shape::Shape(initializer_list<Point> lst),
  // but the add(p) function for Polygon was modified
  // to include an extra checker, which is not present in the Shape::add(Point p)
  Polygon pgn={
      {100,100}, {150,200},{250,250},{300,200}, {100,250}
  }; // the last point was supposed to break it.
  // But if we use the constructor from a different class, we are using Shape::add(Point p)
  // which does not have error checking
  win.attach(pgn);
*/

  win.wait_for_button();  // display!


}


