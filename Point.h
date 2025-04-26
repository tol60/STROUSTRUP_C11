
#ifndef POINT_GUARD
#define POINT_GUARD

// #include "std_lib_facilities.h"  // this is only for cout experiments

//typedef void (*Callback)(void*,void*);

namespace Graph_lib {

struct Point {
	int x,y;
	constexpr Point(int xx, int yy) : x(xx), y(yy) { }  // to be able to use Points in constexpr // aandree 11 Nov 2016
	// Point(int xx, int yy) : x(xx), y(yy) { }
	constexpr Point() :x(0), y(0) { }

	Point& operator+=(Point d) { x+=d.x; y+=d.y; return *this; }

};

inline bool operator==(Point a, Point b) { return a.x==b.x && a.y==b.y; }

inline bool operator!=(Point a, Point b) { return !(a==b); }

// aandree Added while doing chapter 13 exercisers
// Note: if we were to define two version of the same operator:
// inline Point operator +(const Point& pA, const Point& pB) {std::cout << "+ version 1 (passing by const ref)\n"; return Point{pA.x+pB.x, pA.y+pB.y};}
// inline Point operator +(Point pA, Point pB) {std::cout << "+ version 2 (passing by value)\n"; return Point{pA.x+pB.x, pA.y+pB.y};}
// we would get the following error:
// error: ambiguous overload for ‘operator+’ (operand types are ‘Graph_lib::Point’ and ‘Graph_lib::Point’)

inline Point operator + (const Point& pA, const Point& pB) {return Point{pA.x+pB.x, pA.y+pB.y};} // pSum  = pA + pB
inline Point operator - (const Point& pA, const Point& pB) {return Point{pA.x-pB.x, pA.y-pB.y};} // pDiff = pA - pB
inline   int operator * (const Point& pA, const Point& pB) {return pA.x * pB.x + pA.y*pB.y;}     // pA*pB = x1*x2+y1*y2 = (dot product)

}
#endif
