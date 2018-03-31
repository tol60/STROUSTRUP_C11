
/* ch14.e.11_Binary_tree
 * E11 Define a Binary_tree class derived from Shape. Give the number of levels as a parameter (levels==0 means no nodes,
 *     levels==1 means one node,
 *     levels==2 means one top node with two sub-nodes,
 *     levels==3 means one top node with two sub-nodes each, with two sub-nodes, etc).
 *     Let a node be represented by a small circle. Connect the nodes by lines (as is conventional).
 *     PS. In computer science, trees grow downward from a top node (amusingly, but logially, often called the root).
 * E9. Define a Group to be a container of Shapes with suitable operations applied to the various members of the Group.
 *     Hint: Vector_ref. Use a Group to define a checkers (draughts) board where pieces can be moved under program control.
 * E8. Define a class Octagon to be a regular octagon. Write a test that exercises all of its functions
 *     (as defined by you or inherited from Shape).
 * E7. Define a Striped_closed_polyline using the technique from Striped_rectangle (this requires some algorithmic inventiveness).
 * E6. Define a Striped_circle using the technique from Striped_rectangle.
 * E5. Define a Striped_rectangle where instead of fill, the rectangle is "filled" by drawing one-pixel-wide
 *     hirizontal lines across the inside of the rectangle (say, draw every second line like that).
 *     You may have to play with the width of lines and the line spacing to get a pattern you like.
 * E4. Define a class Immobile_Circle, which is just like Circle but can't be moved.
 * E1. Define two classes Smiley and Frowny, which are both derived from class Circle and have
 *    two eyes and a mouth. Next derive classes from Smiley and Frowny which add an appropriate hat to each.

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
g++ -g -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch14.e.11_Binary_tree.C \
           `fltk-config --ldflags --use-images` -o ch14.e.11_Binary_tree.exe 2>&1 | tee tmp.txt

Note:
fltk-config --ldflags --use-images
-L/usr/local/lib -lfltk_images -lpng -lz -lfltk_jpeg -lfltk -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11

convert Stepa_mod.JPG -resize 10% test.JPG
*/

//#include "std_lib_facilities.h"

#include "Simple_window.h"  // get access to our window library
//#include "Window.h"
#include "Graph.h"          // get access to our graphics library facilities

int main ()
{
  using namespace Graph_lib;  // our graphics facilities are in Graph_lib namespace

  constexpr Point pt{100,100};    // to become top left corner of window
  Simple_window win {pt, 600, 400,"ch14.e.11_Binary_tree"};  // make a simple window, {top_left, width, hight, title}

  constexpr Point top{300, 100};
  constexpr int cell_size = 10;

  //constexpr int levels = 2;
  //constexpr Point sz_diag{50,50};  // Size of the diagram

  //constexpr int levels = 3;
  //constexpr Point sz_diag{100,100};  // Size of the diagram

  constexpr int levels = 4;
  constexpr Point sz_diag{150,150};  // Size of the diagram


  Binary_tree btree{top, sz_diag, cell_size, levels}; // checker board
  win.attach(btree);



  win.wait_for_button();
}


