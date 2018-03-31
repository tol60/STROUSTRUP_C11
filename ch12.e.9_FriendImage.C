//
/* EX9. Display an image on the screen, e.g. a photo of a friend. Label the image both with a title on the window and with a caption in the window.
 * EX8. Draw the Olympic five rings.
 * EX7. Draw a two-dimentional house seen from teh front, the way a child would: with a door, two windows, and a roof with a chimney.
 * EX6. What happens when you draw a Shape that doesn't fit inside the window? What happens when you draw a Window that doesn't fit on your screen?
 * EX5. Draw a red 1/4 inch frame around a rectangle that is three-quarters the height of your screen and two-thirds the width.
 * Ex4. Draw a 3-by-3 tic-tac-toe board of alternating white and red squares.
 * Ex3. Draw your initials 150 pixels high. Use a thick line. Draw each initial in a different color.
 * Ex2. Draw a 100-by-30 Rectangle and place the text "Howdy!" inside it.
 * Ex1. Draw a rectangle as a Rectangle and as a Polygon. Make the lines of the Polygon red and the lines of the Rectangle Blue.

https://groups.google.com/forum/#!topic/ppp-public/BtlzdWGuQpQ
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE

The following steps were needed to compile under Linux:
5. Graph.h line 10: Uncomment #include "std_lib_facilities.h"


   //g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch12.e.9_FriendImage.C \
           `fltk-config --ldflags --use-images` -o ch12.e.9_FriendImage.exe 2>&1 | tee tmp.txt

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

  Point  tl {100,100};    // to become top left corner of window

  //cout << "Screen size:" << x_max() <<"*" <<y_max() << endl;
  //Simple_window win{tl, 600, 400, "ch12.e.9_FriendImage"};   // make a simple window, {top_left, width, hight, title}
  Simple_window win{tl, 600, 700, "ch12.e.9_FriendImage"};   // make a simple window, {top_left, width, hight, title}

  int pic_st_y = 140;
  int cap_st_y = pic_st_y-10;
  Image ii{Point{100,pic_st_y},"/home/tony/Pictures/test.JPG"};
  win.attach(ii);
  Text t{Point{100,cap_st_y}, "Stepa"};
  win.attach(t);
  win.set_label("Stepa");


  win.wait_for_button();  // display!

}


