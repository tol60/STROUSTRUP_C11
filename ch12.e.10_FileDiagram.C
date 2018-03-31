//
/* EX10 Draw thefile diagram from $12.8
 * EX9. Display an image on the screen, e.g. a photo of a friend. Label the image both with a title on the window and with a caption in the window.
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
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch12.e.10_FileDiagram.C \
           `fltk-config --ldflags --use-images` -o ch12.e.10_FileDiagram.exe 2>&1 | tee tmp.txt

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

// the function return the center of the column. column 1,2,3,...
int cent_col(int win_width, int num_columns, int column){
  int width = win_width/num_columns;
  return width * (column - 0.5);
}

int main ()
{
  using namespace Graph_lib;  // our graphics facilities are in Graph_lib namespace

  Point  tl {100,100};    // to become top left corner of window

  //cout << "Screen size:" << x_max() <<"*" <<y_max() << endl;
  //Simple_window win{tl, 600, 400, "ch12.e.10_FileDiagram"};   // make a simple window, {top_left, width, height, title}
  const int win_width = 800;
  const int win_hight = 700;
  Simple_window win{tl, win_width, win_hight, "ch12.e.10_FileDiagram"};   // make a simple window, {top_left, width, height, title}

  int st_x = 150;  // center of the box
  int st_y = 100;  // top of the box
  int text_hight = 15; // how much space do we need to reserve for caption.
  int boundary = 3;
  int box_width = 200;
  int num_lines = 1; // number of text lines to fit in the box
  int x,y = 0; //
  int vert_st_disp = 50; // Initial vertical displacement
  int vert_grid_step = 100;  // step between the boxes (vertical)
  int num_columns = 4;
  int column = 1;

  // ###############################
  // First Column
  // ###############################
  column = 1;
  st_x = cent_col(win_width, num_columns, column); // location of the box
  st_y = 2* vert_st_disp;

  // ############ The first box (Box 11) #############
  // st_x, st_y - will point at the bottom center of the cap line (center top of the box)
  box_width = 155;  // width of this box
  x = st_x - box_width/2;
  y = st_y;
  // Capton
  Text Bl11_cap{Point{x,y}, "Point.h:"};  // bottom left corner
  Bl11_cap.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl11_cap);

  // Box
  num_lines = 1; // number of text lines to fit in the box
  y+= boundary;
  Rectangle Bl11_box{Point{x,y},box_width,text_hight*num_lines + 2*boundary}; // top left corner, width, height
  Bl11_box.set_fill_color(Color::yellow);
  win.attach(Bl11_box);

  x+= boundary; // step from the left border
  // first line
  y+= boundary + text_hight; // we need the bottom
  Text Bl11_text_l1{Point{x,y}, "struct Point {...};"}; // bottom left
  Bl11_text_l1.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl11_text_l1);
/*
  // second line
  y+= text_hight; // extra line
  Text Bl1_text_l2{Point{x,y}, "class Window {...};"}; // bottom left
  Bl1_text_l2.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl1_text_l2);

  // third line
  y+= text_hight; // extra line
  Text Bl1_text_l3{Point{x,y}, "..."}; // bottom left
  Bl1_text_l3.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl1_text_l3);
*/
  // ###### Box 11 done
  // #####################################

  st_y = y + vert_grid_step;
  // ############ Box 12 #############
  // st_x, st_y - will point at the bottom center of the cap line (center top of the box)
  box_width = 155;  // width of this box
  x = st_x - box_width/2;
  y = st_y;
  // Capton
  Text Bl12_cap{Point{x,y}, "Graph.h:"};  // bottom left corner
  Bl12_cap.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl12_cap);

  // Box
  num_lines = 3; // number of text lines to fit in the box
  y+= boundary;
  Rectangle Bl12_box{Point{x,y},box_width,text_hight*num_lines + 2*boundary}; // top left corner, width, height
  Bl12_box.set_fill_color(Color::yellow);
  win.attach(Bl12_box);

  x+= boundary; // step from the left border
  // first line
  y+= boundary + text_hight; // we need the bottom
  Text Bl12_text_l1{Point{x,y}, "// graphing interface:"}; // bottom left
  win.attach(Bl12_text_l1);

  // second line
  y+= text_hight; // extra line
  Text Bl12_text_l2{Point{x,y}, "struct Shape {...};"}; // bottom left
  Bl12_text_l2.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl12_text_l2);

  // third line
  y+= text_hight; // extra line
  Text Bl12_text_l3{Point{x,y}, "..."}; // bottom left
  Bl12_text_l3.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl12_text_l3);

  // ###### Box 12 done
  // #####################################

  st_y = y + vert_grid_step;
  // ############ Box 13 #############
  // st_x, st_y - will point at the bottom center of the cap line (center top of the box)
  box_width = 155;  // width of this box
  x = st_x - box_width/2;
  y = st_y;
  // Capton
  Text Bl13_cap{Point{x,y}, "Graph.cpp:"};  // bottom left corner
  Bl13_cap.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl13_cap);

  // Box
  num_lines = 1; // number of text lines to fit in the box
  y+= boundary;
  Rectangle Bl13_box{Point{x,y},box_width,text_hight*num_lines + 2*boundary}; // top left corner, width, height
  Bl13_box.set_fill_color(Color::yellow);
  win.attach(Bl13_box);

  x+= boundary; // step from the left border
  // first line
  y+= boundary + text_hight; // we need the bottom
  Text Bl13_text_l1{Point{x,y}, "Graph code"}; // bottom left
  Bl13_text_l1.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl13_text_l1);

  /*
  // second line
  y+= text_hight; // extra line
  Text Bl13_text_l2{Point{x,y}, "struct Shape {...};"}; // bottom left
  Bl13_text_l2.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl13_text_l2);

  // third line
  y+= text_hight; // extra line
  Text Bl13_text_l3{Point{x,y}, "..."}; // bottom left
  Bl13_text_l3.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl13_text_l3);
*/
  // ###### Box 13 done
  // #####################################



  // ###############################
  // Second Column
  // ###############################
  column = 2;
  st_x = cent_col(win_width, num_columns, column); // location of the box
  st_y = 6 * vert_st_disp;

  // ############ The first box (Box 21) #############
  // st_x, st_y - will point at the bottom center of the cap line (center top of the box)
  box_width = 120;  // width of this box
  x = st_x - box_width/2;
  y = st_y;
  // Capton
  Text Bl21_cap{Point{x,y}, "window.cpp:"};  // bottom left corner
  Bl21_cap.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl21_cap);

  // Box
  num_lines = 1; // number of text lines to fit in the box
  y+= boundary;
  Rectangle Bl21_box{Point{x,y},box_width,text_hight*num_lines + 2*boundary}; // top left corner, width, height
  Bl21_box.set_fill_color(Color::yellow);
  win.attach(Bl21_box);

  x+= boundary; // step from the left border
  // first line
  y+= boundary + text_hight; // we need the bottom
  Text Bl21_text_l1{Point{x,y}, "Window code"}; // bottom left
  Bl21_text_l1.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl21_text_l1);
/*
  // second line
  y+= text_hight; // extra line
  Text Bl1_text_l2{Point{x,y}, "class Window {...};"}; // bottom left
  Bl1_text_l2.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl1_text_l2);

  // third line
  y+= text_hight; // extra line
  Text Bl1_text_l3{Point{x,y}, "..."}; // bottom left
  Bl1_text_l3.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl1_text_l3);
*/
  // ###### Box 21 done
  // #####################################

  st_y = y + vert_grid_step;
  // ############ Box 22 #############
  // st_x, st_y - will point at the bottom center of the cap line (center top of the box)
  box_width = 230;  // width of this box
  x = st_x - box_width/2;
  y = st_y;
  // Capton
  Text Bl22_cap{Point{x,y}, "chapter12.cpp:"};  // bottom left corner
  Bl22_cap.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl22_cap);

  // Box
  num_lines = 3; // number of text lines to fit in the box
  y+= boundary;
  Rectangle Bl22_box{Point{x,y},box_width,text_hight*num_lines + 2*boundary}; // top left corner, width, height
  Bl22_box.set_fill_color(Color::yellow);
  win.attach(Bl22_box);

  x+= boundary; // step from the left border
  // first line
  y+= boundary + text_hight; // we need the bottom
  Text Bl22_text_l1{Point{x,y}, "#include \"Graph.h\""}; // bottom left
  Bl22_text_l1.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl22_text_l1);

  // second line
  y+= text_hight; // extra line
  Text Bl22_text_l2{Point{x,y}, "#include \"Simple_window.h\""}; // bottom left
  Bl22_text_l2.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl22_text_l2);

  // third line
  y+= text_hight; // extra line
  Text Bl22_text_l3{Point{x,y}, "int main() {...}"}; // bottom left
  Bl22_text_l3.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl22_text_l3);

  // ###### Box 22 done
  // #####################################


  // ###############################
  // Third Column
  // ###############################
  column = 3;
  st_x = cent_col(win_width, num_columns, column); // location of the box
  st_y = vert_st_disp;
  // ############ The first box (Box 31) #############
  // st_x, st_y - will point at the bottom center of the cap line (center top of the box)
  box_width = 110;  // width of this box
  x = st_x - box_width/2;
  y = st_y;
  // Capton
/*  Text Bl1_cap{Point{x,y}, "Window.h:"};  // bottom left corner
  Bl1_cap.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl1_cap);
*/
  // Box
  num_lines = 1; // number of text lines to fit in the box
  y+= boundary;
  Rectangle Bl31_box{Point{x,y},box_width,text_hight*num_lines + 2*boundary}; // top left corner, width, height
  Bl31_box.set_fill_color(Color::yellow);
  win.attach(Bl31_box);

  x+= boundary; // step from the left border
  // first line
  y+= boundary + text_hight; // we need the bottom
  Text Bl31_text_l1{Point{x,y}, "FLTK headers"}; // bottom left
  win.attach(Bl31_text_l1);
/*
  // second line
  y+= text_hight; // extra line
  Text Bl1_text_l2{Point{x,y}, "class Window {...};"}; // bottom left
  Bl1_text_l2.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl1_text_l2);

  // third line
  y+= text_hight; // extra line
  Text Bl1_text_l3{Point{x,y}, "..."}; // bottom left
  Bl1_text_l3.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl1_text_l3);
*/
  // ###### Box 31 done
  // #####################################

  st_y = y + vert_grid_step;
  // ############ Box 32 #############
  // st_x, st_y - will point at the bottom center of the cap line (center top of the box)
  box_width = 155;  // width of this box
  x = st_x - box_width/2;
  y = st_y;
  // Capton
  Text Bl32_cap{Point{x,y}, "Window.h:"};  // bottom left corner
  Bl32_cap.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl32_cap);

  // Box
  num_lines = 3; // number of text lines to fit in the box
  y+= boundary;
  Rectangle Bl32_box{Point{x,y},box_width,text_hight*num_lines + 2*boundary}; // top left corner, width, height
  Bl32_box.set_fill_color(Color::yellow);
  win.attach(Bl32_box);

  x+= boundary; // step from the left border
  // first line
  y+= boundary + text_hight; // we need the bottom
  Text Bl32_text_l1{Point{x,y}, "// window interface:"}; // bottom left
  win.attach(Bl32_text_l1);

  // second line
  y+= text_hight; // extra line
  Text Bl32_text_l2{Point{x,y}, "class Window {...};"}; // bottom left
  Bl32_text_l2.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl32_text_l2);

  // third line
  y+= text_hight; // extra line
  Text Bl32_text_l3{Point{x,y}, "..."}; // bottom left
  Bl32_text_l3.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl32_text_l3);

  // ###### Box 32 done
  // #####################################

  st_y = y + vert_grid_step;
  // ############ Box 34 #############
  // st_x, st_y - will point at the bottom center of the cap line (center top of the box)
  box_width = 155;  // width of this box
  x = st_x - box_width/2;
  y = st_y;
  // Capton
  Text Bl34_cap{Point{x,y}, "Simple_window.h:"};  // bottom left corner
  Bl34_cap.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl34_cap);

  // Box
  num_lines = 3; // number of text lines to fit in the box
  y+= boundary;
  Rectangle Bl34_box{Point{x,y},box_width,text_hight*num_lines + 2*boundary}; // top left corner, width, height
  Bl34_box.set_fill_color(Color::yellow);
  win.attach(Bl34_box);

  x+= boundary; // step from the left border
  // first line
  y+= boundary + text_hight; // we need the bottom
  Text Bl34_text_l1{Point{x,y}, "// window interface:"}; // bottom left
  win.attach(Bl34_text_l1);

  // second line
  y+= text_hight; // extra line
  Text Bl34_text_l2{Point{x,y}, "class Window {...};"}; // bottom left
  Bl34_text_l2.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl34_text_l2);

  // third line
  y+= text_hight; // extra line
  Text Bl34_text_l3{Point{x,y}, "..."}; // bottom left
  Bl34_text_l3.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl34_text_l3);

  // ###### Box 34 done
  // #####################################


  // ###############################
  // Fourth Column
  // ###############################
  column = 4;
  st_x = cent_col(win_width, num_columns, column); // location of the box
  st_y = 2* vert_st_disp;

  // ############ The first box (Box 41) #############
  // st_x, st_y - will point at the bottom center of the cap line (center top of the box)
  box_width = 155;  // width of this box
  x = st_x - box_width/2;
  y = st_y;
  // Capton
  /*
  Text Bl41_cap{Point{x,y}, "FLTK code"};  // bottom left corner
  win.attach(Bl41_cap);
*/
  // Box
  num_lines = 1; // number of text lines to fit in the box
  y+= boundary;
  Rectangle Bl41_box{Point{x,y},box_width,text_hight*num_lines + 2*boundary}; // top left corner, width, height
  Bl41_box.set_fill_color(Color::yellow);
  win.attach(Bl41_box);

  x+= boundary; // step from the left border
  // first line
  y+= boundary + text_hight; // we need the bottom
  Text Bl41_text_l1{Point{x,y}, "FLTK code"}; // bottom left
  Bl41_text_l1.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl41_text_l1);
/*
  // second line
  y+= text_hight; // extra line
  Text Bl4_text_l2{Point{x,y}, "class Window {...};"}; // bottom left
  Bl4_text_l2.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl4_text_l2);

  // third line
  y+= text_hight; // extra line
  Text Bl4_text_l3{Point{x,y}, "..."}; // bottom left
  Bl4_text_l3.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl4_text_l3);
*/
  // ###### Box 41 done
  // #####################################

  st_y = y + vert_grid_step;
  // ############ Box 42 #############
  // st_x, st_y - will point at the bottom center of the cap line (center top of the box)
  box_width = 155;  // width of this box
  x = st_x - box_width/2;
  y = st_y;
  // Capton
  Text Bl42_cap{Point{x,y}, "GUI.h:"};  // bottom left corner
  Bl42_cap.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl42_cap);

  // Box
  num_lines = 3; // number of text lines to fit in the box
  y+= boundary;
  Rectangle Bl42_box{Point{x,y},box_width,text_hight*num_lines + 2*boundary}; // top left corner, width, height
  Bl42_box.set_fill_color(Color::yellow);
  win.attach(Bl42_box);

  x+= boundary; // step from the left border
  // first line
  y+= boundary + text_hight; // we need the bottom
  Text Bl42_text_l1{Point{x,y}, "// GUI interface:"}; // bottom left
  win.attach(Bl42_text_l1);

  // second line
  y+= text_hight; // extra line
  Text Bl42_text_l2{Point{x,y}, "struct In_box {...};"}; // bottom left
  Bl42_text_l2.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl42_text_l2);

  // third line
  y+= text_hight; // extra line
  Text Bl42_text_l3{Point{x,y}, "..."}; // bottom left
  Bl42_text_l3.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl42_text_l3);

  // ###### Box 42 done
  // #####################################

  st_y = y + vert_grid_step;
  // ############ Box 43 #############
  // st_x, st_y - will point at the bottom center of the cap line (center top of the box)
  box_width = 155;  // width of this box
  x = st_x - box_width/2;
  y = st_y;
  // Capton
  Text Bl43_cap{Point{x,y}, "GUI.cpp:"};  // bottom left corner
  Bl43_cap.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl43_cap);

  // Box
  num_lines = 1; // number of text lines to fit in the box
  y+= boundary;
  Rectangle Bl43_box{Point{x,y},box_width,text_hight*num_lines + 2*boundary}; // top left corner, width, height
  Bl43_box.set_fill_color(Color::yellow);
  win.attach(Bl43_box);

  x+= boundary; // step from the left border
  // first line
  y+= boundary + text_hight; // we need the bottom
  Text Bl43_text_l1{Point{x,y}, "GUI code"}; // bottom left
  Bl43_text_l1.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl43_text_l1);

  /*
  // second line
  y+= text_hight; // extra line
  Text Bl43_text_l2{Point{x,y}, "struct Shape {...};"}; // bottom left
  Bl43_text_l2.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl43_text_l2);

  // third line
  y+= text_hight; // extra line
  Text Bl43_text_l3{Point{x,y}, "..."}; // bottom left
  Bl43_text_l3.set_font(Graph_lib::Font::times_bold); // make it bold
  win.attach(Bl43_text_l3);
*/
  // ###### Box 43 done
  // #####################################

  win.wait_for_button();  // display!

}


