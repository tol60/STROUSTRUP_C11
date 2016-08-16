// Try to fix the problem
// g++ -std=c++11 -g -o ch5.d_scaffolding.exe ch5.d_scaffolding.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

int main ()
{
  try {
    //<< your code here >>
    //int res = 7; vector <int> v(10); v[5] = res; cout<< "Success!\n"; //5.
    // vector<int> v(10); v[5]=7; if (v[5]==7) cout << "Success!\n"; // 6
    // bool cond = true; if (cond) cout << "Success!\n"; else cout << "Fail!\n";
    // bool c = false; if(!c) cout <<"Success!\n"; else cout << "Fail!\n"; // 8
    // string s = "ape"; bool c = "fool"<s; if(!c) cout << "Success!\n"; // 9.
    // string s = "ape"; if (s!="fool") cout <<"Success!\n";  // 10
    // string s = "ape"; if (s!="fool") cout <"Success!\n"; // would not print it, but compiles!!!
    // string s = "ape"; string f = "fool"; if (s+"fool"!=" ") cout <<"Success!\n"; //12
    // vector <char> v(5); for (int i=0; i<v.size(); ++i) ; cout << "Sucess!\n"; // 13
    // vector <char> v(5); for (int i=0; i<=v.size(); ++i) cout << i << endl; cout << "Sucess!\n"; //14
    // string s = "Success!\n";for(int i=0; i<9; ++i) cout << s[i]; // 15
    // if (true) cout << "Success!\n"; else cout << "Fail!\n"; // 16
    // int x=2000; char c=x; if (c==-48) cout << "Success!\n"; //17
    // string s = "Success!\n";for(int i=0; i<9; ++i) cout << s[i]; // 18
    // vector <int> v(5); for (int i=0; i<=v.size();++i); cout << "Success!\n"; //19
    // int i=0; int j=9; while (i<10) ++i; if (j<i) cout << "Success!\n";  // 20
    // int x=-2; double d = 5/(x-2); if (d!=2*x+0.5) cout << "Success!\n"; // 21
    // string s = "Success!\n"; for (int i=0;i<9;++i) cout << s[i]; // 22
    // int i=0; int j=0; while (i<10)++i; if (j<i) cout <<"Success!\n"; // 23
    // int x = 4; double d = 5/(x-2); if(d!=2*x+0.5) cout << "Success!\n"; // 24
    cout <<"Success!\n";
    return 0;
  }
  catch (exception& e) {
    cerr << "error:"<< e.what()<<endl;
    return 1;
  }
  catch (...){
    cerr << "Oops: unknown exception!\n";
    return 2;
  }
  //return 0;
}


