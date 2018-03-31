//
/*  9. Tile part of a window with Regular_hexagons (use at least eight hexagons).
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
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch13.e.9_hexagon_tile.C \
           `fltk-config --ldflags --use-images` -o ch13.e.9_hexagon_tile.exe 2>&1 | tee tmp.txt

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
  //constexpr Point pt{300,200};

  Simple_window win {pt, 600, 400,"ch13.e.9_hexagon_tile"};  // make a simple window, {top_left, width, hight, title}
  //int radius = 70; // radius to feed to Regualr_hexagon constructor
  constexpr int radius = 40;



  Vector_ref<Regular_hexagon> vr;  // vector reference
  constexpr int NUM_SIDES = 6;
  constexpr double RAD_FAC = atan(1) / 45.0; // factor to multiply degrees to get radians
  constexpr double hight = radius*sqrt(3)/2.0; // the shortest distance from the center to the side of hexagon


  // We'll do columns. between similar columns the space is 3 * radius.
  // There is another column in between 1.5 * radius in x direction and 1 *hight in the y direction
  constexpr int n_ydir = 8;
  constexpr int n_xdir = 10;


  for (int j=0; j<n_xdir; j++) {
    int x = pt.x + 1.5 * radius * j; // the difference between the columns (x direction) is always the same
    int y = pt.y; // the y coordinate have to be adjusted every other column
    // column in between 1.5 * radius in x direction and 1 *hight in the y direction
    y += (j % 2) ? hight : 0;   // every other column will have to be shifted
    Color clr = (j%2) ? Color::green : Color:: blue; // we will change color by the column
    for (int i = 0; i < n_ydir; i++) {
      y += 2 * hight;
      vr.push_back(new Regular_hexagon(Point { x, y }, radius));
      vr[vr.size() - 1].set_fill_color(clr);
      win.attach(vr[vr.size() - 1]);
    }

  }


  /* Sample. If do it around the center
  Regular_hexagon reg_hexagon(pt,radius);
  //Regular_hexagon reg_hexagon(pt,radius,15); // this will rotate the hexagot by 15 degress (when constructed)
  reg_hexagon.set_fill_color(Color::blue);
  reg_hexagon.set_color(Color::red);
  win.attach(reg_hexagon);

  Circle crcl (pt,radius);
  win.attach(crcl);
  // we will go around the center tile (hexagon)
  for (int i=0; i<NUM_SIDES; i++){
    double angle = 30.0 + 360.0/NUM_SIDES *i;
    // the distance between the centers of the two hexagons will be 2*radius*cos(30 degrees)
    int dx = 2*hight * cos(RAD_FAC*angle);
    int dy = 2*hight * sin(RAD_FAC*angle);
    vr.push_back(new Regular_hexagon(Point{pt.x + dx,pt.y + dy},radius) );
    vr[vr.size()-1].set_fill_color(Color::green);
    win.attach(vr[vr.size()-1]);
  }
  for (int i=0; i<NUM_SIDES; i++){
    double angle = 0.0 + 360.0/NUM_SIDES *i;
    // the distance between the centers of the two hexagons will be 2*radius*cos(30 degrees)
    int dx = (3*radius) * cos(RAD_FAC*angle);
    int dy = (3*radius) * sin(RAD_FAC*angle);
    vr.push_back(new Regular_hexagon(Point{pt.x + dx,pt.y + dy},radius) );
    vr[vr.size()-1].set_fill_color(Color::yellow);
    win.attach(vr[vr.size()-1]);
  }
  */


  /*
  constexpr int GREED_SIZE = 4;
  for (int i=0; i<GREED_SIZE;i++)
    for (int j=0; j<GREED_SIZE;j++){
      vr.push_back(new Rectangular_hexagon(Point{x,y},radius));
    }
*/

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


