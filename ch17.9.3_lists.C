// g++ -w -Wall -std=c++11 ch17.9.3_lists.C -o ch17.9.3_lists.exe 2>&1 | tee tmp.txt
// add insertion operator


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

/*
Link* insert(Link* p, Link* n) // insert n before p (incomplete)
{
  n->succ = p;        // p comes after n
  p->prev->succ = n;  // n comes after what used to be p's predecessor
  n->prev = p->prev;  // p's predecessor becomes n's predecessor
  p->prev = n;        // n becomes p's predecessor
}
*/
Link* insert(Link* p, Link* n) // insert n before p (incomplete)
{
  if (n==nullptr) return p;
  if (p==nullptr) return n;
  n->succ = p;        // p comes after n
  if (p->prev) p->prev->succ = n;  // n comes after what used to be p's predecessor
  n->prev = p->prev;  // p's predecessor becomes n's predecessor
  p->prev = n;        // n becomes p's predecessor
  return n;
}


int main()
{
  cout << "Trying Link class" << endl;
  /* v01:
  Link* norce_gods = new Link{"Thor", nullptr, nullptr}; // value, prev, succ
  norce_gods = new Link{"Odin", nullptr, norce_gods};
  norce_gods->succ->prev = norce_gods;
  norce_gods = new Link{"Freia", nullptr,norce_gods};
  norce_gods->succ->prev = norce_gods;
  */

  // v02:
  Link* norce_gods = new Link{"THOR"};
  norce_gods = insert(norce_gods,new Link{"Odin"});
  norce_gods = insert(norce_gods,new Link{"Rreia"});
  cout << *norce_gods << endl;
}
