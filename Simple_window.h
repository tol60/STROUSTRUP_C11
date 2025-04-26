
#include "GUI.h"	// for Simple_window only (doesn't really belong in Window.h)

using namespace Graph_lib;
using Graph_lib::Point;
using Graph_lib::Button;
using Graph_lib::Address;

// Simple_window is basic scaffolding for ultra-simple interaction with graphics
// it provides one window with one "next" button for ultra-simple animation

struct Simple_window : Graph_lib::Window {
	Simple_window(Point xy, int w, int h, const string& title );
	Simple_window(int w, int h, const string& title ); /* aandree 28 Jul 2018 */

	bool wait_for_button();
  /* aandree -- 7 Nov 2016
	void wait_for_button()
	// modified event loop
	// handle all events (as per default), but quit when button_pushed becomes true
	// this allows graphics without control inversion
	{
		while (!button_pushed) Fl::wait();
		button_pushed = false;
		Fl::redraw();
	}
  */
	Button next_button;
private:
	bool button_pushed;
	
	static void cb_next(Address, Address addr); // callback for next_button
  /* aandree -- 7 Nov 2016
	//	{ reference_to<Simple_window>(addr).next(); }
	{
		static_cast<Simple_window*>(addr)->next();
	}
	*/

	void next(); /* aandree -- 7 Nov 2016 { button_pushed = true; } */

};
