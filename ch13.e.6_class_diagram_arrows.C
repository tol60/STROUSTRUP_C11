//
/* 6. Write a program that draws a class diagram like the one of $12.6. It will simplify matters if you start by defining a Box class that is a rectangle with a text label.
 *    (9:50-
 * 5. Define the functions from exercise 4 for a Circle and an Ellipse. Place the connections points on or outside the shape, but no outside the bounding rectangle.
 *    (15:50-18:44) - 3 hours
 * 4. Define functions n(), s(), e(), w(), center(), ne(), se(), sw() and nw(). Each takes a Rectangle argument and returns a Point.
 *    These functions define "connection points" on and in the rectangle. For example, nw(r) is the northwest (top left) corner of a Rectangle called r
 *    (12:30 - 14:00 (an hour and a half) )
 * 3. Define a class Arrow, which draws a line with an arrowhead (Four days)
 * 2. Draw a box with rounded corners. Define a class Box, consisting of four lines and four arcs.
 * 1. Define a class Arc, which draws a part of an ellipse. Hint:: fl_arc()

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

   //g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch13.e.6_class_diagram_arrows.C \
           `fltk-config --ldflags --use-images` -o ch13.e.6_class_diagram_arrows.exe 2>&1 | tee tmp.txt

Note:
fltk-config --ldflags --use-images
-L/usr/local/lib -lfltk_images -lpng -lz -lfltk_jpeg -lfltk -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11

convert Stepa_mod.JPG -resize 10% test.JPG

14:10
*/

//#include "std_lib_facilities.h"

//#include <FL/Fl.H>
//#include <FL/Fl_Box.H>
//#include <FL/Fl_Window.H>

#include "Simple_window.h"  // get access to our window library
//#include "Window.h"
#include "Graph.h"          // get access to our graphics library facilities

// the function return the center of the column. column 1,2,3,...
int cent_col(int win_width, int num_columns, int column){
  int width = win_width/num_columns;
  return width * (column - 0.5);
}

int main ()
{
  using namespace Graph_lib;  // our graphics facilities are in Graph_lib namespace

  constexpr Point pt{100,100};    // to become top left corner of window

  double dn = 2.3;
  cout << "dn = " << dn <<", round(dn) = " << Graph_lib::round(dn) <<endl;
  cout << "-dn = " << -dn <<", round(-dn) = " << Graph_lib::round(-dn) <<endl;

  cout << endl;
  dn = 2.5;
  cout << "dn = " << dn <<", round(dn) = " << Graph_lib::round(dn) <<endl;
  cout << "-dn = " << -dn <<", round(-dn) = " << Graph_lib::round(-dn) <<endl;

  cout << endl;
  dn = 2.7;
  cout << "dn = " << dn <<", round(dn) = " << Graph_lib::round(dn) <<endl;
  cout << "-dn = " << -dn <<", round(-dn) = " << Graph_lib::round(-dn) <<endl;

  /* First Test. looked good
  Simple_window win {pt, 600, 400,"ch13.e.6_class_diagram_arrows"};  // make a simple window, {top_left, width, hight, title}

  Point A{100,100};
  Point B{400, 200};

  Arrow arrSE{A,B,30,10};
  arrSE.set_color(Color::blue);
  win.attach(arrSE);


  //Box Bl11{B, 100, 50};
  Box Bl11{B};
  Bl11.set_fill_color(Color::yellow);
  Bl11.add_text_line("ABCD");
  Bl11.add_text_line("// window interface:");
  Bl11.add_text_line("class Window {...};",Graph_lib::Font::times_bold);
  Bl11.add_text_line("...",Graph_lib::Font::times_bold);
  Bl11.add_text_line("// one more line");

  Bl11.add_caption("First Caption"); // this will be replaced by "Second Caption"
  Bl11.add_caption("Second Caption",Graph_lib::Font::times_bold);
  win.attach(Bl11);


  Text t{Point{50,390},"ch13.e.6_class_diagram_arrows use example"};
  t.set_color(Color::blue);
  win.attach(t);
  */

  const int win_width = 800;
  const int win_hight = 700;
  Simple_window win{pt, win_width, win_hight, "ch13.e.6_class_diagram_arrows"};   // make a simple window, {top_left, width, height, title}

  constexpr int num_columns = 4; // total number of columns
  int column = 1;
  constexpr int vert_st_disp = 50; // Initial vertical displacement/ step
  constexpr int vert_grid_step = 100;  // step between the boxes (vertical)

  // we will recalculate for each box
  int st_x = 150;  // center of the box
  int st_y = 100;  // top of the box

  Point bottom; // temporary point used in calculations

  // ###############################
  // First Column
  // ###############################
  column = 1;
  st_x = cent_col(win_width, num_columns, column); // location of the box
  st_y = 2* vert_st_disp;

  // ############ The first box (Box 11) #############
  Box Bl11{Point{st_x,st_y}};
  Bl11.set_fill_color(Color::yellow); // all boxes are yellow
  Bl11.add_caption("Point.h:",Graph_lib::Font::times_bold);  // caption (single line)
  Bl11.add_text_line("struct Point {...};",Graph_lib::Font::times_bold); // Text (will automatically resize the box
  win.attach(Bl11);

  bottom = Bl11.s(); // calculate the bottom of the previous box
  st_y = bottom.y + vert_grid_step;
    // ############ Box 12 #############
  Box Bl12{Point{st_x,st_y}};
  Bl12.set_fill_color(Color::yellow); // all boxes are yellow
  Bl12.add_caption("Graph.h:",Graph_lib::Font::times_bold);  // caption (single line)
  Bl12.add_text_line("// graphing interface:"); // Text (will automatically resize the box
  Bl12.add_text_line("struct Shape {...};",Graph_lib::Font::times_bold); // Text (will automatically resize the box
  Bl12.add_text_line("...",Graph_lib::Font::times_bold); // Text (will automatically resize the box
  win.attach(Bl12);

  bottom = Bl12.s(); // calculate the bottom of the previous box
  st_y = bottom.y + vert_grid_step;
    // ############ Box 13 #############
  Box Bl13{Point{st_x,st_y}};
  Bl13.set_fill_color(Color::yellow); // all boxes are yellow
  Bl13.add_caption("Graph.cpp:",Graph_lib::Font::times_bold);  // caption (single line)
  Bl13.add_text_line("Graph code",Graph_lib::Font::times_bold); // Text (will automatically resize the box
  win.attach(Bl13);

  // done column 1



  // ###############################
  // Second Column
  // ###############################
  column = 2;
  st_x = cent_col(win_width, num_columns, column); // location of the box
  st_y = 6 * vert_st_disp;

  // ############ The first box (Box 21) #############
  Box Bl21{Point{st_x,st_y}};
  Bl21.set_fill_color(Color::yellow); // all boxes are yellow
  Bl21.add_caption("window.cpp:",Graph_lib::Font::times_bold);  // caption (single line)
  Bl21.add_text_line("Window code",Graph_lib::Font::times_bold); // Text (will automatically resize the box
  win.attach(Bl21);

  bottom = Bl21.s(); // calculate the bottom of the previous box
  st_y = bottom.y + vert_grid_step;
  // ############ Box 22 #############
  Box Bl22{Point{st_x,st_y}};
  Bl22.set_fill_color(Color::yellow); // all boxes are yellow
  Bl22.add_caption("chapter12.cpp:",Graph_lib::Font::times_bold);  // caption (single line)
  Bl22.add_text_line("#include \"Graph.h\"",Graph_lib::Font::times_bold); // Text (will automatically resize the box
  Bl22.add_text_line("#include \"Simple_window.h\"",Graph_lib::Font::times_bold); // Text (will automatically resize the box
  Bl22.add_text_line("int main() {...}",Graph_lib::Font::times_bold); // Text (will automatically resize the box
  win.attach(Bl22);
  bottom = Bl22.s(); // calculate the bottom of the previous box
  st_y = bottom.y + vert_grid_step;


  // ###############################
  // Third Column
  // ###############################
  column = 3;
  st_x = cent_col(win_width, num_columns, column); // location of the box
  st_y = vert_st_disp;
  // ############ The first box (Box 31) #############
  Box Bl31{Point{st_x,st_y}};
  Bl31.set_fill_color(Color::yellow); // all boxes are yellow
  //Bl31.add_caption("",Graph_lib::Font::times_bold);  // caption (single line)
  Bl31.add_text_line("FLTK headers",Graph_lib::Font::times_bold); // Text (will automatically resize the box
  win.attach(Bl31);
  bottom = Bl31.s(); // calculate the bottom of the previous box
  st_y = bottom.y + vert_grid_step;

  // ############ Box 32 #############
  Box Bl32{Point{st_x,st_y}};
  Bl32.set_fill_color(Color::yellow); // all boxes are yellow
  Bl32.add_caption("Window.h:",Graph_lib::Font::times_bold);  // caption (single line)
  Bl32.add_text_line("// window interface:"); // Text (will automatically resize the box
  Bl32.add_text_line("class Window {...};",Graph_lib::Font::times_bold); // Text (will automatically resize the box
  Bl32.add_text_line("...",Graph_lib::Font::times_bold); // Text (will automatically resize the box
  win.attach(Bl32);
  bottom = Bl32.s(); // calculate the bottom of the previous box
  st_y = bottom.y + vert_grid_step;

  // ############ Box 33 #############
  Box Bl33{Point{st_x,st_y}};
  Bl33.set_fill_color(Color::yellow); // all boxes are yellow
  Bl33.add_caption("Simple_window.h:",Graph_lib::Font::times_bold);  // caption (single line)
  Bl33.add_text_line("// window interface:"); // Text (will automatically resize the box
  Bl33.add_text_line("class Window {...};",Graph_lib::Font::times_bold); // Text (will automatically resize the box
  Bl33.add_text_line("...",Graph_lib::Font::times_bold); // Text (will automatically resize the box
  win.attach(Bl33);
  bottom = Bl33.s(); // calculate the bottom of the previous box
  st_y = bottom.y + vert_grid_step;


  // ###############################
  // Fourth Column
  // ###############################
  column = 4;
  st_x = cent_col(win_width, num_columns, column); // location of the box
  st_y = 2* vert_st_disp;

  // ############ The first box (Box 41) #############
  // st_x, st_y - will point at the bottom center of the cap line (center top of the box)
  Box Bl41{Point{st_x,st_y}};
  Bl41.set_fill_color(Color::yellow); // all boxes are yellow
  //Bl41.add_caption("",Graph_lib::Font::times_bold);  // caption (single line)
  Bl41.add_text_line("FLTK code",Graph_lib::Font::times_bold); // Text (will automatically resize the box
  win.attach(Bl41);
  bottom = Bl41.s(); // calculate the bottom of the previous box
  st_y = bottom.y + vert_grid_step;


  // ############ Box 42 #############
  Box Bl42{Point{st_x,st_y}};
  Bl42.set_fill_color(Color::yellow); // all boxes are yellow
  Bl42.add_caption("GUI.h:",Graph_lib::Font::times_bold);  // caption (single line)
  Bl42.add_text_line("// GUI interface:"); // Text (will automatically resize the box
  Bl42.add_text_line("struct In_box {...};",Graph_lib::Font::times_bold); // Text (will automatically resize the box
  Bl42.add_text_line("...",Graph_lib::Font::times_bold); // Text (will automatically resize the box
  win.attach(Bl42);
  bottom = Bl42.s(); // calculate the bottom of the previous box
  st_y = bottom.y + vert_grid_step;

  // ############ Box 43 #############
  Box Bl43{Point{st_x,st_y}};
  Bl43.set_fill_color(Color::yellow); // all boxes are yellow
  Bl43.add_caption("GUI.cpp:",Graph_lib::Font::times_bold);  // caption (single line)
  Bl43.add_text_line("GUI code",Graph_lib::Font::times_bold); // Text (will automatically resize the box
  win.attach(Bl43);
  bottom = Bl43.s(); // calculate the bottom of the previous box
  st_y = bottom.y + vert_grid_step;


  // Template:
  // ############ Box 22 #############
  /*
  Box Bl22{Point{st_x,st_y}};
  Bl22.set_fill_color(Color::yellow); // all boxes are yellow
  Bl22.add_caption("",Graph_lib::Font::times_bold);  // caption (single line)
  Bl22.add_text_line("",Graph_lib::Font::times_bold); // Text (will automatically resize the box
  win.attach(Bl22);
  bottom = Bl22.s(); // calculate the bottom of the previous box
  st_y = bottom.y + vert_grid_step;
*/

  // ########### arrows #############
  // ########### Arrow Originate Column 1
  Arrow Arr_12_11 {Bl12.n(), Bl11.s(), 8, 4};
  Arr_12_11.set_fill_color(Color::black);
  win.attach(Arr_12_11);

  Arrow Arr_12_31 {Bl12.n(), Bl31.sw(), 8, 4};
  Arr_12_31.set_fill_color(Color::black);
  win.attach(Arr_12_31);

  Arrow Arr_13_12 {Bl13.n(), Bl12.s(), 8, 4};
  Arr_13_12.set_fill_color(Color::black);
  win.attach(Arr_13_12);

  // ########### Arrow Originate Column 2
  Arrow Arr_21_32 {Bl21.n(), Bl32.sw(), 8, 4};
  Arr_21_32.set_fill_color(Color::black);
  win.attach(Arr_21_32);

  Arrow Arr_22_12 {Bl22.n(), Bl12.s(), 8, 4};
  Arr_22_12.set_fill_color(Color::black);
  win.attach(Arr_22_12);

  Arrow Arr_22_33 {Bl22.n(), Bl33.sw(), 8, 4};
  Arr_22_33.set_fill_color(Color::black);
  win.attach(Arr_22_33);

  // ########### Arrow Originate Column 3
  Arrow Arr_32_11 {Bl32.nw(), Bl11.se(), 8, 4};
  Arr_32_11.set_fill_color(Color::black);
  win.attach(Arr_32_11);

  Arrow Arr_32_31 {Bl32.n(), Bl31.s(), 8, 4};
  Arr_32_31.set_fill_color(Color::black);
  win.attach(Arr_32_31);

  Arrow Arr_33_32 {Bl33.n(), Bl32.s(), 8, 4};
  Arr_33_32.set_fill_color(Color::black);
  win.attach(Arr_33_32);

  Arrow Arr_33_42 {Bl33.n(), Bl42.sw(), 8, 4};
  Arr_33_42.set_fill_color(Color::black);
  win.attach(Arr_33_42);

  // ########### Arrow Originate Column 4
  Arrow Arr_41_31 {Bl41.w(), Bl31.e(), 8, 4};
  Arr_41_31.set_fill_color(Color::black);
  win.attach(Arr_41_31);

  Arrow Arr_42_31 {Bl42.n(), Bl31.se(), 8, 4};
  Arr_42_31.set_fill_color(Color::black);
  win.attach(Arr_42_31);

  Arrow Arr_42_32 {Bl42.n(), Bl32.e(), 8, 4};
  Arr_42_32.set_fill_color(Color::black);
  win.attach(Arr_42_32);

  Arrow Arr_43_42 {Bl43.n(), Bl42.s(), 8, 4};
  Arr_43_42.set_fill_color(Color::black);
  win.attach(Arr_43_42);

  win.wait_for_button();  // display!


}


