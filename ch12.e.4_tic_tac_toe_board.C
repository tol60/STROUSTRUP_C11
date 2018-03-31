//
/* Ex4. Draw a 3-by-3 tic-tac-toe board of alternating white and red squares.
 * Ex3. Draw your initials 150 pixels high. Use a thick line. Draw each initial in a different color.
 * Ex2. Draw a 100-by-30 Rectangle and place the text "Howdy!" inside it.
 * Ex1. Draw a rectangle as a Rectangle and as a Polygon. Make the lines of the Polygon red and the lines of the Rectangle Blue.

https://groups.google.com/forum/#!topic/ppp-public/BtlzdWGuQpQ
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE

The following steps were needed to compile under Linux:
5. Graph.h line 10: Uncomment #include "std_lib_facilities.h"


   //g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch12.e.4_tic_tac_toe_board.C \
           `fltk-config --ldflags --use-images` -o ch12.e.4_tic_tac_toe_board.exe 2>&1 | tee tmp.txt

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
  vector<Point> points;
  points.push_back(tl);

  const int MAX_ROW = 3;
  const int MAX_COL = 3;




  Rectangle rec{Point{50,50},50,50};


  Simple_window win {tl, 600, 400,"My Window"};  // make a simple window, {top_left, width, hight, title}

  // First initial
  int size = 50;
  int st_x=50; // starting x-coordinate of the field
  int st_y=50; // starting y-coordinate of the field

/*
  Rectangle squares[MAX_ROW * MAX_COL] =
  {
      Rectangle{Point(st_x, st_y), size, size}
      , Rectangle{Point(st_x, st_y), size, size}
      , Rectangle{Point(st_x, st_y), size, size}
      , Rectangle{Point(st_x, st_y), size, size}
      , Rectangle{Point(st_x, st_y), size, size}
      , Rectangle{Point(st_x, st_y), size, size}
      , Rectangle{Point(st_x, st_y), size, size}
      , Rectangle{Point(st_x, st_y), size, size}
      , Rectangle{Point(st_x, st_y), size, size}
  };
*/
/*
  Vector_ref vr;
  vr.push_back(new Rectangle{tl,50,50});
  */
/*
  for (int i=0, x=0; i<MAX_ROW; i++, x+=size){
    for (int j=0,y=0; j<MAX_COL; j++,y+=size) {
      squares[i*MAX_ROW+j].move(x,y);
    }
  }
  */
  /*
  for (auto & fd:Fields){
    win.attach(fd);
  }
*/

  // Brute force
  int x = st_x;
  int y = st_y;
  bool light = true;
  Rectangle R11{Point(x, y), size, size};
  R11.set_fill_color( (light) ? Color::white : Color::red);
  win.attach(R11);

  x+=size;
  light = ! light;
  Rectangle R21{Point(x, y), size, size};
  R21.set_fill_color( (light) ? Color::white : Color::red);
  win.attach(R21);

  x+=size;
  light = ! light;
  Rectangle R31{Point(x, y), size, size};
  R31.set_fill_color( (light) ? Color::white : Color::red);
  win.attach(R31);

  // Start next row
  x = st_x;
  y+=size;
  light = ! light;
  Rectangle R12{Point(x, y), size, size};
  R12.set_fill_color( (light) ? Color::white : Color::red);
  win.attach(R12);

  x+=size;
  light = ! light;
  Rectangle R22{Point(x, y), size, size};
  R22.set_fill_color( (light) ? Color::white : Color::red);
  win.attach(R22);

  x+=size;
  light = ! light;
  Rectangle R32{Point(x, y), size, size};
  R32.set_fill_color( (light) ? Color::white : Color::red);
  win.attach(R32);

  // Start next row
  x = st_x;
  y+=size;
  light = ! light;
  Rectangle R13{Point(x, y), size, size};
  R13.set_fill_color( (light) ? Color::white : Color::red);
  win.attach(R13);

  x+=size;
  light = ! light;
  Rectangle R23{Point(x, y), size, size};
  R23.set_fill_color( (light) ? Color::white : Color::red);
  win.attach(R23);

  x+=size;
  light = ! light;
  Rectangle R33{Point(x, y), size, size};
  R33.set_fill_color( (light) ? Color::white : Color::red);
  win.attach(R33);


  win.wait_for_button();  // display!

}


