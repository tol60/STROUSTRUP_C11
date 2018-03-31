//
/*

https://groups.google.com/forum/#!topic/ppp-public/BtlzdWGuQpQ
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE

The following steps were needed to compile under Linux:
5. Graph.h line 10: Uncomment #include "std_lib_facilities.h"

http://en.cppreference.com/w/cpp/utility/initializer_list


   //g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE
g++ -g -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch13.3_Lines.C \
           `fltk-config --ldflags --use-images` -o ch13.3_Lines.exe 2>&1 | tee tmp.txt

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

  //constexpr Point pt{100,100};    // to become top left corner of window

  Point pt = {420,430};

  Simple_window win {pt, 600, 400,"Lines"};  // make a simple window, {top_left, width, hight, title}

  // Need to revisit Lines(initializer_list<Point> lst). Did not work
  Lines x = {
      {100,100}, {150,200},{250,250},{300,200}
  };

  /*
  Lines x;
  x.add(Point{100,100},Point{200,100}); // first line: horizontal
  x.add(Point{150,50},Point{150,150});  // second line: vertical
*/
  x.set_color(Color::red); // set color (chould affect both lines

  win.attach(x);

  win.wait_for_button();  // display!

}


