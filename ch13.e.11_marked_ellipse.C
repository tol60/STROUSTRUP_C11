//
/* 11. Draw a 300-by-200-pixel ellipse. Draw a 400-pixel-long x axis and a 300-pixel-long y axis through the center of the ellipse. Mark the foci.
 * Mark a point on the ellipse that is not on one of the axes. Draw the two lines from the foci to the point.
 * 10. Define a class Regular_polygon. Use the center, the number of sides (>2), and the distance from the center to a corner as constructor arguments.
 *  9. Tile part of a window with Regular_hexagons (use at least eight hexagons).
 *  8. Define a class Regular_hexagon (a regular hexagon is a six-sided polygon with all sides of equal length).
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
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch13.e.11_marked_ellipse.C \
           `fltk-config --ldflags --use-images` -o ch13.e.11_marked_ellipse.exe 2>&1 | tee tmp.txt

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

  constexpr Point pt{100,100}; // top left corner of the window
  Simple_window win {pt, 600, 400,"ch13.e.11_marked_ellipse"};  // make a simple window, {top_left, width, hight, title}
  constexpr Point center{300,200};    // center of the ellipse

  // Draw a 300-by-200-pixel ellipse.
  constexpr int x_size_Els = 300; // size on an ellipse in x-direction
  constexpr int y_size_Els = 200; // size of an ellipse in y-derection
  Ellipse els (center,x_size_Els/2, y_size_Els/2); // center plus half - axis
  win.attach(els);

  // Axis:
  constexpr int notchSize = 10;

  // Draw a 400-pixel-long x axis
  constexpr int x_axis_Length = 400;
  Point pXaxis_start {center.x - x_axis_Length/2, center.y}; // Start of the x-axis (to the left from the center)
  //Axis(Orientation d, Point xy, int length, int nummber_of_notches=0, string label = "");
  Axis xa{Axis::x,pXaxis_start,x_axis_Length, x_axis_Length/notchSize, "x-axis"};
  win.attach(xa);

  // Draw a 300-pixel-long y axis through the center of the ellipse.
  constexpr int  y_axis_Length = 300;
  Point pYaxis_start {center.x, center.y + y_axis_Length/2}; // Start of the y-axis (to the bottom  from the center) - goes up
  //Axis(Orientation d, Point xy, int length, int nummber_of_notches=0, string label = "");
  Axis ya{Axis::y,pYaxis_start,y_axis_Length, y_axis_Length/notchSize, "y-axis"};
  win.attach(ya);

  // Mark the foci.
  Mark mF1 {els.focus1(),'x'};
  win.attach(mF1);

  Mark mF2 {els.focus2(),'x'};
  win.attach(mF2);

  // Mark a point on the ellipse that is not on one of the axes.
  constexpr int alpha = -120;  // we pick up an angle
  // constexpr int alpha = 45;  // we pick up an angle
  constexpr double RAD_FAC = atan(1) / 45.0; // factor to multiply degrees to get radians
  Point selPoint {center.x + els.major()*cos(RAD_FAC*alpha), center.y - els.minor()*sin(RAD_FAC*alpha)}; // Note, x uses '+',  y uses '-'
  Mark mSel{selPoint,'x'};
  win.attach(mSel);


  // Draw the two lines from the foci to the point.
  Open_polyline opl = {els.focus1(),selPoint,els.focus2()};
  opl.set_color(Color::red);
  win.attach(opl);


  win.wait_for_button();  // display!


}


