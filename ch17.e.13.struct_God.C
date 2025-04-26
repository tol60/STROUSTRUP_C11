// g++ -w -Wall -std=c++11 ch17.e.13.struct_God.C -o ch17.e.13.struct_God.exe 2>&1 | tee tmp.txt
// add insertion operator


#include <iostream>

using namespace std;

struct God {
    string name;
    string mythology;
    string vehecle;
    string weapon;
    God(const string& nam, const string& myth="",const string& veh="", const string& weap="")
      :name{nam},mythology{myth},vehecle{veh},weapon{weap} {}
  };

ostream& operator << (ostream& os, const God& g){
  return os << g.name <<", " << g.mythology << ", " << g.vehecle << ", " << g.weapon;
}

class Link{
public:
  //string value;
  God gd;

  //Link () = delete; // prevent default constructor
  Link (const God& v, Link* p = nullptr, Link* s = nullptr)
    :gd{v},prev{p},succ{s} {}
  Link (const string&v, Link* p = nullptr, Link* s = nullptr )
    :Link(God{v}, p, s){}


  Link* insert(Link* n);  // insert n before this object
  Link* add(Link* n);     // insert n after this object
  Link* add_ordered(Link* n); // insert n in the correct lexicographical position
  Link* erase();          // remove this object from list
  void  clear_ptrs(){prev=nullptr; succ=nullptr;} // in case we want to move a Link element from one list to another
                                // we might consider cleaning the ptrs before inserting a Link element into the new list
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
  os << ln.gd;
  if (ln.next()){
    os << "\t|\t" << *ln.next();
  }
  return os;
}

void print_all(const Link* p)
{
  cout<< '{' << endl;
  while (p) {
    cout << p->gd << endl;
    p=p->next();
  }
  cout << '}' << endl;
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
Link* Link::insert(Link* n) // insert n before p, return n
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

Link* Link::add(Link* n) // insert n after p, return p
{
  Link* p = this;
  if (n==nullptr) return p;
  if (p==nullptr) return n;
  if (p->succ) p->succ->prev = n;  // n comes before what used to be p's successor
  n->prev = p;        // p comes before n
  n->succ = p->succ;  //  p's cuccessor becomes n's successor
  p->succ = n;        // n becomes p's successor
  return p;
}

Link* Link::add_ordered(Link* n) // insert n in the correct lexicographical position
{
  Link* p = this;
  if (n==nullptr) return p;
  if (p==nullptr) return n;

  // at this point we now that n and p are not nullptrs
  string nm = n->gd.name;  // we will use this to compare lexicographical order
  if (p->gd.name >= nm) // if lexicographically the new element should go before this one
        return insert(n);  // return pointer to new element
  // otherwise we need to return this

  while (p) {
    if (p->gd.name >= nm) // if lexicographically the new element should go before this one
    {
      p->insert(n); // important: as we advance in the loop, can not use this pointer here (need to use p->)
      return this;
    }
    else if (p->succ == nullptr) // if the end of the line, nothing else left but to add the element after
    {
      p->add(n); // important: as we advance in the loop, can not use this pointer here (need to use p->)
      return this;
    }
    else
      p=p->succ;  // else traverse the linked list
  }
  cerr << "Link::add_ordered should have never gotten here. Terminating"<< endl;
  exit(1);
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
    if (p->gd.name == s) return p;
    p = p->succ;
  }
  return nullptr;
}

const Link* Link::find(const string& s) const // find s in list; return nullptr for "not found"
{
  const Link* p = this;
  while (p) {
    if (p->gd.name == s) return p;
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
  Link* norse_gods = new Link{ God{"THOR","Norse"} };
  norse_gods = norse_gods->insert(new Link{ God{"Odin","Norse","Eight-legged flying horse called Sleipner","Spear called Gungnir"} });
  norse_gods = norse_gods->insert(new Link{ God{"Zeus","Greek","","lightning"} }); // this is actually a greek_god
  norse_gods = norse_gods->insert(new Link{ God{"Freia","Norse"} });
  cout << "norce_gods = ";
  print_all(norse_gods);
  cout << endl;

  Link* greek_gods = new Link{ God{"Hera", "Greek"} };
  greek_gods = greek_gods->insert (new Link{ God{"Athena","Greek"} });
  greek_gods = greek_gods->insert (new Link{ God{"Mars","Roman"} });
  greek_gods = greek_gods->insert (new Link{ God{"Poseidon","Greek"} });
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
  if (p) p->gd = God{"Ares","Greek"};
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

  cout << endl;
  cout << "******************************************************" << endl;
  cout << "Creating a mixed list of Gods, then splitting it 3 way alphabetically" << endl;
  cout << "******************************************************" << endl;

  Link* list_gods = new Link{ God{"THOR","Norse"} };
  list_gods = list_gods->insert(new Link{ God{"Odin","Norse","Eight-legged flying horse called Sleipner","Spear called Gungnir"} });
  list_gods = list_gods->insert(new Link{ God{"Zeus","Greek","","lightning"} }); // this is actually a greek_god
  list_gods = list_gods->insert(new Link{ God{"Freia","Norse"} });
  list_gods = list_gods->insert(new Link{ God{"Hera", "Greek","", "Goddes of Olympus"} });
  list_gods = list_gods->insert (new Link{ God{"Athena","Greek"} });
  list_gods = list_gods->insert (new Link{ God{"Mars","Roman","","God of war"} });
  list_gods = list_gods->insert (new Link{ God{"Poseidon","Greek"} });

  list_gods = list_gods->insert (new Link{ God{"Venus","Roman", "","God of love"} });
  list_gods = list_gods->insert (new Link{ God{"Jupiter","Roman","","Supreme"} });
  list_gods = list_gods->insert (new Link{ God{"Neptune","Roman","","God of water"} });


  Link* pt = list_gods;
  Link* list_gods_Greek = nullptr;
  Link* list_gods_Norse = nullptr;
  Link* list_gods_Roman = nullptr;

  cout << "list_gods:"<< list_gods<< endl;
  print_all(list_gods);
  cout << "list_gods_Greek:"<< list_gods_Greek<< endl;
  print_all(list_gods_Greek);
  cout << "list_gods_Norse:"<< list_gods_Norse<< endl;
  print_all(list_gods_Norse);
  cout << "list_gods_Roman:"<< list_gods_Roman<< endl;
  print_all(list_gods_Roman);

  while (pt) {
    string god_myth = pt->gd.mythology;
    cout << "processing " << pt->gd.name << endl;
    Link* next = pt->erase();  // this will point to the next iteration
    // Before we re-insert *pt into another list, make sure we clean the prev and succ pointers (as they might be copied if the new list was nullptr
    pt->clear_ptrs();

    if (god_myth == "Greek")
      list_gods_Greek = list_gods_Greek->add_ordered(pt);
    else if (god_myth == "Norse")
      list_gods_Norse = list_gods_Norse->add_ordered(pt);
    else
      list_gods_Roman = list_gods_Roman->add_ordered(pt);

    pt = next; // advance (prepare for next iteration
  }

  // at this point list_gods still non nullptr
  list_gods = pt;

  cout << "******************************************************" << endl;
  cout << "After modification" << endl;
  cout << "******************************************************" << endl;

  cout << "list_gods:"<< list_gods<< endl;
  print_all(list_gods);
  cout << "list_gods_Greek:"<< list_gods_Greek<< endl;
  print_all(list_gods_Greek);
  cout << "list_gods_Norse:"<< list_gods_Norse<< endl;
  print_all(list_gods_Norse);
  cout << "list_gods_Roman:"<< list_gods_Roman<< endl;
  print_all(list_gods_Roman);


}
