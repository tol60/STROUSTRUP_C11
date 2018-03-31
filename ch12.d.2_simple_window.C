//
/*

https://groups.google.com/forum/#!topic/ppp-public/BtlzdWGuQpQ
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE

The following steps were needed to compile under Linux:
5. Graph.h line 10: Uncomment #include "std_lib_facilities.h"


   //g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch12.d.2_simple_window.C \
           `fltk-config --ldflags --use-images` -o ch12.d.2_simple_window.exe 2>&1 | tee tmp.txt

Note:
fltk-config --ldflags --use-images
-L/usr/local/lib -lfltk_images -lpng -lz -lfltk_jpeg -lfltk -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11

g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch12.d.2_simple_window.C \
           -L/usr/local/lib -lfltk_images -lpng -lz -lfltk_jpeg -lfltk -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11 \
           -o ch12.d.2_simple_window.exe 2>&1 | tee tmp.txt
Worked as well!

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

  win.wait_for_button();  // display!

}


