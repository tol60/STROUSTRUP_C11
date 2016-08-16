// Illustrate how to handle errors errors
// g++ -std=c++11 -g -o ch5.6.1_bad_arguments.exe ch5.6.1_bad_arguments.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

class Bad_area{}; // a type specifically for reporting errors from area()

// calculate area of a rectangle;
// return -1 to indicate bad argument
int area (int length, int width) {
  if (length<=0 || width<=0) throw Bad_area{};
  return length * width;
}

constexpr int frame_width = 2;
int framed_area (int x, int y) { //calculate area with frame
  return area(x-frame_width, y-frame_width);
}

int main ()
{
  try{
    //int x = -1;
    int x = 1;
    int y = 2;
    int z = 4;
    int area1 = area(x,y);
    cout << "area1 = " << area1 << endl;
    if (area1<=0) error ("non-positive area");

    int area2 = framed_area(1,z);
    cout << "area2 = " << area2 << endl;
    if (area2<=0) error ("non-positive area");

    int area3 = framed_area(y,z);
    cout << "area3 = " << area3 << endl;
    if (area3<=0) error ("non-positive area");

    double ratio = double (area1) / area3;

  }
  catch (Bad_area) {
    cout <<"Oops! Bad arguments to area()\n";
  }
  return 0;
}


