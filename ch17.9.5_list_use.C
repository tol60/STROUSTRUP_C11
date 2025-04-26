// g++ -w -Wall -std=c++11 ch17.10.this_pointer.C -o ch17.10.this_pointer.exe 2>&1 | tee tmp.txt
// add insertion operator


#include <iostream>

using namespace std;

struct Link{
  string value;
  Link* prev;
  Link* succ;
  //Link () = delete; // prevent default constructor
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

void print_all(Link* p)
{
  cout <<'{';
  while (p) {
    cout << p->value;
    if (p=p->succ) cout <<','; // assignment in condition on purpose
  }
  cout << '}';
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
Link* insert(Link* p, Link* n) // insert n before p (incomplete), return n
{
  if (n==nullptr) return p;
  if (p==nullptr) return n;
  n->succ = p;        // p comes after n
  if (p->prev) p->prev->succ = n;  // n comes after what used to be p's predecessor
  n->prev = p->prev;  // p's predecessor becomes n's predecessor
  p->prev = n;        // n becomes p's predecessor
  return n;
}

Link* add(Link* p, Link* n) // insert n after p, return n
{
  if (n==nullptr) return p;
  if (p==nullptr) return n;
  if (p->succ) p->succ->prev = n;  // n comes before what used to be p's successor
  n->prev = p;        // p comes before n
  n->succ = p->succ;  //  p's cuccessor becomes n's successor
  p->succ = n;        // n becomes p's successor
  return n;
}

Link* erace(Link* p) // remove *p from list; return p's successor
{
  if (p==nullptr) return nullptr;
  if(p->succ) p->succ->prev = p->prev;
  if(p->prev) p->prev->succ = p->succ;
  return p->succ;
}

// v01:
/*
Link* find(Link* p, const string& s) // find s in list; return nullptr for "not found"
{
  while (p!=nullptr && p->value !=s) p=p->succ;
  return p;
}
*/

// v02:
Link* find(Link* p, const string& s) // find s in list; return nullptr for "not found"
{
  while (p) {
    if (p->value == s) return p;
    p = p->succ;
  }
  return nullptr;
}

// v01:
/*
Link* advance(Link* p, int n) // move n positions in list; return nullptr for "not found"
    // positive n moves forward, negative backward
{
  if (n>0){
    while (p!=nullptr && n>0){
      p=p->succ;
      n--;
    }
  } else if (n<0) {
    while (p!=nullptr && n<0) {
      p=p->prev;
      n++;
    }
  }
  return p;
}
*/

// v02:
Link* advance(Link* p, int n) // move n positions in list; return nullptr for "not found"
    // positive n moves forward, negative backward
{
  if (p==nullptr) return nullptr;
  if (n>0) {
    while (n--) {
      if (p->succ == nullptr) return nullptr;
      p=p->succ;
    }
  } else if (n<0) {
    while (n++) {
      if (p->prev == nullptr) return nullptr;
      p=p->prev;
    }
  }
  return p;
}

int main()
{
  cout << "Trying Link class" << endl;
  /* v01:
  Link* norse_gods = new Link{"Thor", nullptr, nullptr}; // value, prev, succ
  norse_gods = new Link{"Odin", nullptr, norse_gods};
  norse_gods->succ->prev = norse_gods;
  norse_gods = new Link{"Freia", nullptr,norse_gods};
  norse_gods->succ->prev = norse_gods;
  */

  // v02:
  Link* norse_gods = new Link{"THOR"};
  norse_gods = insert(norse_gods,new Link{"Odin"});
  norse_gods = insert(norse_gods,new Link{"Zeus"}); // this is actually a greek_god
  norse_gods = insert(norse_gods,new Link{"Freia"});
  cout << "norce_gods = " << *norse_gods << endl;

  Link* greek_gods = new Link{"Hera"};
  greek_gods = insert (greek_gods,new Link{"Athena"});
  greek_gods = insert (greek_gods,new Link{"Mars"});
  greek_gods = insert (greek_gods,new Link{"Poseidon"});
  cout << "greek_gods = " << *greek_gods << endl;


  // Modification experiments
  Link* p = find(greek_gods, "Mars");
  if (p) p->value = "Ares";
  cout << endl << "Fixing the gods"<<endl;
  cout << "norce_gods = " << *norse_gods << endl;
  cout << "greek_gods = " << *greek_gods << endl;

  p = find(norse_gods, "Zeus");
  if (p) {
    if (p==norse_gods) norse_gods = p->succ;
    erace(p);
    //greek_gods = insert(greek_gods,p);
    add(greek_gods,p);
  }

  cout << endl << "Fixing the gods one more time"<<endl;
  cout << "norce_gods = " << *norse_gods << endl;
  cout << "greek_gods = " << *greek_gods << endl;

  cout << endl << "Checking print_all" << endl;
  print_all(norse_gods);
  cout << endl;
  print_all(greek_gods);
  cout << endl;
}
