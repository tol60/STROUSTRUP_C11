
/* ch14.e.7_Striped_closed_polyline
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

Algorithms for filling up polygons:
https://www.tutorialspoint.com/computer_graphics/polygon_filling_algorithm.htm

   //g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch14.e.7_Striped_closed_polyline.C \
           `fltk-config --ldflags --use-images` -o ch14.e.7_Striped_closed_polyline.exe 2>&1 | tee tmp.txt

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
  Simple_window win {pt, 600, 400,"ch14.e.7_Striped_closed_polyline"};  // make a simple window, {top_left, width, hight, title}

  constexpr Point centA{300, 200};
  constexpr int radius = 150;

  // This is sample using standard example from Stroustrup
  Closed_polyline cp_ref{{500,100},{550,300},{500,200},{450,300}}; // refernce (closed polyline)
  cp_ref.set_fill_color(Color::blue);
  win.attach(cp_ref);

  // This is example from Excercise
  Striped_closed_polyline scpol_Big{{300,100},{400,300},{300,200},{200,300}}; // original fail
  scpol_Big.set_fill_color(Color::green);
  win.attach(scpol_Big);

  // Criss-Cross
  Striped_closed_polyline scpol_CrissCross{{100,50},{200,50}, {100,150}, {200,200}};
  scpol_CrissCross.set_fill_color(Color::dark_cyan);
  scpol_CrissCross.set_step(1);
  win.attach(scpol_CrissCross);

  Striped_closed_polyline scpol_Tri{{500,50}, {550,75}, {525,100}};
  scpol_Tri.set_fill_color(Color::red);
  win.attach(scpol_Tri);

  // Smaller samples:
  Striped_closed_polyline scpol_top{{30,10},{45,30},{20,30}}; // base parallel (pick at top)
  scpol_top.set_fill_color(Color::blue);
  win.attach(scpol_top);

  Striped_closed_polyline scpol_bot{{30,50},{60,50},{45,90}}; // base parallel (pick at top)
  scpol_bot.set_fill_color(Color::yellow);
  win.attach(scpol_bot);

  int disp  = 40;
  // The following triangle will be very close to scpol_bot, but verticies shuffled
  // I believe there is a difference if we are drawing left to right or right to left
  Striped_closed_polyline scpol_bot_Shufl{{45+disp,90},{60+disp,50},{30+disp,50}}; // base parallel (pick at top)
  scpol_bot_Shufl.set_fill_color(Color::yellow);
  win.attach(scpol_bot_Shufl);

  Striped_closed_polyline scpol_tb{{30,150},{60,180},{45,190}}; // top-bottom base parallel (pick at top)
  scpol_tb.set_fill_color(Color::red);
  win.attach(scpol_tb);


  Striped_closed_polyline scpol_vertLine{{30,200},{30,200},{30,250}}; // base parallel (pick at top)
  scpol_vertLine.set_fill_color(Color::yellow);
  //scpol_vertLine.set_color(Color::Transparency::invisible);
  win.attach(scpol_vertLine);

  Striped_closed_polyline scpol_angleLine{{30,250},{30,250},{45,290}}; // base parallel (pick at top)
  scpol_angleLine.set_fill_color(Color::yellow);
  //scpol_angleLine.set_color(Color::Transparency::invisible);
  win.attach(scpol_angleLine);


  /*
  Striped_circle str_cir{centA, radius};
  str_cir.set_fill_color(Color::red);
  win.attach(str_cir);
*/

  // Demonstration of rounding problem:
  // Point A{0,0};
  // Point B{15,40};
  //  Point A{30,250};
  //  Point B{45,290};
  // put the pair in reverse, getting mismatch
  // Point A{45,290};
  // Point B{30,250};
  /* Sample:
  Point A{45,260};
  Point B{30,250};
  i = 0; y = 260; x_one = 45; x_two = 45;
  i = 1; y = 261; x_one = 43; x_two = 44; Mismatch of 1
  i = 2; y = 262; x_one = 42; x_two = 42;
  i = 3; y = 263; x_one = 40; x_two = 41; Mismatch of 1
  i = 4; y = 264; x_one = 39; x_two = 39;
  i = 5; y = 265; x_one = 37; x_two = 38; Mismatch of 1
  i = 6; y = 266; x_one = 36; x_two = 36;
  i = 7; y = 267; x_one = 34; x_two = 35; Mismatch of 1
  i = 8; y = 268; x_one = 33; x_two = 33;
  i = 9; y = 269; x_one = 31; x_two = 32; Mismatch of 1
  i = 10; y = 270; x_one = 30; x_two = 30;

  int height = B.y - A.y; // 40
  int stripe_gap = 1;
  int stripe_disp = 0;
  int direction = 1; // if A is on top (A.y is the smallest), y will be incrementing
  if (height < 0) { // Y axis down, it means that the point A is below the base line
    height = -height;
    direction = -1;
    stripe_disp = (stripe_gap-stripe_disp)%stripe_gap; // as we start going from the bottom up, we need to adjust
  }

  const double delx_B = (B.x-A.x)/(double)height;
  //for (int i=0; i<=height; i+=1){  // hight is 2, but 3 rows, need <= hight
  for (int i=stripe_disp; i<=height; i+=stripe_gap){
    int line_y = A.y + i; // the y coordinte of the line
    // we start with A and then calculate the displacement
    int line_x_one = A.x + delx_B*i; // this should be the most accurate
    int line_x_two = A.x + (B.x-A.x)*i/height;
    cout << "i = " << i << "; y = " << line_y << "; x_one = " << line_x_one
        << "; x_two = " << line_x_two << ";";
    if (line_x_one != line_x_two)
      cout << " Mismatch of " << (line_x_two - line_x_one);
    cout<< endl;
  }
*/

  // The same demonstration side by side:
  /*
   *  j=0; A=(30;250); B=(45;260)
      height=10
      After adjustment:
         height=10; direction=1stripe_disp=0; stripe_gap=1
      i = 0; y = 250; x_one = 30; x_two = 30;
      i = 1; y = 251; x_one = 31; x_two = 31;
      i = 2; y = 252; x_one = 33; x_two = 33;
      i = 3; y = 253; x_one = 34; x_two = 34;
      i = 4; y = 254; x_one = 36; x_two = 36;
      i = 5; y = 255; x_one = 37; x_two = 37;
      i = 6; y = 256; x_one = 39; x_two = 39;
      i = 7; y = 257; x_one = 40; x_two = 40;
      i = 8; y = 258; x_one = 42; x_two = 42;
      i = 9; y = 259; x_one = 43; x_two = 43;
      i = 10; y = 260; x_one = 45; x_two = 45;

      j=1; A=(45;260); B=(30;250)
      height=-10
      After adjustment:
         height=10; direction=-1stripe_disp=0; stripe_gap=1
      i = 0; y = 260; x_one = 45; x_two = 45;
      i = 1; y = 259; x_one = 43; x_two = 44; Mismatch of 1
      i = 2; y = 258; x_one = 42; x_two = 42;
      i = 3; y = 257; x_one = 40; x_two = 41; Mismatch of 1
      i = 4; y = 256; x_one = 39; x_two = 39;
      i = 5; y = 255; x_one = 37; x_two = 38; Mismatch of 1
      i = 6; y = 254; x_one = 36; x_two = 36;
      i = 7; y = 253; x_one = 34; x_two = 35; Mismatch of 1
      i = 8; y = 252; x_one = 33; x_two = 33;
      i = 9; y = 251; x_one = 31; x_two = 32; Mismatch of 1
      i = 10; y = 250; x_one = 30; x_two = 30;
   *
   */


  Point A{30,250};
  Point B{45,260};
  for (int j=0; j<2; j++){
    if (j==1) {
      // swap the points
      Point tpt = A;
      A = B;    // Point{45,290};
      B = tpt;  // Point{30,250};
    }
    cout << "j="<<j << "; A="<<A<<"; B="<<B <<endl;
    int height = B.y - A.y; // 40
    cout << "height="<<height<<endl;
    int stripe_gap = 1;
    int stripe_disp = 0;
    int direction = 1; // if A is on top (A.y is the smallest), y will be incrementing
    if (height < 0) { // Y axis down, it means that the point A is below the base line
      height = -height;
      direction = -1;
      stripe_disp = (stripe_gap-stripe_disp)%stripe_gap; // as we start going from the bottom up, we need to adjust
    }
    cout << "After adjustment:\n"
        <<"\t height="<<height<<"; direction="<<direction<<"stripe_disp="<<stripe_disp
        <<"; stripe_gap="<<stripe_gap<<endl;

    const double delx_B = (B.x-A.x)/(double)height;
    //for (int i=0; i<=height; i+=1){  // hight is 2, but 3 rows, need <= hight
    for (int i=stripe_disp; i<=height; i+=stripe_gap){
      int line_y = A.y + i*direction; // the y coordinte of the line
      // we start with A and then calculate the displacement
      int line_x_one = A.x + delx_B*i; // this should be the most accurate
      int line_x_two = A.x + (B.x-A.x)*i/height;
      cout << "i = " << i << "; y = " << line_y << "; x_one = " << line_x_one
          << "; x_two = " << line_x_two << ";";
      if (line_x_one != line_x_two)
        cout << " Mismatch of " << (line_x_two - line_x_one);
      cout<< endl;
    }
    cout << endl; // end of j iteration
  }

  // Calculation:
  // 15* 1 /10 produced the same as int (15/10.0 *1)
  // 15*(-1) /10  produced different as int (15/10.0 *(-1))
  cout << "Double to int conversion - truncation. Example:\n";
  cout << "int(double):\n";
  int exA_int = 15*1/10;
  int exA_dbl = 15/10.0*1;
  int exB_int = 15*(-1)/10;
  int exB_dbl = 15/10.0*(-1);
  cout << "15*1/10 = " << exA_int<<endl;
  cout << "15/10.0*1 = " << exA_dbl<<endl;
  cout << "15*(-1)/10 = " << exB_int<<endl;
  cout << "15/10.0*(-1) = " << exB_dbl<<endl;
  cout<<endl;

  cout << "int(int-double):"<<endl;
  int exC_int = 45+15*1/10;
  int exC_dbl = 45+15/10.0*1;
  int exD_int = 45+15*(-1)/10;
  int exD_dbl = 45+15/10.0*(-1);
  cout << "45+15*1/10 = " << exC_int<<endl;
  cout << "45+15/10.0*1 = " << exC_dbl<<endl;
  cout << "45+15*(-1)/10 = " << exD_int<<endl;
  cout << "45+15/10.0*(-1) = " << exD_dbl<<endl;
  cout<<endl;

  int exE_int = 17/10;
  int exE_dbl = 1.7;
  int exF_int = -17/10;
  int exF_dbl = -1.7;
  cout << "17/10 = " << exE_int<<endl;
  cout << "1.7 = " << exE_dbl<<endl;
  cout << "-17/10 = " << exF_int<<endl;
  cout << "-1.7 = " << exF_dbl<<endl;
  cout<<endl;

  int exG_int = 45+17/10;
  int exG_dbl = 45+1.7;
  int exH_int = 45+-17/10;
  int exH_dbl = 45+-1.7;
  cout << "45+17/10 = " << exG_int<<endl;
  cout << "45+1.7 = " << exG_dbl<<endl;
  cout << "45-17/10 = " << exH_int<<endl;
  cout << "45-1.7 = " << exH_dbl<<endl;
  cout<<endl;


  win.wait_for_button();
}


