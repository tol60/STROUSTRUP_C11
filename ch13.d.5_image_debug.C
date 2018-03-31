//
/* Drill for chapter 13
 * 1. make an 800 by 1000 Simple_window
 * 2. Put an 8-by-8 grid on the leftmost 800-by-800 part of that window (so that each square is 100 by 100
 * 3. Make the eight squares on the diagonal starting from the top left corner red (use Rectangle)
 * 4. Find a 200-by-200-pixel imgage (JPEG or GIF) and place three copies of it on the grid (each image covering four squares).
 *    If you can't find an image that is exactly 200 by 200, use set_mask() to pick a 200-by-200 section of a larger image. Don't obscure the red squares.
 * 5. Add a 100-by-100 image. Have it move around from square to square when you clock the "Next" button.
 *    Just put wait_for_button() in a loop with some code that picks a new square for your image.
 *

https://groups.google.com/forum/#!topic/ppp-public/BtlzdWGuQpQ
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE

The following steps were needed to compile under Linux:
5. Graph.h line 10: Uncomment #include "std_lib_facilities.h"


   //g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch13.d.5_image_debug.C \
           `fltk-config --ldflags --use-images` -o ch13.d.5_image_debug.exe 2>&1 | tee tmp.txt

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

  Simple_window win {pt, 800, 1000,"ch13.d.5_image_debug"};  // make a simple window, {top_left, width, hight, title}

  const int x_size = 800; // could have used win.x_max();
  const int y_size = 800; // could have used win.y_max();
  const int x_grid = 100;
  const int y_grid = 100;

  Lines grid;
  for (int x=x_grid; x<=x_size; x+=x_grid)
    grid.add(Point{x,0},Point{x,y_size}); // vertical line
  for (int y=y_grid; y<=y_size; y+=y_grid)
    grid.add(Point{0,y},Point{x_size,y});  // horizontal line

  //grid.set_color(Color::red); // set color (chould affect both lines
  win.attach(grid);

  Vector_ref <Rectangle> recs;
  // draw 8 rectangles on the diagonal (color red)
  for (int i=0; i<8; ++i) {
    recs.push_back(new Rectangle{Point{i*x_grid,i*y_grid},x_grid+1,y_grid+1});
    recs[i].set_color(Color::red);
    recs[i].set_fill_color(Color::red);// fill with red
    win.attach(recs[i]);
  }

  // single image:

  Image ii {Point{200,0},"/home/tony/Pictures/minDasha.JPG"};
  win.attach(ii);
  ii.set_mask(Point{250,50},100,100);


  // multiple images
  Vector_ref <Image> imgs;
  //imgs.push_back(ii);
  //imgs.push_back(new Image{Point{200,0},"/home/tony/Pictures/test.JPG"});
  //win.attach(imgs[0]);


  int num_duplicates = 3;
  for (int i=0; i<num_duplicates; ++i ) {
    //Image ii {Point{2*x_size*(1+i),0},"/home/tony/Pictures/test.JPG"};
    //imgs.push_back(ii);
    imgs.push_back(new Image{Point{0,2*y_grid*(1+i)},"/home/tony/Pictures/test.JPG"});
    //imgs.push_back(new Image{Point{200,0},"/home/tony/Pictures/test.JPG"});
    imgs[i].set_mask(Point{0,0},200,200);
    win.attach(imgs[i]);
    //win.attach(ii);
  }


  win.wait_for_button();  // display!

  win.put_on_top(ii); // putting the image on top

  while(1){

    ii.move(x_grid,0); // trying to move in x direction
    // do the check that we are still in the visible area:
    Point p = ii.point(0);
    if (p.x>=x_size){
      ii.move(-x_size,y_grid); // go back to the beginning of the row, and then increment y

      // check if y reached the edge of the screen
      p = ii.point(0);
      if (p.y>=y_size) {
        ii.move(0, -y_size); // go back to the very first row
      }
    }

    win.label("New Lable");
    win.wait_for_button();  // display!
  }

}


