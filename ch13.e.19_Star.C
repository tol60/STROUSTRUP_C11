//
/*  19. Define a class Star. One parameter should be the number of points. Draw a few stars with differing number of points, differing line colors, and differing fill colors
 *  18. Define a class Poly that represents a polygon but checks that its points really do make a polygon in its constructor.
 *      Hint: you'll have to suply the points to the constructor
 *  15. "Tile" a window with small right triangles
 *  14. Define a right triangle class. Make an octagonal shape out of eight right triangles of different colors.
 *  13. Draw the color matrix from 13.10, but without lines around each color.

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
  Simple_window win {pt, 600, 400,"ch13.e.19_Star"};  // make a simple window, {top_left, width, hight, title}


  Point center{300,200};
  int num_pts = 5;
  int rad_one = 100;
  int rad_two = 50;
  int alpha = 90; // for rotation
  Star st {center, num_pts, rad_one, rad_two, alpha};
  st.set_color(Color::red);
  st.set_fill_color(Color::blue);
  win.attach(st);
  // st.draw_lines(); // we really should have all the draw_lines() marked as protected. But then our container classes whould not be able to draw the pieces.

  Vector_ref<Shape> vr;
  center = Point {100,100};
  num_pts = 20;
  vr.push_back(new Star{center,num_pts,rad_one,rad_two,});
  vr[vr.size()-1].set_color(Color::green);
  vr[vr.size()-1].set_fill_color(Color::dark_cyan);
  win.attach(vr[vr.size()-1]);



  win.wait_for_button();  // display!


}


