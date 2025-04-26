
/* ch15.d.3_ClassDefinition
 * B9. Write a function sloping_cos() that adds a cosine to slope() (as defined above) and ad to the window
 * B8. Make the cosine blue
 * B7. Add a cosine to the window (don't write a new function)
 * B6. Add double square(double x) {return x*x;} to the window
 * B5. Label the slope with a Text "x/2" at a point just above its bottom left end point.
 * B4. Add double slope(double x){return x/2;} to the window
 * B3. From now on use that range, scale, etc. for all graphs.
 * B2. Change it to use x scale 20 and y scale 20
 * B1. Graph the function double one(double x) {return 1;} in the range [-10, 11] with (0,0) at (300,300) using 400 points and no scaling (in the window).
 *
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
g++ -g -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch15.d.3_ClassDefinition.C \
           `fltk-config --ldflags --use-images` -o ch15.d.3_ClassDefinition.exe 2>&1 | tee tmp.txt

Note:
fltk-config --ldflags --use-images
-L/usr/local/lib -lfltk_images -lpng -lz -lfltk_jpeg -lfltk -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11

convert Stepa_mod.JPG -resize 10% test.JPG
*/

//#include "std_lib_facilities.h"

//#include "Simple_window.h"  // get access to our window library
#include "Window.h"
#include "Graph.h"          // get access to our graphics library facilities

double one(double x) {return 1;}
double slope(double x){return x/2;}
double square (double x) {return x*x;}
double sloping_cos(double x) {return slope(x) + cos(x);}

// C1. Define a struct Person containing a string name and an int age
struct Person {
  string name;
  int age;
  Person(string name, int age):name{name},age{age} {}
  Person():age{0}{}
};
ostream& operator << (ostream& os, const Person& per) {
  return os << '(' << per.name << ';' << per.age << ')';
}
istream& operator >> (istream& is, Person& per){
  // assume format (name; age)
  char ch1 = 0;
  char ch2 = 0;
  char ch3 = 0;
  Person dd;
  if (is >> ch1 >> dd.name
      >> ch2 >> dd.age
      >> ch3) {
    if (ch1 !='(' || ch2 != ';' || ch3 != ')') {
      is.clear(ios_base::failbit);
      return is;
    }

  } else
    return is;

  per = dd;
  return is;
}

int main ()
{
  using namespace Graph_lib;  // our graphics facilities are in Graph_lib namespace

  constexpr Point pt{100,100};    // to become top left corner of window

  constexpr int xmax = 600;
  constexpr int ymax = 600;

  constexpr int x_orig = xmax/2;  // position of (0,0) is center of window
  constexpr int y_orig = ymax/2;
  constexpr Point orig {x_orig, y_orig};

  constexpr int r_min = -10; // range [-10:11)
  constexpr int r_max = 11;

  constexpr int n_points = 400; // number of points used in range

  //constexpr int x_scale = 1; // scaling factors
  //constexpr int y_scale = 1;

  constexpr int x_scale = 20; // scaling factors
  constexpr int y_scale = 20;

  constexpr int ax_length = 400; // length of the axes
  constexpr int num_pix_per_notch = 20; // number of pixels per notch

  constexpr int label_raise = 10; // how far we need to lift the label from off the function to make it look pretty

  //Simple_window win {pt, 600, 400,"ch15.d.3_ClassDefinition"};  // make a simple window, {top_left, width, height, title}
  Graph_lib::Window win {pt, xmax, ymax, "ch15.d.3_ClassDefinition"};  // make a simple window, {top_left, width, height, title}

  // Axis(Orientation d, Point xy, int length, int nummber_of_notches=0, string label = "");
  Axis ax_x {Axis::x, Point{orig.x - ax_length/2, orig.y}, ax_length, ax_length/num_pix_per_notch, "1==20 pixels"}; // left-right
  ax_x.set_color(Color::red);
  win.attach(ax_x);

  Axis ax_y {Axis::y, Point{orig.x, orig.y + ax_length/2}, ax_length, ax_length/num_pix_per_notch, "1==20 pixels"}; // bottom - up
  ax_y.set_color(Color::red);
  win.attach(ax_y);


  //Function f1(one, r_min, r_max, orig, n_points); // default scaling
  Function f1{one, r_min, r_max, orig, n_points, x_scale, y_scale };
  win.attach(f1);

  Function f2{slope, r_min, r_max, orig, n_points, x_scale, y_scale };
  win.attach(f2);

  int x = ax_x.point(0).x; // get the coordinate of the left point of the axis
  int y = orig.y - slope(r_min)*y_scale - label_raise;
  Text ts2(Point{x,y}, "x/2");
  //cout << "Point{x,y} = " << Point{x,y} << endl;
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


  //cout << "Hallo" << endl;
  Person per{"Goofy", 63};
  cout << per << endl;
  cout << "Enter a new person info (name;age)" << endl;

  cin >> per;
  cout << per << endl;

  //gui_main();



  // Simple_window use format:
  //Binary_tree btree{top, sz_diag, cell_size, levels}; // checker board
  //win.attach(btree);

  // win.wait_for_button(); // this applies to Simple_window only
}


