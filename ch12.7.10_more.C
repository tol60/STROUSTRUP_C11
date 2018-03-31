//
/*

https://groups.google.com/forum/#!topic/ppp-public/BtlzdWGuQpQ
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE

The following steps were needed to compile under Linux:
5. Graph.h line 10: Uncomment #include "std_lib_facilities.h"


   //g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch12.7.10_more.C \
           `fltk-config --ldflags --use-images` -o ch12.7.10_more.exe 2>&1 | tee tmp.txt

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

  Point  tl {100,100};    // to become top left corner 0f window

  Simple_window win {tl, 600, 400,"My Window"};  // make a simple window, {top_left, width, hight, title}

  Axis xa {Axis::x, Point{20,300}, 280, 10, "x axis"}; // make an axis
  // An Axis is kind of a Shape
  // Axis::x means horizontal
  // starting at (20,300)
  // 280 pixels long
  // 10 "notches"
  // label the axis "x axis"
  win.attach(xa); // attach xa to the window, win
  win.set_label("Canvas #2"); // relable the window

  Axis ya {Axis::y, Point{20,300}, 280, 10, "y axis"};
  ya.set_color(Color::cyan);  // choose a color for the axis
  ya.label.set_color(Color::dark_red);  // choose the color for the label
  win.attach(ya);
  win.set_label("Canvas #3");

  Function sine{sin,0,100, Point{20,150},1000,50,50}; // sine curve
    // plot sin() in the range [0,100) with (0,0) at (20,150)
    // using 1000 points; scale x values *50, scale y values *50

  win.attach(sine);

  win.set_label("Canvas #4");
  sine.set_color(Color::blue);  // change the color of the sine graph

  Polygon poly; // a polygon; a Polygon is a kind of Shape
  poly.add(Point{300,200}); // three points to make a triangle
  poly.add(Point{350,100});
  poly.add(Point{400,200});

  poly.set_color(Color::red);
  poly.set_style(Line_style::dash);
  win.attach(poly);
  win.set_label("12.7.5 Polygons");


  Rectangle r{Point{200,200},100,50}; // top left corner, width, height
  win.attach(r);
  win.set_label("12.7.6 Rectangles");

  Closed_polyline poly_rect;
  poly_rect.add(Point{100,50});
  poly_rect.add(Point{200,50});
  poly_rect.add(Point{200,100});
  poly_rect.add(Point{100,100});
  win.attach(poly_rect);

  win.set_label("12.7.6.1 Rectangles");
  poly_rect.add(Point{50,75});
  win.set_label("12.7.6.2 Rectangles");

  r.set_fill_color(Color::yellow); // color the inside of the rectangle
  poly.set_style(Line_style(Line_style::dash,4));
  poly_rect.set_style(Line_style(Line_style::dash,2));
  poly_rect.set_fill_color(Color::green);
  win.set_label("12.7.7_fill");

  //Text t{Point{150,150},"Hello, graphical world!"};
  Text t{Point{150,150},"Hi, Branden is here!"};
  win.attach(t);
  win.set_label("12.7.8 Text");

  t.set_font(Graph_lib::Font::times_bold);
  t.set_font_size(20);
  win.set_label("12.7.8 Text Bold");

  //Image ii {Point{100,150},"image.jpg"};  // 400*212-pixel jpg
  Image ii {Point{100,150},"/home/tony/Pictures/test.JPG"};
  win.attach(ii);
  win.set_label("12.7.9 Images");

  Circle c{Point{100,200},50};
  Ellipse e{Point{100,200},75,25};
  e.set_color(Color::dark_red);
  Mark m {Point{100,200},'x'};

  ostringstream oss;
  oss <<"screen size: "<<x_max() <<"*" <<y_max()
      << "; window size: " << win.x_max() << "*" << win.y_max();
  Text sizes{Point{100,20},oss.str()};
  ii.set_mask(Point{40,40},200,250);  // display center part of image

  win.attach(c);
  win.attach(m);
  win.attach(e);

  win.attach(sizes);
  win.set_label("12.7.10 More");

  win.wait_for_button();  // display!

}


