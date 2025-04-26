// g++ -g -w -Wall -std=c++11 ch18.d.1_std_Vector_drill.C -o ch18.d.1_std_Vector_drill.exe 2>&1 | tee tmp.txt
/* Standard library vector drill
 * 1. Define a global vector<int> gv; initialize it with ten ints, 1,2,4,8, 16, etc.
 * 2. Define a function f() taking a vector<int> argument
 * 3. In f():
 *    a. Define a local vector<int> lv with the same number of elements as the argument vector
 *    b. Copy the values from gv into lv
 *    c. print out the elements of lv
 *    d. Define a local vector<int> lv2; initialize it to be a copy of the argument vector
 *    e. Print the elements of lv2
 *  4. In main():
 *    a. Call f() with gv as its argument
 *    b. Define a vector<int> vv, , and initialize it with the first ten
 *       factorial values (1, 2*1, 3*2*1,4*3*2*1, etc.).
 *    c. Call f() with vv as its argument
 */

#include <iostream>
#include <vector>

using namespace std;

vector<int> gv = {1,2,4,8,16,32,64,128,256,512};

void f(const vector<int>& v)
{
  //a. Define a local vector<int> lv with the same number of elements as the argument vector
  vector<int> lv(v.size());

  // b. Copy the values from gv into lv
  for (int i=0; i<v.size(); ++i) {
    lv[i] = gv[i];
  }

  // c. print out the elements of lv
  for (int i=0; i<lv.size(); ++i )
    cout << "lv["<<i<<"] = "<< lv[i] << endl;

  // d. Define a local vector<int> lv2; initialize it to be a copy of the argument vector
  vector<int> lv2{v};

  // e. Print the elements of lv2
  for (int i=0; i<lv2.size(); ++i)
    cout << "lv2["<<i<<"] = "<< lv2[i] << endl;


}

int main()
{
  cout << "*************************************\n";
  cout << "Inside main function \n";
  cout << "*************************************\n";

  //  a. Call f() with gv as its argument
  f(gv);

  // b. Define a vector<int> vv, initialize it with the first ten
  //       factorial values (1, 2*1, 3*2*1,4*3*2*1, etc.).
  vector<int>vv(10);
  for (int i=0; i<10; ++i) {
    fac *= i+1;
    vv[i] = fac;
  }

  // c. Call f() with vv as its argument
  f(vv);

  cout << "*************************************\n";
  cout << "main() function is done\n";
  cout << "*************************************\n";
}
