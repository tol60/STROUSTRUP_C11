//
/*

https://groups.google.com/forum/#!topic/ppp-public/BtlzdWGuQpQ
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE

The following steps were needed to compile under Linux:
5. Graph.h line 10: Uncomment #include "std_lib_facilities.h"


   //g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch13.3_grid.C \
           `fltk-config --ldflags --use-images` -o ch13.3_grid.exe 2>&1 | tee tmp.txt

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

  Simple_window win {pt, 600, 400,"ch13.3_grid"};  // make a simple window, {top_left, width, hight, title}

  const int x_size = win.x_max();
  const int y_size = win.y_max();
  const int x_grid = 80;
  const int y_grid = 40;

  Lines grid;
  for (int x=x_grid; x<x_size; x+=x_grid)
    grid.add(Point{x,0},Point{x,y_size}); // vertical line
  for (int y=y_grid; y<y_size; y+=y_grid)
    grid.add(Point{0,y},Point{x_size,y});  // horizontal line

  grid.set_color(Color::red); // set color (chould affect both lines

  win.attach(grid);

  win.wait_for_button();  // display!

}


