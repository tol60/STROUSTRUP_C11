//
/* Ex1. Draw a rectangle as a Rectangle and as a Polygon. Make the lines of the Polygon red and the lines of the Rectangle Blue.

https://groups.google.com/forum/#!topic/ppp-public/BtlzdWGuQpQ
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE

The following steps were needed to compile under Linux:
5. Graph.h line 10: Uncomment #include "std_lib_facilities.h"


   //g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch12.e.1_Rectangle_Polygon.C \
           `fltk-config --ldflags --use-images` -o ch12.e.1_Rectangle_Polygon.exe 2>&1 | tee tmp.txt

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

  Point  tl {100,100};    // to become top left corner of window

  Simple_window win {tl, 600, 400,"My Window"};  // make a simple window, {top_left, width, hight, title}

  Rectangle r{Point{50,50},100,50}; // rectangle
  win.attach(r);
  r.set_color(Color::red);

  Polygon poly;
  poly.add(Point{200,50}); // add points
  poly.add(Point{200,100});
  poly.add(Point{300,100});
  poly.add(Point{300,50});
  win.attach(poly);
  poly.set_color(Color::blue);

  win.wait_for_button();  // display!

}


