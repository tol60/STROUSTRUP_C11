
/* ch16.3.1_CallbackFunction
 * Approximating e^x = 1 + x + x^2/2! + x^3/3! + x^4/4! + .. *
 * D3. Make both axes red
 * D2. Add an x axis and a y axis each of length 400, labeled "1==20pixels" and with a notch every 20 pixels. The axes should cross at (300,300).
 * D1. Make an empty 600-by-600 Window labeled "Functional graphs"

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

ch14.e.7:
Algorithms for filling up polygons:
https://www.tutorialspoint.com/computer_graphics/polygon_filling_algorithm.htm

compare solutions at:
https://github.com/thelastpolaris/Programming-Principles-and-Practice-Using-C-/tree/master/14

   //g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE
g++ -g -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch16.3.1_CallbackFunction.C \
           `fltk-config --ldflags --use-images` -o ch16.3.1_CallbackFunction.exe 2>&1 | tee tmp.txt

Note:
fltk-config --ldflags --use-images
-L/usr/local/lib -lfltk_images -lpng -lz -lfltk_jpeg -lfltk -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11

convert Stepa_mod.JPG -resize 10% test.JPG


Note:
On Unix might need to add the code to limit the maximum y values when we go outside the size of the screen. Otherwise we might wrap.
See ch16.3.1_CallbackFunction_debug_FLTK.C

   Fl_Graphics_Driver::line (this=0x6c6ac0 <fl_xlib_driver>, x=420, y=-7768, x1=460, y1=-32898) at fl_rect.cxx:336
   // this call draws a vertical line across the window.
   Question:
   Why?

   FLTK/fltk-1.3.3/src/fl_rect.cxx
 46 #ifdef USE_X11
 47
 48 #ifndef SHRT_MAX
 49 #define SHRT_MAX (32767)
 50 #endif

 53   We need to check some coordinates for areas for clipping before we
 54   use X functions, because X can't handle coordinates outside the 16-bit
 55   range. Since all windows use relative coordinates > 0, we do also
 56   check for negative values. X11 only, see also STR #2304.

 64   We define the usable X coordinate space as [ -LW : SHRT_MAX - LW ]
 65   where LW = current line width for drawing. This is done so that
*/

#include "std_lib_facilities.h"

#include "Simple_window.h"  // get access to our window library
//#include "Window.h"
#include "Graph.h"          // get access to our graphics library facilities

double one(double x) {return 1;}
double slope(double x){return x/2;}
double square (double x) {return x*x;}
double sloping_cos(double x) {return slope(x) + cos(x);}



int main ()
{
  using namespace Graph_lib;  // our graphics facilities are in Graph_lib namespace

  // constexpr Point pt{100,100};    // to become top left corner of window
  // constexpr Point pt{0,0};    // to become top left corner of window
  constexpr Point pt{80,80};    // to become top left corner of window

  constexpr int xmax = 600;
  constexpr int ymax = 600;

  constexpr int x_orig = xmax/2;  // position of (0,0) is center of window
  constexpr int y_orig = ymax/2;
  constexpr Point orig {x_orig, y_orig};

  constexpr int r_min = -10; // range [-10:10)
  constexpr int r_max = 10;

  constexpr int n_points = 400; // number of points used in range

  constexpr int x_scale = 20; // scaling factors
  constexpr int y_scale = 20;

  constexpr int ax_length = 400; // length of the axes
  constexpr int num_pix_per_notch = 20; // number of pixels per notch

  constexpr int label_raise = 10; // how far we need to lift the label from off the function to make it look pretty

  static const string window_title = "ch16.3.1_CallbackFunction"; // This is in the static area
  //Simple_window win {pt, xmax, ymax,"ch16.3.1_CallbackFunction"};  // make a simple window, {top_left, width, height, title} // This actually causes problem as FLTK only saves pointer to the string
  Simple_window win {pt, xmax, ymax,window_title};  // y coordinate keeps changing after wait_for_button() calls // make a simple window, {top_left, width, height, title}
  // Simple_window win {xmax, ymax,window_title}; // worked great! let's use default for the window location -- aandree 28 Jul 2018
  //Graph_lib::Window win {pt, xmax, ymax, "ch16.3.1_CallbackFunction"};  // make a simple window, {top_left, width, height, title}

  // Axis(Orientation d, Point xy, int length, int nummber_of_notches=0, string label = "");
  Axis ax_x {Axis::x, Point{orig.x - ax_length/2, orig.y}, ax_length, ax_length/num_pix_per_notch, "1==20 pixels"}; // left-right
  ax_x.set_color(Color::red);
  win.attach(ax_x);

  Axis ax_y {Axis::y, Point{orig.x, orig.y + ax_length/2}, ax_length, ax_length/num_pix_per_notch, "1==20 pixels"}; // bottom - up
  ax_y.set_color(Color::red);
  win.attach(ax_y);

  win.wait_for_button(); // this applies to Simple_window only

  Function real_exp{exp,r_min,r_max, orig,n_points, x_scale, y_scale}; // real exponent
  real_exp.set_color(Color::blue);
  win.attach(real_exp);
  win.set_label("real_exp");
  win.wait_for_button(); // this applies to Simple_window only
  win.wait_for_button(); // this applies to Simple_window only
  win.detach(real_exp);

  Function one_fun{one,r_min,r_max,orig,n_points, x_scale,y_scale}; //y=1 function
  win.attach(one_fun);
  win.set_label("One");
  win.wait_for_button(); // this applies to Simple_window only

/*
  //Function f1(one, r_min, r_max, orig, n_points); // default scaling
  Function f1{one, r_min, r_max, orig, n_points, x_scale, y_scale };
  win.attach(f1);

  Function f2{slope, r_min, r_max, orig, n_points, x_scale, y_scale };
  win.attach(f2);

  int x = ax_x.point(0).x; // get the coordinate of the left point of the axis
  int y = orig.y - slope(r_min)*y_scale - label_raise;
  Text ts2(Point{x,y}, "x/2");
  cout << "Point{x,y} = " << Point{x,y} << endl;
  win.attach(ts2);

  //  * B6. Add double square(double x) {return x*x;} to the window
  Function f3{square, r_min, r_max,orig, n_points, x_scale, y_scale};
  win.attach(f3);

  //  * B7. Add a cosine to the window (don't write a new function)
  Function f4{[](double x){return cos(x);}, r_min, r_max, orig, n_points, x_scale, y_scale };
  f4.set_color(Color::blue);
  win.attach(f4);

  Function f5{sloping_cos, r_min, r_max,orig, n_points, x_scale, y_scale};
  win.attach(f5);
  f5.set_color(Color::dark_cyan);
*/


  //win.wait_for_button(); // this applies to Simple_window only
  //gui_main(); // use this one with Regular Window

  /*for (int n=0; n<50; ++n) {
    //int n =10;
    ostringstream ss;
    ss << "exp approximation; n=="<<n ;
    win.set_label(ss.str());

    // get next approximation:
    Function e{[](double x){return expe(x,n);},  // unless n is constexpr, I am running into problem where the compiler does not understand the lambda
      r_min,r_max,orig,n_points,x_scale,y_scale};
    win.attach(e);
    win.wait_for_button();
    win.detach(e);
  }
*/
  // Simple_window use format:
  //Binary_tree btree{top, sz_diag, cell_size, levels}; // checker board
  //win.attach(btree);

  // win.wait_for_button(); // this applies to Simple_window only
}


