//
/* EX5. Draw a red 1/4 inch frame around a rectangle that is three-quarters the height of your screen and two-thirds the width.
 * Ex4. Draw a 3-by-3 tic-tac-toe board of alternating white and red squares.
 * Ex3. Draw your initials 150 pixels high. Use a thick line. Draw each initial in a different color.
 * Ex2. Draw a 100-by-30 Rectangle and place the text "Howdy!" inside it.
 * Ex1. Draw a rectangle as a Rectangle and as a Polygon. Make the lines of the Polygon red and the lines of the Rectangle Blue.

https://groups.google.com/forum/#!topic/ppp-public/BtlzdWGuQpQ
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE

The following steps were needed to compile under Linux:
5. Graph.h line 10: Uncomment #include "std_lib_facilities.h"


   //g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch12.e.5_red_frame.C \
           `fltk-config --ldflags --use-images` -o ch12.e.5_red_frame.exe 2>&1 | tee tmp.txt

Note:
fltk-config --ldflags --use-images
-L/usr/local/lib -lfltk_images -lpng -lz -lfltk_jpeg -lfltk -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11

Note:
Can not create vector<Rectangle>
See
https://groups.google.com/forum/#!msg/ppp-public/GsCfxCnSLig/I3va8938lAgJ;context-place=searchin/ppp-public/vector%3CRectangle%3E%7Csort:relevance
The GUI
library classes are incompatible with the STL; specifically std::vector.

The problem is that you can't make a vector <Rectangle> because Rectangle is
derived from Shape and Shape hides the copy constructor as well as the
assignment operator,

    class Shape
    {
        //...
    private:
        Shape(const Shape&);               // prevent copying
        Shape& operator=(const Shape&);
    };

Both of these are requirements for a vector.
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

  Point  tl {0,0};    // to become top left corner of window

  cout << "Screen size:" << x_max() <<"*" <<y_max() << endl;
  Simple_window win{tl, x_max(), y_max(), "Full Screen Window"};   // make a simple window, {top_left, width, hight, title}
  Rectangle r{Point{x_max()/6.0, y_max()/8.0}, x_max()*2/3.0, y_max()*3/4.0}; // 2/3 width, 3/4 hight,
  r.set_color(Color::red); // set the color
  r.set_style(Line_style(Line_style::solid,20));
  win.attach(r);

  win.wait_for_button();  // display!

}


