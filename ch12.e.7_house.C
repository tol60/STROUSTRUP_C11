//
/* EX7. Draw a two-dimentional house seen from teh front, the way a child would: with a door, two windows, and a roof with a chimney.
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
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch12.e.7_house.C \
           `fltk-config --ldflags --use-images` -o ch12.e.7_house.exe 2>&1 | tee tmp.txt

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
  Simple_window win{tl, 600, 400, "ch12.e.7_house"};   // make a simple window, {top_left, width, hight, title}

  int st_x = 200;
  int st_y = 150;
  const int house_size = 200;
  const int roof_pitch = 100;
  const int chim_width = 20;
  Point A{st_x,st_y}; // reference point. Left base point of the roof
  Rectangle rH{A, house_size, house_size}; // main House structure
  win.attach(rH);

  // roof
  Point B{st_x + house_size/2, st_y - roof_pitch}; // roof top
  Point C{st_x + house_size, st_y}; // the other (right) base point of the roof
  // Finish drawing the roof:
  Line lRoofLeft{A,B};
  Line lRoofRight{B,C};

  win.attach(lRoofLeft);
  win.attach(lRoofRight);

  // windows and a door:
  int win_st_y = st_y + house_size / 3.0; // the level where windows and door will start
  int door_hight = (house_size *2) /3.0; // the door will go all the way to the bottom
  int win_width = 50; // the width for windows and a door
  int gap = (house_size - 3*win_width)/4; // assume equidistant gap
  if (gap<=0){
    error ("Dimensions do not match, the gap is non-positive!");
  }

  // Left window
  int x = st_x+gap; // start of the first window
  Rectangle rWinLeft{ Point{x,win_st_y}, win_width, win_width}; // Left window
  win.attach(rWinLeft);

  // Door
  x = st_x +2*gap +win_width; // start of the door
  Rectangle rDoor{ Point{x,win_st_y}, win_width, door_hight};
  win.attach(rDoor);

  // right window
  x = st_x + house_size - gap - win_width;
  Rectangle rWinRight{ Point{x,win_st_y}, win_width, win_width};
  win.attach(rWinRight);


  // Chimney
  Polygon pChim;
  int xChim_left = st_x + (house_size * 3)/4.0; // in the middle of the roof.
  int yChim_left = st_y - roof_pitch/2.0; // In the middle of the roof
  int xChim_right = xChim_left + chim_width;
  int yChim_right = yChim_left + (2*roof_pitch * chim_width) / house_size;

  pChim.add(Point{xChim_left,yChim_left});
  pChim.add(Point{xChim_left,st_y - roof_pitch}); // the Chimney will be as tall as the roof
  pChim.add(Point{xChim_right,st_y-roof_pitch}); // the Chimney will be as tall as the roof
  pChim.add(Point{xChim_right,yChim_right});
  win.attach(pChim);

  win.wait_for_button();  // display!

}


