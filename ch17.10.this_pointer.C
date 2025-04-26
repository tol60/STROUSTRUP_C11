// g++ -w -Wall -std=c++11 ch17.10.this_pointer.C -o ch17.10.this_pointer.exe 2>&1 | tee tmp.txt
// add insertion operator


#include <iostream>

using namespace std;

class Link{
public:
  string value;

  //Link () = delete; // prevent default constructor
  Link (const string& v, Link* p = nullptr, Link* s = nullptr)
    :value{v},prev{p},succ{s} {}
  Link* insert(Link* n);  // insert n before this object
  Link* add(Link* n);     // insert n after this object
  Link* erase();          // remove this object from list
  Link* find(const string& s);  // find s in  list
  const Link* find(const string& s) const; // find in const list

  Link* advance(int n) const; // move n positions in list

  Link* next() const {return succ;}
  Link* previous() const {return prev;}
private:
  Link* prev;
  Link* succ;
};

ostream& operator << (ostream& os, const Link& ln)
{
  os << ln.value;
  if (ln.next()){
    os << ",\t" << *ln.next();
  }
  return os;
}

void print_all(const Link* p)
{
  cout <<'{';
  while (p) {
    cout << p->value;
    p=p->next();
    if (p) cout <<','; // assignment in condition on purpose
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
Link* Link::insert(Link* n) // insert n before p (incomplete), return n
{
  Link* p = this;           // pointer to this object
  if (n==nullptr) return p; // nothing to insert
  if (p==nullptr) return n; // nothing to insert into
  n->succ = p;              // p comes after n
  if (p->prev) p->prev->succ = n;  // n comes after what used to be p's predecessor
  n->prev = p->prev;        // p's predecessor becomes n's predecessor
  p->prev = n;              // n becomes p's predecessor
  return n;
}

Link* Link::add(Link* n) // insert n after p, return n
{
  Link* p = this;
  if (n==nullptr) return p;
  if (p==nullptr) return n;
  if (p->succ) p->succ->prev = n;  // n comes before what used to be p's successor
  n->prev = p;        // p comes before n
  n->succ = p->succ;  //  p's cuccessor becomes n's successor
  p->succ = n;        // n becomes p's successor
  return n;
}

Link* Link::erase() // remove *p from list; return p's successor
{
  Link* p = this;
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
Link* Link::find(const string& s) // find s in list; return nullptr for "not found"
{
  Link* p = this;
  while (p) {
    if (p->value == s) return p;
    p = p->succ;
  }
  return nullptr;
}

const Link* Link::find(const string& s) const // find s in list; return nullptr for "not found"
{
  const Link* p = this;
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
Link* Link::advance(int n) const// move n positions in list; return nullptr for "not found"
    // positive n moves forward, negative backward
{
  Link* p = (Link*)this;
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
  norse_gods = norse_gods->insert(new Link{"Odin"});
  norse_gods = norse_gods->insert(new Link{"Zeus"}); // this is actually a greek_god
  norse_gods = norse_gods->insert(new Link{"Freia"});
  cout << "norce_gods = ";
  print_all(norse_gods);
  cout << endl;

  Link* greek_gods = new Link{"Hera"};
  greek_gods = greek_gods->insert (new Link{"Athena"});
  greek_gods = greek_gods->insert (new Link{"Mars"});
  greek_gods = greek_gods->insert (new Link{"Poseidon"});
  cout << "greek_gods = ";
  print_all(greek_gods);
  cout << endl;


  // Question: Why did we need two declarations of find?
  // const Link* p_test = greek_gods->find("Mars")->advance(1);
  const Link* p_const = greek_gods;
  const Link* p_test = p_const->find("Mars");
  cout << endl << "Checking const verstion of find. Did we find Mars?" << endl;
  // print_all((Link*)p_test);
  cout << *p_test << endl;

  // Modification experiments
  Link* p = greek_gods->find("Mars");
  if (p) p->value = "Ares";
  cout << endl << "Fixing the gods"<<endl;
  cout << "norce_gods = ";
  print_all(norse_gods);
  cout << endl;
  cout << "greek_gods = ";
  print_all(greek_gods);
  cout << endl;

  p = norse_gods->find("Zeus");
  if (p) {
    if (p==norse_gods) norse_gods = p->next();
    p->erase();
    greek_gods = greek_gods->insert(p);
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
