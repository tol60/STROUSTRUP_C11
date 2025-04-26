//
/* Testing FLTK installation
 * http://www.fltk.org
 * The lib is located:
 *   /usr/local/include/
 *   /usr/local/lib/
 *
 */
// Did not work. g++ -std=c++11 -g fltk_test.C  -o fltk_test.exe 2>&1 | tee tmp.txt
// g++ fltk_test.C  -o fltk_test.exe `fltk-config --cxxflags --ldflags` 2>&1 | tee tmp.txt
/* $ fltk-config --cxxflags --ldflags
-I/usr/local/include -I/usr/local/include/FL/images -I/usr/include/freetype2 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT
-L/usr/local/lib -lfltk -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11


Let's try removing -lX11
 g++ fltk_test.C  -o fltk_test.exe -I/usr/local/include -I/usr/local/include/FL/images -I/usr/include/freetype2 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT -L/usr/local/lib -lfltk -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm 2>&1 | tee tmp.txt
Got an error:
/usr/bin/ld: /usr/local/lib/libfltk.a(Fl_x.o): undefined reference to symbol 'XConvertSelection'
//usr/lib/x86_64-linux-gnu/libX11.so.6: error adding symbols: DSO missing from command line
collect2: error: ld returned 1 exit status
tony@tony-ThinkPad-W520:~/workspace/STROUSTRUP_PRC++/HelloStraus$

Worked (6 Nov 2016):
fltk-config --compile fltk_test.C
g++ -I/usr/local/include -I/usr/local/include/FL/images -I/usr/include/freetype2 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT -o 'fltk_test' 'fltk_test.C' /usr/local/lib/libfltk.a -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11

// trying to slice it:
g++ -I/usr/local/include -I/usr/local/include/FL/images -I/usr/include/freetype2 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT \
       -o 'fltk_test' 'fltk_test.C' \
        /usr/local/lib/libfltk.a -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11

Or better way:

g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp MY_CPP_FILE.cpp `fltk-config --ldflags --use-images` -o MY_EXECUTABLE
g++ -w -Wall -std=c++11 fltk_test.C \
           `fltk-config --ldflags --use-images` -o fltk_test.exe 2>&1 | tee tmp.txt

*/

//#include "std_lib_facilities.h"

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>

int main ()
{
  Fl_Window window(200,200, "Window title");
  Fl_Box box (0,0,200,200, "Hey, I mean, Hello, World!");
  window.show();
  return Fl::run();
}


