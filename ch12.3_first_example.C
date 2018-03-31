//
/* Ch12.3 first Example (using the GUI)
 *
 * http://www.fltk.org
 * The lib is located:
 *   /usr/local/include/
 *   /usr/local/lib/
 *
 */
// g++ -std=c++11 GUI.cpp Window.cpp Simple_window.cpp Graph.cpp ch12.3_first_example.C  -o ch12.3_first_example.exe `fltk-config --cxxflags --ldflags` 2>&1 | tee tmp.txt
/* $ fltk-config --cxxflags --ldflags
-I/usr/local/include -I/usr/local/include/FL/images -I/usr/include/freetype2 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT
-L/usr/local/lib -lfltk -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11

// trying to slice it:
g++ -std=c++11 -I/usr/local/include -I/usr/local/include/FL/images -I/usr/include/freetype2 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT \
       -o 'ch12.3_first_example.exe' Simple_window.cpp Graph.cpp ch12.3_first_example.C  \
        /usr/local/lib/libfltk.a -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11 \
        2>&1 | tee tmp.txt
Gives errors!!

g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch12.3_first_example.C \
-I/usr/local/include -I/usr/local/include/FL/images -I/usr/include/freetype2 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT \
        /usr/local/lib/libfltk.a -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11 \
        -o 'ch12.3_first_example.exe' 2>&1 | tee tmp.txt
Error:
/tmp/ccCFoz5M.o: In function `Graph_lib::Image::Image(Graph_lib::Point, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, Graph_lib::Suffix::Encoding)':
Graph.cpp:(.text+0x222d): undefined reference to `Fl_JPEG_Image::Fl_JPEG_Image(char const*)'
Graph.cpp:(.text+0x2267): undefined reference to `Fl_GIF_Image::Fl_GIF_Image(char const*)'
collect2: error: ld returned 1 exit status


https://groups.google.com/forum/#!topic/ppp-public/BtlzdWGuQpQ
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE

The following steps were needed to compile under Linux:
5. Graph.h line 10: Uncomment #include "std_lib_facilities.h"


g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE
g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch12.3_first_example.C \
           `fltk-config --ldflags --use-images` -o ch12.3_first_example.exe 2>&1 | tee tmp.txt

Note:
fltk-config --ldflags --use-images
-L/usr/local/lib -lfltk_images -lpng -lz -lfltk_jpeg -lfltk -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11

g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp ch12.3_first_example.C \
           -L/usr/local/lib -lfltk_images -lpng -lz -lfltk_jpeg -lfltk -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11 \
           -o ch12.3_first_example.exe 2>&1 | tee tmp.txt
Worked as well!

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

  Point  tl {100,100};    // to become top left corner 0f window

  Simple_window win {tl, 600, 400,"Canvas"};  // make a simple window, {top_left, width, hight, title}
  //Graph_lib::Window{tl, 600, 400,"Canvas"};

  Polygon poly; // make a shape (a polygon)

  poly.add(Point{300,200}); // add a point
  poly.add(Point{350,100}); // add another point
  poly.add(Point{400,200}); // add a third point

  poly.set_color(Color::red); // adjust properties of poly

  win.attach(poly); // connect poly to the window

  win.wait_for_button();  // gvie control to the display engine

}


