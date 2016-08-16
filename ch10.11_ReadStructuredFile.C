/* Write the code to read structured file
 *
 * Example:
 * {year 1990}
 * {year 1991 {month jun}}
 * {year 1992 {month jan (1 0 61.5)} {month feb (1 1 64) (2 2 65.2)}}
 * {year 2000
 *  {month feb (1 1 68) (2 3 66.66) (1 0 67.2)}
 *  {month dec (15 15 -9.2) (15 14 -8.8) (14 0 -2)}
 * }
 *
 * Viewing the context of a Vector:
 *   print *(your_vector._M_impl._M_start)@your_vector_size
 * Viewing an element i [0,vector_size-1] of a vector
 *   print *(your_vector._M_impl._M_start + i)
 * From http://www.math-linux.com/c/faq-c/faq-c-stl/article/how-to-print-the-elements-of-a-c-std-vector-with-gnu-debugger-gdb
 *
 * As far as this example:
 * (gdb) p (month.day._M_impl._M_start+0)
 * $24 = (Day *) 0x6050e0
 * (gdb) p *(month.day._M_impl._M_start+0)
 * $25 = {hour = {<std::vector<double, std::allocator<double> >> = std::vector of length 24, capacity 24 = {-7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777}, <No data fields>}}
 *
 * (gdb) p (month.day._M_impl._M_start+0).hour
 * (gdb) p (month.day._M_impl._M_start+5).hour
 * $18 = {<std::vector<double, std::allocator<double> >> = std::vector of length 24, capacity 24 = {-7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777}, <No data fields>}
 *
 * (gdb) p *((month.day._M_impl._M_start+5).hour._M_impl._M_start+3)
 * $21 = -7777
 *
 * (gdb) p *((month.day._M_impl._M_start+5).hour._M_impl._M_start+3)@2
 * $22 = {-7777, -7777}
 *
 *
 * Note: the debugger does not check if you go over the limits (in this case 24)
 * (gdb) p *((month.day._M_impl._M_start+5).hour._M_impl._M_start+0)@24
 * $31 = {-7777 <repeats 24 times>}
 * (gdb) p *((month.day._M_impl._M_start+5).hour._M_impl._M_start+0)@25
 * $32 = {-7777 <repeats 24 times>, 0}
 * (gdb) p *((month.day._M_impl._M_start+5).hour._M_impl._M_start+0)@26
 * $33 = {-7777 <repeats 24 times>, 0, 1.0325971998082053e-321}
 *
 * (gdb) p bugday
 * $1 = {hour = {<std::vector<double, std::allocator<double> >> = std::vector of length 2, capacity 2 = {24, -7777}, <No data fields>}}
* (gdb) p day
 * $2 = {hour = {<std::vector<double, std::allocator<double> >> = std::vector of length 24, capacity 24 = {-7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777}, <No data fields>}}
 *
 * (gdb) p month.day
 * $3 = {<std::vector<Day, std::allocator<Day> >> = std::vector of length 32, capacity 32 = {{hour = {<std::vector<double, std::allocator<double> >> = std::vector of length 24, capacity 24 = {-7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777}, <No data fields>}}, {hour = {<std::vector<double, std::allocator<double> >> = std::vector of length 24, capacity 24 = {-77
 */
// g++ -std=c++11 -g -o ch10.11_ReadStructuredFile.exe ch10.11_ReadStructuredFile.C     2>&1 | tee tmp.txt

#include "std_lib_facilities.h"


const int not_a_reading = -7777; // less then absolute zero
const int not_a_month  = -1;

struct Day{
  vector<double> hour{vector<double>(24, not_a_reading)};
};

struct Month{ // a month of temerature readings
  int month {not_a_month}; // [0:11] January is 0
  vector<Day> day{32};      // [1:31] one vector reading per date.// we waste day[0] to keep the code simple
};

struct Year{
  int year; // positive = AD
  vector<Month> month{12};
};

struct BugDay{
  vector<double> hour{24, not_a_reading};  // this will create a vector of just 2 elements
};

int main ()
{
  Day day;
  Month month;
  Year year;

  // this will create a vector of just 2 elements
  BugDay bugday;

  return 0;
}


