
/* ch14.e.4_Immobile_Circle
 * E4. Define a class Immobile_Circle, which is just like Circle but can't be moved.
 * E1. Define two classes Smiley and Frowny, which are both derived from class Circle and have
 *    two eyes and a mouth. Next derive classes from Smiley and Frowny which add an appropriate hat to each.

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
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch14.e.4_Immobile_Circle.C \
           `fltk-config --ldflags --use-images` -o ch14.e.4_Immobile_Circle.exe 2>&1 | tee tmp.txt

Note:
fltk-config --ldflags --use-images
-L/usr/local/lib -lfltk_images -lpng -lz -lfltk_jpeg -lfltk -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11

convert Stepa_mod.JPG -resize 10% test.JPG
*/

//#include "std_lib_facilities.h"

#include "Simple_window.h"  // get access to our window library
//#include "Window.h"
#include "Graph.h"          // get access to our graphics library facilities

using namespace Graph_lib;
struct Immobile_Circle : Circle {
  using Circle::Circle; // use Circle's constructors
  void move(int dx, int dy) override {} // make this Shape immovable
};

int main ()
{
  using namespace Graph_lib;  // our graphics facilities are in Graph_lib namespace

  constexpr Point pt{100,100};    // to become top left corner of window
  Simple_window win {pt, 600, 400,"ch14.e.4_Immobile_Circle"};  // make a simple window, {top_left, width, hight, title}

  constexpr Point centA{300, 200};
  constexpr int radius = 100;
  Immobile_Circle ic{centA, radius};
  //Circle ic{centA, radius};

  ic.move(100,100);
  win.attach(ic);

  win.wait_for_button();
}


