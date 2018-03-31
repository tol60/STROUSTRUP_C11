//
/*   15. "Tile" a window with small right triangles
 *   14. Define a right triangle class. Make an octagonal shape out of eight right triangles of different colors.
 *   13. Draw the color matrix from 13.10, but without lines around each color.

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
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch13.e.15_tile_RightTriangle.C \
           `fltk-config --ldflags --use-images` -o ch13.e.15_tile_RightTriangle.exe 2>&1 | tee tmp.txt

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
  Simple_window win {pt, 600, 400,"ch13.e.15_tile_RightTriangle"};  // make a simple window, {top_left, width, hight, title}


  // "Tile" a window with small right triangles
  constexpr int sz = 100; // the representative size we will use in the construction
  Vector_ref<Right_triangle> rt; // right triagle
  constexpr int nx_tiles = 40; // how many tiles in x direction
  constexpr int ny_tiles = 30; // how many tiles in y direction

  Point ptAnch{0,0}; // we will start from this point (as an anchor)
  for (int i=0; i<nx_tiles; i++) {
    for (int j=0; j<ny_tiles; j++) {
      // internal loop: go down a columnt

      //  Two triangles per square:
      Point pt1 = ptAnch + Point{0, sz};
      Point pt2 = ptAnch + Point{sz, 0};
      Point pt3 = ptAnch + Point{sz,sz};
      rt.push_back(new Right_triangle{pt1,pt2,pt3}); // right angle dowan
      rt[rt.size()-1].set_fill_color(Color::blue); // paint the triangle
      win.attach(rt[rt.size()-1]);

      // replace one point, the other two points the same
      pt3 = ptAnch + Point{0, 0};
      rt.push_back(new Right_triangle{pt1,pt2,pt3}); // right angle down
      rt[rt.size()-1].set_fill_color(Color::yellow); // paint the triangle
      win.attach(rt[rt.size()-1]);

      ptAnch.y += sz; // prepare for the next iteration
    }
    // prepare for the next iteration
    ptAnch.x += sz;
    ptAnch.y = 0;
  }
  win.wait_for_button();  // display!


}


