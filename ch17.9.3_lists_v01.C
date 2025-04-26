// g++ -w -Wall -std=c++11 ch17.9.3_lists_v01.C -o ch17.9.3_lists_v01.exe 2>&1 | tee tmp.txt

#include <iostream>

using namespace std;

struct Link{
  string value;
  Link* prev;
  Link* succ;
  Link (const string& v, Link* p = nullptr, Link* s = nullptr)
    :value{v},prev{p},succ{s} {}
};

ostream& operator << (ostream& os, const Link& ln)
{
  os << ln.value;
  if (ln.succ){
    os << ",\t" << *ln.succ;
  }
  return os;
}

int main()
{
  cout << "Trying Link class" << endl;
  Link* norce_gods = new Link{"Thor", nullptr, nullptr}; // value, prev, succ
  norce_gods = new Link{"Odin", nullptr, norce_gods};
  norce_gods->succ->prev = norce_gods;
  norce_gods = new Link{"Freia", nullptr,norce_gods};
  norce_gods->succ->prev = norce_gods;
  cout << *norce_gods << endl;
}
