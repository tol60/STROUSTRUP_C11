// Replace Name_pair::print() with a (global) operator << and define == and != for Name_pair

// Design and implement a Name_pairs class holding (name,age) pairs where
/*
  name is a string and age is a double. Represent that as a vector<string>
  (called name) and a vector<double> (called age) member. Provide an input operator
  read_names() that reads a series of names. Provide a
  read_ages() operation that prompts the user for an age for each name. Provide a
  print() operation that prints out the (name[i], age[i]) pairs (one per line) in the order determined by the name vector. Provide a
  sort() operation that sorts the name vector in alphabetical order and reorganizes the age vector to match.

  Implement all "operations" as member functions.

 */

// g++ -std=c++11 -g -o ch9.e.3_Name_pair_cout.exe ch9.e.3_Name_pair_cout.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

class Name_pairs {
public:
  class Invalid{};              // to throw an exception

  void read_names(); // reads a series of names
  void read_ages();  // prompts the user for an age for each name
  void print(); // prints out the (name[i], age[i]) pairs (one per line) in the order determined by the name vector
  void sort(); // sorts the name vector in alphabetical order and reorganizes the age vector to match
  bool is_valid() const; // check if the sizes of the arrays match
  int size() const; // the size of name vector
  //int age_size() const {return age.size();} // the size of age vector
  const string & name_el(int ind) const; // return the reference to a string name[i]
  double age_el(int ind) const; // return age[i]
private:
  vector <string> name;
  vector <double> age;
};


void Name_pairs::read_names() // read a series of names
{
  name.clear(); // reset all the names
  age.clear(); // reset all the ages
  cout<< "Please enter the names you want to store (when done, enter q):\n";
  string str;
  cin>>str;
  while (str != "q"){
    name.push_back(str);
    cin>>str;
  }
}

void Name_pairs::read_ages() // prompts the user for an age for each name
{
  age.clear();
  cout << "Please enter the age for each name:\n";
  for (int i=0; i<name.size(); ++i){
    cout << (i+1) << ". " << name[i] << ": ";
    double age_entry;
    cin >> age_entry;

    //handling io fails
    if (cin.fail()) {
          cin.clear();  // clear error flags
          cin.ignore(10000,'\n'); // remove a bunch of characters that are still in the buffer up to a new line
          --i; // make sure we try to repeat the input
    }

    if (age_entry>0)
      age.push_back(age_entry);
    else {
      cout << "Error: you entered a non-positive age "<< age_entry << "for name " << name[i] <<endl;
    }
  }
}

void Name_pairs::print() // prints out the (name[i], age[i]) pairs (one per line) in the order determined by the name vector
{
  if (name.size()!= age.size()) // we probably did not read the ages yet.
    throw Invalid{};
  for (int i=0; i<name.size(); ++i){
    cout << i << ". (" << name[i] << ", " << age[i] << ")\n";
  }
}

void Name_pairs::sort() // sorts the name vector in alphabetical order and reorganizes the age vector to match
{
  if (name.size()!= age.size()) // we probably did not read the ages yet.
    throw Invalid{};
  vector <string> orig_name(name); // we need an original vector order
  std::sort(name.begin(),name.end()); // name is sorted now

  vector <double> orig_age(age); // we need original values
  for (int i=0; i< name.size(); ++i){
    // find the old location
    int k=-1; // old index
    for (k=0; k<orig_name.size(); ++k  ) {
      if (orig_name[k] == name[i])
        break;
    }

    if (k<0)
      throw Invalid{}; // some internal error

    age[i] = orig_age[k]; // now it is order is matched.
  }
}

bool Name_pairs::is_valid() const
{
  if (name.size()!= age.size()) // we probably did not read the ages yet.
    return false;
  return true;
}

int Name_pairs::size() const
{
  if (name.size()!=age.size())
    throw Invalid{};
  return name.size();
}

const string & Name_pairs::name_el(int ind) const // return the reference to a string name[i]
{
  if (ind<0 || ind>=name.size())
    throw Invalid{};
  return name[ind];
}
double Name_pairs::age_el(int ind) const // return age[i]
{
  if (ind<0 || ind>=age.size())
    throw Invalid{};
  return age[ind];
}

ostream& operator << (ostream& os, const Name_pairs& np){
  if (!np.is_valid())
    throw Name_pairs::Invalid{};
  for (int i=0; i<np.size(); ++i){
    os << i << ". (" << np.name_el(i) << ", " << np.age_el(i) << ")\n";
  }
  return os;
}

bool operator != (const Name_pairs& a, const Name_pairs& b)
    {
      if (a.size()!= b.size())
        return true;
      for (int i=0;i<a.size(); ++i)
        if (a.name_el(i) != b.name_el(i) || a.age_el(i) != b.age_el(i))
          return true;

      return false;
    }

bool operator == (const Name_pairs&a, const Name_pairs& b)
    {
      return !(a!=b);
    }

int main ()
{
  Name_pairs first_pair;
  first_pair.read_names();
  // first_pair.size(); /// should throw Invalid{};
  //pair.print(); // should throw Invalid{};
  first_pair.read_ages();
  first_pair.size(); // should be ok
  //pair.print();
  cout << "listing pairs:\n";
  cout << first_pair;

  /*
  // reset and read the names
  pair.read_names();
  pair.read_ages();
  pair.print();
  */

  Name_pairs second_pair (first_pair);
  second_pair.sort();
  cout << "listing pairs after the sort:\n";
  cout << second_pair;

  if (first_pair == second_pair)
    cout << "The pairs are identical\n";
  else
    cout << "The pairs are different\n";


  return 0;
}
