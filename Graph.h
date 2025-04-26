
#ifndef GRAPH_GUARD
#define GRAPH_GUARD 1

#include "Point.h"
#include<vector>
//#include<string>
//#include<cmath>
#include "fltk.h"
#include "std_lib_facilities.h"

#include <initializer_list> // http://en.cppreference.com/w/cpp/utility/initializer_list

namespace Graph_lib {
// defense against ill-behaved Linux macros:
#undef major
#undef minor

inline pair<double,double> line_intersect(Point p1, Point p2, Point p3, Point p4, bool& parallel);

struct Color {
	enum Color_type {
		red=FL_RED, blue=FL_BLUE, green=FL_GREEN,
		yellow=FL_YELLOW, white=FL_WHITE, black=FL_BLACK,
		magenta=FL_MAGENTA, cyan=FL_CYAN, dark_red=FL_DARK_RED,
		dark_green=FL_DARK_GREEN, dark_yellow=FL_DARK_YELLOW, dark_blue=FL_DARK_BLUE,
		dark_magenta=FL_DARK_MAGENTA, dark_cyan=FL_DARK_CYAN
	};
	enum Transparency { invisible = 0, visible=255 };

	Color(Color_type cc) :c(Fl_Color(cc)), v(visible) { }
	Color(Color_type cc, Transparency vv) :c(Fl_Color(cc)), v(vv) { }
	Color(int cc) :c(Fl_Color(cc)), v(visible) { }
	Color(Transparency vv) :c(Fl_Color()), v(vv) { }
	Color(uchar r, uchar g, uchar b):c(fl_rgb_color(r,g,b)),v(visible){}  // 19 Mar 2017 added RGB support
	Color(Color colA, Color colB, float weight):c(fl_color_average(colA.c,colB.c,weight)), v(visible) {} // 26 Mar 2017 added RGB support
	//  color = color1 * weight  + color2 * (1 - weight)

	int as_int() const { return c; }
	char visibility() const { return v; }
	void set_visibility(Transparency vv) { v=vv; }
private:
	unsigned char v;	// 0 or 1 for now
	Fl_Color c;
};

struct Line_style {
	enum Line_style_type {
		solid=FL_SOLID,				// -------
		dash=FL_DASH,				// - - - -
		dot=FL_DOT,					// ....... 
		dashdot=FL_DASHDOT,			// - . - . 
		dashdotdot=FL_DASHDOTDOT,	// -..-..
	};
	Line_style(Line_style_type ss) :s(ss), w(0) { }
	Line_style(Line_style_type lst, int ww) :s(lst), w(ww) { }
	Line_style(int ss) :s(ss), w(0) { }

	int width() const { return w; }
	int style() const { return s; }
private:
	int s;
	int w;
};

class Font {
public:
	enum Font_type {
		helvetica=FL_HELVETICA,
		helvetica_bold=FL_HELVETICA_BOLD,
		helvetica_italic=FL_HELVETICA_ITALIC,
		helvetica_bold_italic=FL_HELVETICA_BOLD_ITALIC,
		courier=FL_COURIER,
  		courier_bold=FL_COURIER_BOLD,
  		courier_italic=FL_COURIER_ITALIC,
  		courier_bold_italic=FL_COURIER_BOLD_ITALIC,
		times=FL_TIMES,
		times_bold=FL_TIMES_BOLD,
		times_italic=FL_TIMES_ITALIC,
		times_bold_italic=FL_TIMES_BOLD_ITALIC,
		symbol=FL_SYMBOL,
		screen=FL_SCREEN,
		screen_bold=FL_SCREEN_BOLD,
		zapf_dingbats=FL_ZAPF_DINGBATS
	};

	Font(Font_type ff) :f(ff) { }
	Font(int ff) :f(ff) { }

	int as_int() const { return f; }
private:
	int f;
};

template<class T> class Vector_ref {
	vector<T*> v;
	vector<T*> owned;
public:
	Vector_ref() {}

	Vector_ref(T* a, T* b=0, T* c=0, T* d=0)
	{
			if (a) push_back(a);
			if (b) push_back(b);
			if (c) push_back(c);
			if (d) push_back(d);
	}

	~Vector_ref() { for (int i=0; i<owned.size(); ++i) delete owned[i]; }

	void push_back(T& s) { v.push_back(&s); }
	void push_back(T* p) { v.push_back(p); owned.push_back(p); }

	// ???void erase(???)

	T& operator[](int i) { return *v[i]; }
	const T& operator[](int i) const { return *v[i]; }
	int size() const { return v.size(); }
};

typedef double Fct(double);

class Shape  {	// deals with color and style, and holds sequence of lines
protected:
	Shape() { }
	Shape(initializer_list<Point> lst);  // add() the Points to this Shape

//	Shape() : lcolor(fl_color()),
//		ls(0),
//		fcolor(Color::invisible) { }
	
	void add(Point p){ points.push_back(p); }
	void set_point(int i, Point p) { points[i] = p; }
public:
	void draw() const;					// deal with color and draw_lines
protected:
	virtual void draw_lines() const;	// simply draw the appropriate lines
public:
	virtual void move(int dx, int dy);	// move the shape +=dx and +=dy

	virtual void set_color(Color col) { lcolor = col; } // We derive Arc from Ellipse
	//void set_color(Color col) { lcolor = col; }
	Color color() const { return lcolor; }

	void set_style(Line_style sty) { ls = sty; }
	Line_style style() const { return ls; }

  virtual void set_fill_color(Color col) { fcolor = col; } // We derive Arc from Ellipse
	//void set_fill_color(Color col) { fcolor = col; }
	Color fill_color() const { return fcolor; }

	Point point(int i) const { return points[i]; }
	int number_of_points() const { return int(points.size()); }

	virtual ~Shape() { }
	/*
	struct Window* attached;
	Shape(const Shape& a)
		:attached(a.attached), points(a.points), line_color(a.line_color), ls(a.ls)
	{loStraus$ ./ch17.9.5_list_use.exe
Trying Link class
norce_gods = Freia, Zeus, Odin, THOR
greek_gods = Poseidon,  Mars, Athena, Hera

Fixing the gods
norce_gods = Freia, Zeus, Odin, THOR
greek_gods = Poseidon,  Ares,
		if (a.attached)error("attempt to copy attached shape");
	}
	*/
	Shape(const Shape&) = delete;  // prevent copying
	Shape& operator=(const Shape&) = delete;
private:
	vector<Point> points;	// not used by all shapes
	Color lcolor {fl_color()}; // color of lines and characters (with default)
	Line_style ls {0};
	Color fcolor {Color::invisible}; // fill color

//	Shape(const Shape&);
//	Shape& operator=(const Shape&);
};

struct Function : Shape {
	// the function parameters are not stored
	Function(Fct f, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25);
	//Function(Point orig, Fct f, double r1, double r2, int count, double xscale = 1, double yscale = 1);	
};

constexpr int SHRT_MAX = 32767/2; // if using X11 (linux), int might be converted to short int. To prevent it, we need to truncate the values (if outside visible range)
inline int clip_16bit(int y) {
  // if using X11 (linux), int might be converted to short int. To prevent it, we need to truncate the values (if outside visible range)
  if (y > SHRT_MAX)
    return SHRT_MAX;
  if (y< -SHRT_MAX)
    return -SHRT_MAX;
  return y; // regular case (no truncation)
}

struct Fill {
	Fill() :no_fill(true), fcolor(0) { }
	Fill(Color c) :no_fill(false), fcolor(c) { }

	void set_fill_color(Color col) { fcolor = col; }
	Color fill_color() { return fcolor; }
protected:
	bool no_fill;
	Color fcolor;
};

struct Line : Shape {
	Line(Point p1, Point p2) { add(p1); add(p2); }
	//void set_end (Point p) {points[1] = p;}  // if we want to modify both coordinates, we can move both points first, and then use set_end.
};

struct Rectangle : Shape {

	Rectangle(Point xy, int ww, int hh) :w{ ww }, h{ hh }
	{
		if (h<=0 || w<=0) error("Bad rectangle: non-positive side");
		add(xy);
	}
	Rectangle(Point x, Point y) :w{ y.x - x.x }, h{ y.y - x.y }
	{
		if (h<=0 || w<=0) error("Bad rectangle: first point is not top left");
		add(x);
	}
	void draw_lines() const;

//	void set_fill_color(Color col) { fcolor = col; }
//	Color fill_color() { return fcolor; }

	int height() const { return h; }
	int width() const { return w; }
	void resize(int ww, int hh) {
	  w = ww;
	  h=hh;
	}
private:
	int h;			// height
	int w;			// width
//	Color fcolor;	// fill color; 0 means "no fill"
};

bool intersect(Point p1, Point p2, Point p3, Point p4);


struct Open_polyline : Shape {	// open sequence of lines
	// using Shape::Shape; // If we want to do that, need switch constructors in Shape from protected to public or
  // Need to explicitly declare constructors to make them public (they were protected in the Base class Shape which makes them protected
  Open_polyline():Shape(){} // now public
  Open_polyline(initializer_list<Point> lst) : Shape{lst} {} // now public
       // Lines(initializer_list<Point> lst) : Shape{lst} { if (lst.size() % 2) error("odd number of points for Lines"); }

	void add(Point p) { Shape::add(p); }
	void draw_lines() const;
};

struct Closed_polyline : Open_polyline {	// closed sequence of lines
	using Open_polyline::Open_polyline;

//protected:
	void draw_lines() const;
	
//	void add(Point p) { Shape::add(p); }
};

// aandree 13 Nov 2016
// we will need to explicitly declare the initializer_list constructor for Polygons.
// It is ends up being derived from Shape, and therefore mimics the Shape::Shape(initializer_list<Point> lst),
// but the add(p) function for Polygon was modified
// to include an extra checker, which is not present in the Shape::add(Point p)
struct Polygon : Closed_polyline {	// closed sequence of non-intersecting lines
	using Closed_polyline::Closed_polyline;
	//Polygon(initializer_list<Point> lst);
	void add(Point p);
	void draw_lines() const;
};

struct Lines : Shape {	// indepentdent lines
	Lines() {}
	Lines(initializer_list<Point> lst) : Shape{lst} { if (lst.size() % 2) error("odd number of points for Lines"); }
	void draw_lines() const;
	void add(Point p1, Point p2) { Shape::add(p1); Shape::add(p2); }
};

struct Text : Shape {
	// the point is the bottom left of the first letter
	Text(Point x, const string& s) : lab{ s } { add(x); }

	void draw_lines() const;

	void set_label(const string& s) { lab = s; }
	string label() const { return lab; }

	void set_font(Font f) { fnt = f; }
	Font font() const { return Font(fnt); }

	void set_font_size(int s) { fnt_sz = s; }
	int font_size() const { return fnt_sz; }
private:
	string lab;	// label
	Font fnt{ fl_font() };
	int fnt_sz{ (14<fl_size()) ? fl_size() : 14 };	// at least 14 point
};


struct Axis : Shape {
	// representation left public
	enum Orientation { x, y, z };
	Axis(Orientation d, Point xy, int length, int nummber_of_notches=0, string label = "");

	void draw_lines() const;
	void move(int dx, int dy);

	void set_color(Color c);

	Text label;
	Lines notches;
//	Orientation orin;
//	int notches;
};

struct Circle : Shape {
	Circle(Point p, int rr)	// center and radius
	:r{ rr } {
		add(Point{ p.x - r, p.y - r });
	}

	void draw_lines() const;

	Point center() const { return { point(0).x + r, point(0).y + r }; }

	void set_radius(int rr) { r=rr; }
	int radius() const { return r; }
private:
	int r;
};


struct Ellipse : Shape {
	Ellipse(Point p, int ww, int hh)	// center, min, and max distance from center
	:w{ ww }, h{ hh } {
		add(Point{ p.x - ww, p.y - hh });
	}

	void draw_lines() const;

	Point center() const { return{ point(0).x + w, point(0).y + h }; }
	Point focus1() const { return{ center().x + int(sqrt(double(w*w - h*h))), center().y }; }
	Point focus2() const { return{ center().x - int(sqrt(double(w*w - h*h))), center().y }; }
	
	void set_major(int ww) { w=ww; }
	int major() const { return w; }
	void set_minor(int hh) { h=hh; }
	int minor() const { return h; }
//private:
protected:  // so that the derived arc could access them
	int w;
	int h;
};

/*
struct Mark : Text {
	static const int dw = 4;
	static const int dh = 4;
	Mark(Point xy, char c) : Text(Point(xy.x-dw, xy.y+dh),string(1,c)) {}
};
*/

struct Marked_polyline : Open_polyline {
	Marked_polyline(const string& m) :mark(m) { }
	Marked_polyline(const string&m,initializer_list<Point> lst);
	void draw_lines() const;
private:
	string mark;
};

struct Marks : Marked_polyline {
	Marks(const string& m) :Marked_polyline(m)
	{ set_color(Color(Color::invisible)); }
	Marks(const string& m, initializer_list<Point> lst) :Marked_polyline(m,lst)
	  { set_color(Color(Color::invisible)); }
};

struct Mark : Marks {
	Mark(Point xy, char c) : Marks(string(1,c)) {Marks::add(xy); }
	void add(Point x){
	  if (number_of_points() >0)
	    error("Mark already has a point initialized. Terminating");
	  else
	    Marks::add(x);
	}
};

/*

struct Marks : Shape {
	Marks(char m) : mark(string(1,m)) { }
	void add(Point p) { Shape::add(p); }
	void draw_lines() const;
private:
	string mark;
};
*/

struct Bad_image : Fl_Image {
	Bad_image(int h, int w) : Fl_Image(h,w,0) { }
	void draw(int x,int y, int, int, int, int) { draw_empty(x,y); }
};

struct Suffix {
	enum Encoding { none, jpg, gif, bmp };
};

Suffix::Encoding get_encoding(const string& s);

struct Image : Shape {
	Image(Point xy, string s, Suffix::Encoding e = Suffix::none);
	~Image() { delete p; }
	void draw_lines() const;
	void set_mask(Point xy, int ww, int hh) { w=ww; h=hh; cx=xy.x; cy=xy.y; }
	void move(int dx,int dy) { Shape::move(dx,dy); p->draw(point(0).x,point(0).y); }
private:
	int w,h,cx,cy; // define "masking box" within image relative to position (cx,cy)
	Fl_Image* p;
	Text fn;
};

// new classes for ch 13:
struct Arc : Ellipse {
  Arc(Point p, int ww, int hh, int alpha = 0, int betta = 360) // center, min, and max distance from center, two angles
    :Ellipse{p,ww,hh},
     alpha{alpha},
     betta{betta} {}

     void draw_lines() const;
private:
  int alpha;  // angles to start drawing the arc
  int betta;  // angle to finish drawing the arc
};

struct Striped_rectangle : Rectangle {
  using Rectangle::Rectangle; // Using Rectanble's constructors
  void draw_lines() const;
};

struct Striped_closed_polyline : Closed_polyline {
  using Closed_polyline::Closed_polyline; // Using Closed Polyline's constructors
  void draw_lines() const;
  void set_step (int st) { if (st>0) step = st;}
private:
  int step{4}; // set up the step of the stripes
};

bool line_segment_intersect_horizontal_line(Point p1, Point p2, Point p3, int line_y, int& x);
// returns true, if the horizontal line y=line_y (= const) intersect the line segment between p1 and p2, or in the right point (p2)
// The points have to be checked consecutively (this way the head will be checked exactly once).
// if the function returns true, it will also return x, for the x coordinate of intersection.
// in case p2 comes as an intersection point, we need to check p3 to see if this is on the opposite side from p1

void draw_par_base_stripe_triangle (const Point& A, const Point& B, const Point& C, int stripe_gap, int stripe_disp=0);
// fill a regular triangle (B.y = C.y)

void draw_stripe_triangle(const Point& A, const Point& B, const Point& C, int stripe_gap, int stripe_disp = 0);
// fill a triangle with stripes

struct Striped_circle : Circle {
  using Circle::Circle; // Using Circle's constructors
  void draw_lines() const;
};

struct Smiley : Circle {
  Smiley(Point p, int rr) // center and radius;
  :Circle{p,rr},
   leye{p+Point{-rr/2, -rr/2}, rr/10}, // as y goes down, we need to subtract to go up y-direction
   reye{p+Point{+rr/2, -rr/2}, rr/10}, // as y goes down, we need to subtract to go up y-direction
   mouth{p, rr, rr/2, -45, -135}
   {}

  void draw_lines() const;
private:
  Circle leye;
  Circle reye;
  Arc mouth;
};

struct SmileyHat : Smiley {
  SmileyHat(Point p, int rr); // center and radius
  void draw_lines() const;
private:
  Open_polyline hat;
};

struct Frowny : Circle {
  Frowny(Point p, int rr) // center and radius;
  :Circle{p,rr},
   leye{p+Point{-rr/2, -rr/2}, rr/10}, // as y goes down, we need to subtract to go up y-direction
   reye{p+Point{+rr/2, -rr/2}, rr/10}, // as y goes down, we need to subtract to go up y-direction
   mouth{p + Point{0, rr/2}, rr, rr/2, +45, +135} // as we are doing the upper lip, we need to pull the center down
   {}

  void draw_lines() const;
private:
  Circle leye;
  Circle reye;
  Arc mouth;
};

struct FrownyHat : Frowny {
  FrownyHat(Point p, int rr); // center and radius
  void draw_lines() const;
private:
  Open_polyline hat;
};

struct Poly: Polygon {
  using Polygon::Polygon; // use Polygon's functions
  Poly(initializer_list<Point> lst);  // add() the Points to this Shape. This will check if the lines intersect
};

struct Right_triangle : Closed_polyline {
  Right_triangle(initializer_list<Point> lst)
  : Closed_polyline{lst}
  {
    // make sure we have 3 points
    if(lst.size() != 3)
      error("Right_triangle requires 3 points in the constructor");

    // verify that one angle is 90 degrees (dot product = 0)
    // we re-purpose points as vectors.
    // This required to overload operators '+', '-' and '*' in Point.h (dot product)
    // Note: the std::initializer_list does not provide subsripting []
    // https://stackoverflow.com/questions/17787394/why-doesnt-stdinitializer-list-provide-a-subscript-operator
    // Point vec1 {lst[1] - lst[0]};
    // Point vec2 {lst[2] - lst[0]};
    // Point vec3 {lst[2] - lst[1]};

    //  Point point(int i) const { return points[i]; }
    Point vec1 {point(1) - point(0)};
    Point vec2 {point(2) - point(0)};
    Point vec3 {point(2) - point(1)};
    if ( vec1*vec2 && vec1*vec3 && vec2*vec3)
      error ("Right triangle constructor: none of the angles are 90 degrees");
  }
};

struct Star:Closed_polyline {
  Star (Point centPt, int num_points, int rad_one, int rad_two, int alpha = 0);
private:
  Point center; // center of hexagon
  int number_points; // number of points
  int radius_one; // radius (used in the constructor)
  int radius_two; // radius (used in the constructor)
  int alpha;  // the angle (degrees) to the first point (in case we want to rotate),
};

struct Regular_polygon : Shape {
  Regular_polygon(Point centr, int radius, int numb_sides, int alpha = 0);

  void draw_lines() const;
  void set_fill_color (Color col){
    Shape::set_fill_color(col);
    cl_polyline.set_fill_color(col);
  }
  void set_color(Color col) {
    Shape::set_color(col);
    cl_polyline.set_color(col);
  }
private:
  Closed_polyline cl_polyline;
  Point center; // center of regular polygon
  int radius; // radius (used in the constructor)
  int alpha; // the angle (degrees) to the first point (in case we want to rotate)

};


struct Group:Shape{
  Group(){};
  void push_back(Shape& s) { shapes.push_back(s); }
  void push_back(Shape* p) { shapes.push_back(p); }

  Shape& operator[](int i) { return shapes[i]; }
  const Shape& operator[](int i) const { return shapes[i]; }
  int size() const { return shapes.size(); }

  void draw_lines() const;
private:
  Vector_ref<Shape> shapes; // container for the Shapes.
};

// Binary tree will take a Point as the start of the tree (=root), and a Point (=step) = a vector that will define one level of the tree growth
struct Binary_tree:Shape{
  Binary_tree (Point root, Point step, int node_sz, int lev=1);
  void draw_lines() const; // override virtual function from Shape
private:
  Point root;
  Point step;
  Vector_ref<Point> vertexes; // This to keep track of the vertexes (around which the nodes and edges will be build
  Group nodes;  // We can potentially redefine the shapes that represent a node
  Group edges;  // We can potentially redefine the edge (for example an error)
  int node_sz;
  int levels;
};

struct Checkers:Shape{
  Checkers (Point corner, int cell_size);
  void draw_lines() const;
  void checker_add(int x, int y, Color fill_cl); // add a checker of specified color
  void checker_remove(int x, int y); // remove a checker
private:
  Point corner;   // top left corner of the board
  int cell_size;  // the size of the square. The whole board is x8 times larger
  Group squares;  // squares
  Group checkers; // checkers
  int coord_2_ind (int x, int y); // coordinates 0..7 (we will use Ncell_x, Ncell_y in our code to check the boundaries
  static constexpr int Ncell_x {8};
  static constexpr int Ncell_y {8};
};

struct Regular_Octagon:Closed_polyline{
  Regular_Octagon(Point centPtr, int rad, int alpha=0);
  //void draw_lines() const;
private:
  Point center; // center of Octagon
  int radius; // radius (used in the constructor)
  int alpha;  // the angle (degrees) to the first point (in case we want to rotate),
};

struct Regular_hexagon : Shape {
  Regular_hexagon(Point p, int radius ,int alpha = 0);

  void draw_lines() const;
  void set_fill_color(Color col){
    Shape::set_fill_color(col);
    // Do not forget to update the fill color of the objects we added
    cl_polyline.set_fill_color(col);
  }
  void set_color(Color col){
    Shape::set_color(col);
    // Do not forget to update the fill color of the objects we added
    cl_polyline.set_color(col);
  }
private:
  Closed_polyline cl_polyline;
  Point center; // center of hexagon
  int radius; // radius (used in the constructor)
  int alpha;  // the angle (degrees) to the first point (in case we want to rotate),
};

struct Arrow : Shape {
  static constexpr int arrHight_SuggMin  = 5; // suggested min
  static constexpr int arrBase_SuggMin  = 2; // suggested min
  Arrow(Point p1, Point p2, int arrHight = 5, int arrHalfBase = 2);

  void draw_lines() const;
  void set_color(Color col);
  void set_fill_color(Color col);

private:
  // Note: we will also keep a track of two points for the line
  Closed_polyline head;
};

struct RoundedBox : Shape {
  RoundedBox(Point xy, int ww, int hh, int rr);
  RoundedBox(Point x, Point y, int rr);

  void draw_lines() const;

  void set_color(Color col);
  void set_fill_color(Color col);

  int height() const { return h; }
  int width() const { return w; }
  int radius() const { return r; }
private:
  int h;  // height
  int w;  // width
  int r;  // radius of the corner
  Vector_ref<Arc> arcs; // to store corner arcs
  Lines lns; // to store 4 lines
  void initParts(); // constructor helper: init arcs and lns
};

// the following is the class that is a Rectangle with a text label.
struct Box:Shape {
  static constexpr int text_hight = 15;  // How much space do we need for a line of text
  static constexpr int boundary = 3;   // When we draw the box, we want the height = text_hight*num_lines + 2*boundary
  static constexpr int letter_width = 9; // an estimate for a letter

  Box (Point p, int ww, int hh):rec{p, ww, hh} {add(p);}
  Box (Point p):rec{p, 1, 1} {add(p);} // this is a default constructor. Once we add the text, we would resize the Box automatically
  void draw_lines() const;

  void set_color(Color col);
  void set_fill_color(Color col);

  void move(int dx, int dy);  // move the shape +=dx and +=dy
  void add_text_line(const string& str, Font f = fl_font()); // add another line text. Resize the box

  // we only support single line for caption. If non was given, add the line. If we already had one, replace it
  void add_caption(const string& str, Font f = fl_font()); // add caption. No resizing the box

  Point nw() const;  // North West (top left) corner of the rectangle
  Point sw() const;  // South West (bottom left) corner of the rectangle
  Point ne() const;  // North East (top right) corner of the rectangle
  Point se() const;  // South East (bottom right) corner of the rectangle

  Point n() const;  // North (left) middle of the rectangle
  Point s() const;  // South (bottom) middle of the rectangle
  Point e() const;  // East (top right) middle of the rectangle
  Point w() const;  // West (bottom right) middle of the rectangle

private:
  Rectangle rec; // Body of the box
  Vector_ref<Text> caption;  // Caption (can be empty)
  Vector_ref<Text> lns; // Can contain multiple lines (or zero)
};

// Extra function introduced:
  ostream& operator << (ostream& os, const Point& p);

  // Rectangle
  Point nw(const Rectangle & r);  // North West (top left) corner of the rectangle
  Point sw(const Rectangle & r);  // South West (bottom left) corner of the rectangle
  Point ne(const Rectangle & r);  // North East (top right) corner of the rectangle
  Point se(const Rectangle & r);  // South East (bottom right) corner of the rectangle

  Point n(const Rectangle & r);  // North (left) middle of the rectangle
  Point s(const Rectangle & r);  // South (bottom) middle of the rectangle
  Point e(const Rectangle & r);  // East (top right) middle of the rectangle
  Point w(const Rectangle & r);  // West (bottom right) middle of the rectangle

  // Circle
  Point nw(const Circle & r);  // North West (top left) corner of the Circle
  Point sw(const Circle & r);  // South West (bottom left) corner of the Circle
  Point ne(const Circle & r);  // North East (top right) corner of the Circle
  Point se(const Circle & r);  // South East (bottom right) corner of the Circle

  Point n(const Circle & r);  // North (left) middle of the Circle
  Point s(const Circle & r);  // South (bottom) middle of the Circle
  Point e(const Circle & r);  // East (top right) middle of the Circle
  Point w(const Circle & r);  // West (bottom right) middle of the Circle

  // Ellipse
  Point nw(const Ellipse & r);  // North West (top left) corner of the Ellipse
  Point sw(const Ellipse & r);  // South West (bottom left) corner of the Ellipse
  Point ne(const Ellipse & r);  // North East (top right) corner of the Ellipse
  Point se(const Ellipse & r);  // South East (bottom right) corner of the Ellipse

  Point n(const Ellipse & r);  // North (left) middle of the Ellipse
  Point s(const Ellipse & r);  // South (bottom) middle of the Ellipse
  Point e(const Ellipse & r);  // East (top right) middle of the Ellipse
  Point w(const Ellipse & r);  // West (bottom right) middle of the Ellipse

  int round(double dnum); // convert double to int (default just drops the fraction part

}
#endif

