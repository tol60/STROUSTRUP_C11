/*
 * Month.C
 *
   g++ -std=c++11 -g -o Month.exe Month.C  2>&1 | tee tmp.txt
 */

//#include "std_lib_facilities.h"
#include<iostream>
#include<vector>

using namespace std;

namespace Chrono {
enum class Month {
  jan=1,feb,mar,apr,may,jun,jul,aug,sep,oct,nov,dec
};

vector <string> month_tbl{"jan","feb","mar","apr","may","jun","jul","aug","sep","oct","nov","dec"};
ostream& operator <<(ostream& os, const Month& m){
  return os << month_tbl[int(m)];
  //return os << int(m);
}

} // Chrono

int main()
{
  // Chrono::Month mm {Chrono::Month::feb};
  using Chrono::Month;
  Month mm {Month::feb};
  cout << "mm = "<< mm << endl;
}


