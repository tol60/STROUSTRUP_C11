//
/* Ex3. Draw your initials 150 pixels high. Use a thick line. Draw each initial in a different color.
 * Ex2. Draw a 100-by-30 Rectangle and place the text "Howdy!" inside it.
 * Ex1. Draw a rectangle as a Rectangle and as a Polygon. Make the lines of the Polygon red and the lines of the Rectangle Blue.

https://groups.google.com/forum/#!topic/ppp-public/BtlzdWGuQpQ
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE

The following steps were needed to compile under Linux:
5. Graph.h line 10: Uncomment #include "std_lib_facilities.h"


   //g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch12.e.3_Initials.C \
           `fltk-config --ldflags --use-images` -o ch12.e.3_Initials.exe 2>&1 | tee tmp.txt

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

  Point  tl {100,100};    // to become top left corner of window

  Simple_window win {tl, 600, 400,"My Window"};  // make a simple window, {top_left, width, hight, title}

  // First initial
  int disp = 0;
  Line A1{Point{50+disp,200},Point{100+disp,50}}; // letterA part 1
  win.attach(A1);

  Line A2{Point{100+disp,50},Point{150+disp,200}}; // letterA part2
  win.attach(A2);

  Line A3{Point{125+disp,125},Point{75+disp,125}}; // letterA part 3
  win.attach(A3);

  A1.set_color(Color::dark_blue);
  A2.set_color(Color::dark_blue);
  A3.set_color(Color::dark_blue);

  // Second Initial is the same, just need to shift it
  disp = 150;
  Line B1{Point{50+disp,200},Point{100+disp,50}}; // letterA part 1
  win.attach(B1);

  Line B2{Point{100+disp,50},Point{150+disp,200}}; // letterA part2
  win.attach(B2);

  Line B3{Point{125+disp,125},Point{75+disp,125}}; // letterA part 3
  win.attach(B3);

  B1.set_color(Color::dark_yellow);
  B2.set_color(Color::dark_yellow);
  B3.set_color(Color::dark_yellow);


  win.wait_for_button();  // display!

}


