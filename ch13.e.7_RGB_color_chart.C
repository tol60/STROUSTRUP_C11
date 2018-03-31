//
/* 7. Make an RGB color chart (http://www.rapidtables.com/web/color/RGB_Color.htm#color-chart)

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
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch13.e.7_RGB_color_chart.C \
           `fltk-config --ldflags --use-images` -o ch13.e.7_RGB_color_chart.exe 2>&1 | tee tmp.txt

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

Graph_lib::Color index2Color(int i) {
  uchar r = (i%3==0) ? 0xFF: 0x00;
  uchar g = (i%3==1) ? 0xFF: 0x00;
  uchar b = (i%3==2) ? 0xFF: 0x00;
  return Graph_lib::Color(r,g,b);
}

int main ()
{
  using namespace Graph_lib;  // our graphics facilities are in Graph_lib namespace

  constexpr Point pt{100,100};    // to become top left corner of window

  Simple_window win {pt, 600, 400,"ch13.e.7_RGB_color_chart"};  // make a simple window, {top_left, width, hight, title}

  /*
  Vector_ref<Rectangle> rect; // store named or unnamed objects

  Rectangle x{Point{100,200},Point{200,300}};
  rect.push_back(x);  // add named

  rect.push_back(new Rectangle{Point{50,60},Point{80,90}});  // add unnamed

  for (int i=0; i<rect.size(); ++i) rect[i].move(10,10);  // use rect

  Vector_ref<Rectangle> vr;

  for(int i=0; i<16; ++i)
    for (int j=0; j<16; ++j) {
      vr.push_back(new Rectangle{Point{i*20,j*20},20,20});
      vr[vr.size()-1].set_fill_color(Color{i*16+j});
      win.attach(vr[vr.size()-1]);
    }
*/

  /*
  unsigned int h = 0xFF;
  for (int i=1; i<15; ++i )
    cout << showbase << hex << h << " divided by " << i << " = " << h/i << endl;
*/
  constexpr int size_x = 20;
  constexpr int size_y = size_x;
  constexpr int part_x = 5; // has to be odd, >=3
  constexpr int mid_ind_x = part_x/2; // 2 - index in the middle [0,1,2,3,4]
  constexpr float fl_den = mid_ind_x; // we want to calculate 1/fl_den

  constexpr int part_y = 5; // The final vertical span will contain 2*part_y -1 blocs
  constexpr float fl_den_y = part_y; // we want to calculate 1/fl_den
  Vector_ref<Rectangle> vr;
  // (x,y) = (i, j)
  int x=0;
  int y=0;
  Color paint(0); // the color of the middle row (consider paintX)
  Color paintY(0); // the final color we will paint with
  Color colBlk(0,0,0);
  Color colWht(0xFF,0xFF,0xFF);
  for(int i=0; i<3; ++i){
    Color colA = index2Color(i); // (0,1,2) = (all red, all green, all blue), Example 0xFF0000_00 - red
    Color colB = index2Color(i+1); // this was based on Mod 3; Example 0x00FF00_00 - green
    Color colMid ( (unsigned int) colA.as_int() + (unsigned int) colB.as_int()); // Example 0xFFFF00_00 - Mixed (= yellow)
    for (int k=0;k<part_x-1;++k){
      //color = color1 * weight  + color2 * (1 - weight)
      if (k<mid_ind_x) {  // colA | colMid
        paint = Color(colMid,colA,k/fl_den); // Example: should yield 0xFF0000_00 and 0xFF7f00_00 for mid_ind_x = 2,
      } else if (k == mid_ind_x) {
        paint = colMid;
      } else { // colMid | colB
        paint = Color(colB,colMid,(k-mid_ind_x)/fl_den); // Example: should yield 0x7fFF00_00. Note we prefer 0x80 instead of 0x7f
      }
      // x is fixed as i*(part_x-1)+ k
      // we do not write the last column, as we would cover it on the next iteration of i
      x = i*(part_x-1)+ k;

      // Now calculate y (and final color paintY)
      // first half (part_y vertical blocks:  colBlk | paint
      y = 0;
      for (int j=0; j<part_y; ++j) {
        //color = color1 * weight  + color2 * (1 - weight)
        // colBlk | paint
        paintY = Color(paint,colBlk,(j+1)/fl_den_y); // 1/5, 2/5, 3/5, 4/4, 1 = 5/5

        y=j; // explicit
        vr.push_back(new Rectangle{Point{x*size_x,y*size_y},size_x,size_y}); // add a new rectangle
        // Pick the color:
        //vr[vr.size()-1].set_fill_color(index2Color(i)); // color the new rectangle
        // vr[vr.size()-1].set_fill_color(paint); // color the new rectangle
        vr[vr.size()-1].set_fill_color(paintY); // color the new rectangle
        win.attach(vr[vr.size()-1]);  // show the new rectangle
      }

      // Second half (part_y -1 vertical blocks:  paint | colWht) Note we already painted pure "paint" row
      for (int j=1; j<part_y; ++j) { // note skipping j=0 on purpose: we aready painted pure "paint" row
        //color = color1 * weight  + color2 * (1 - weight)
        // paint | colWht
        paintY = Color(colWht,paint,j/fl_den_y); // 1/5, 2/5, 3/5, 4/5
        y = part_y + j -1;
        vr.push_back(new Rectangle{Point{x*size_x,y*size_y},size_x,size_y}); // add a new rectangle
        vr[vr.size()-1].set_fill_color(paintY); // color the new rectangle
        win.attach(vr[vr.size()-1]);  // show the new rectangle
      }
    }
  }

  // Last column - all the shades from black to white.
  x += 1;
  float fl_weight = 2*(part_y - 1); // part_y = 5, then fl_wight = 8.0
  for (int j=0; j<2*part_y-1; ++j){ // part_y = 5, then we get 0,1,...,7,8
    //color = color1 * weight  + color2 * (1 - weight)
    // colBlk | colWht
    paintY = Color(colWht,colBlk,j/fl_weight); // 0/8, 1/8, 2/8, 3/8,...,7/8, 1 = 8/8
    y = j; // explicit
    vr.push_back(new Rectangle{Point{x*size_x,y*size_y},size_x,size_y}); // add a new rectangle
    vr[vr.size()-1].set_fill_color(paintY); // color the new rectangle
    win.attach(vr[vr.size()-1]);  // show the new rectangle
  }

  win.wait_for_button();  // display!


}


