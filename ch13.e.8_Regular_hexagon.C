//
/*  8. Define a class Regular_hexagon (a regular hexagon is a six-sided polygon with all sides of equal length).
 *     Use the center and the distance from the center to a corner point as constructor arguments.
 *     Problem:
 *        Still have to figure out how to tackle fill color for complex classes (the one that contain other classes)
 *  7. Make an RGB color chart (http://www.rapidtables.com/web/color/RGB_Color.htm#color-chart)

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
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch13.e.8_Regular_hexagon.C \
           `fltk-config --ldflags --use-images` -o ch13.e.8_Regular_hexagon.exe 2>&1 | tee tmp.txt

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

  Simple_window win {pt, 600, 400,"ch13.e.8_Regular_hexagon"};  // make a simple window, {top_left, width, hight, title}
  int radius = 70; // radius to feed to Regualr_hexagon constructor

  Regular_hexagon reg_hexagon(pt,radius);
  //Regular_hexagon reg_hexagon(pt,radius,15); // this will rotate the hexagot by 15 degress (when constructed)
  reg_hexagon.set_fill_color(Color::blue);
  reg_hexagon.set_color(Color::red);
  win.attach(reg_hexagon);

  Circle crcl (pt,radius);
  win.attach(crcl);
/*
  Closed_polyline poly_rect;
  poly_rect.add(Point{100,50});
  poly_rect.add(Point{200,50});
  poly_rect.add(Point{200,100});
  poly_rect.add(Point{100,100});

  poly_rect.add(Point{50,75});

  poly_rect.set_style(Line_style(Line_style::dash,2));
  poly_rect.set_fill_color(Color::green);
  //poly_rect.set_color(Color::Transparency::invisible); // This should make the outline of the shape invisible (=black)
  //poly_rect.set_fill_color(Color::Transparency::invisible); // This should make the fill color (= green) become invisible


  win.attach(poly_rect);


  RoundedBox rb{Point{200,200}, 200,100, 20};
  rb.set_fill_color(Color::yellow);
  rb.set_color(Color::red);

  //rb.set_color(Color::Transparency::invisible); // this effectively will destroy the underlying color
  //rb.set_color(Color::Transparency::visible); // this sets the visibility back on, but it set's the color to default (=black)
  win.attach(rb);
*/

  win.wait_for_button();  // display!


}


