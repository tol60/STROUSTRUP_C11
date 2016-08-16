// Illustrage how to catch range errors
// g++ -std=c++11 -g -o ch5.6.2_range_errors.exe ch5.6.2_range_errors.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

int main ()
{
  try{
    vector <int> v; // a vector of ints
    cout << "Please enter a couple integers\n";
    for (int x; cin >> x;)
       v.push_back(x);  // set values
    for (int i=0;i<=v.size();++i ) // will generate out_of_range error on the last iteration
      cout << "v["<<i<<"]==" << v[i] << endl;
  } catch (out_of_range) {
    cout <<"Oops! Range error\n";
    return 1;
  } catch (...) {
    cerr << "Exception: something went wrong\n"; // catch all other exceptions
    return 2;
  }

  return 0;
}


