/* http://fltk.org/doc-2.0/html/index.html
 * http://fltk.org/doc-1.3/
 * Example 1: Basic FLTK Program
 * Compile:
 *   c++ -I/usr/local/include ...
 * Link:
 *   c++ ... -L/usr/local/lib -lfltk2 -lXext -lXinerama -lXft -lX11 -lXi -lm
 *
 * Try:
    c++ -I/usr/local/include \
        -L/usr/local/lib -lfltk2 -lXext -lXinerama -lXft -lX11 -lXi -lm \
         tut_fltk_HalloWorld.C -o tut_fltk_HalloWorld.exe 2>&1 | tee tmp.txt
    c++ tut_fltk_HalloWorld.C \
          `fltk-config --ldflags --use-images` -o tut_fltk_HalloWorld.exe 2>&1 | tee tmp.txt


    g++ -w -Wall -std=c++11 `fltk-config --ldflags --use-images` \
         tut_fltk_HalloWorld.C -o tut_fltk_HalloWorld.exe 2>&1 | tee tmp.txt

    g++ -w -Wall -std=c++11 tut_fltk_HalloWorld.C \
          `fltk-config --ldflags --use-images` -o tut_fltk_HalloWorld.exe 2>&1 | tee tmp.txt

   Question:
   If we use window->end(), why don't we need window->begin() any more?
    *
 */

/*
#include <fltk/Window.h>
#include <fltk/Widget.h>
#include <fltk/run.h>
*/

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

//using namespace fltk;


int main(int argc, char **argv) {
  //Fl_Window *window = new Fl_Window(300, 180);
  //window->begin();
  //Widget *box = new Widget(20, 40, 260, 100, "Hello, World!");


  Fl_Window *window = new Fl_Window(340,180);
  // window->begin(); // If we use window->end(), why don't we need window->begin() any more?
  Fl_Box *box = new Fl_Box(20,40,300,100,"Hello, World!");

  //box->box(FL_UP_BOX);
  box->box(FL_DOWN_BOX);
  box->labelfont(FL_HELVETICA + FL_BOLD + FL_ITALIC);
  box->labelsize(36);
  box->labeltype(FL_SHADOW_LABEL);

  window->end();
  window->show(argc, argv);
  return Fl::run();
}
