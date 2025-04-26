
/* ch15.d.1_Window
 * D3. Make both axes red
 * D2. Add an x axis and a y axis each of length 400, labeled "1==20pixels" and with a notch every 20 pixels. The axes should cross at (300,300).
 * D1. Make an empty 600-by-600 Window labeled "Functional graphs"

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

ch14.e.7:
Algorithms for filling up polygons:
https://www.tutorialspoint.com/computer_graphics/polygon_filling_algorithm.htm

compare solutions at:
https://github.com/thelastpolaris/Programming-Principles-and-Practice-Using-C-/tree/master/14

   //g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE
g++ -g -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch15.d.1_Window.C \
           `fltk-config --ldflags --use-images` -o ch15.d.1_Window.exe 2>&1 | tee tmp.txt

Note:
fltk-config --ldflags --use-images
-L/usr/local/lib -lfltk_images -lpng -lz -lfltk_jpeg -lfltk -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11

convert Stepa_mod.JPG -resize 10% test.JPG
*/

//#include "std_lib_facilities.h"

//#include "Simple_window.h"  // get access to our window library
#include "Window.h"
#include "Graph.h"          // get access to our graphics library facilities

int main ()
{
  using namespace Graph_lib;  // our graphics facilities are in Graph_lib namespace

  constexpr Point pt{100,100};    // to become top left corner of window
  //Simple_window win {pt, 600, 400,"ch15.d.1_Window"};  // make a simple window, {top_left, width, height, title}
  Graph_lib::Window win {pt, 600, 600, "ch15.d.1_Window"};  // make a simple window, {top_left, width, height, title}

  constexpr int ax_length = 400; // length of the axes
  constexpr int num_pix_per_notch = 20; // number of pixels per notch
  constexpr Point ctr{300,300}; // axes have to cross this point

  // Axis(Orientation d, Point xy, int length, int nummber_of_notches=0, string label = "");
  Axis x {Axis::x, Point{ctr.x - ax_length/2, ctr.y}, ax_length, ax_length/num_pix_per_notch, "1==20 pixels"}; // left-right
  x.set_color(Color::red);
  win.attach(x);

  Axis y {Axis::y, Point{ctr.x, ctr.y + ax_length/2}, ax_length, ax_length/num_pix_per_notch, "1==20 pixels"}; // bottom - up
  y.set_color(Color::red);
  win.attach(y);

  gui_main();



  // Simple_window use format:
  //Binary_tree btree{top, sz_diag, cell_size, levels}; // checker board
  //win.attach(btree);

  // win.wait_for_button(); // this applies to Simple_window only
}


