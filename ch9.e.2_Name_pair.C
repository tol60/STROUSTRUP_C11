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

// g++ -std=c++11 -g -o ch9.e.2_Name_pair.exe ch9.e.2_Name_pair.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

class Name_pairs {
public:
  class Invalid{};              // to throw an exception

  void read_names(); // reads a series of names
  void read_ages();  // prompts the user for an age for each name
  void print(); // prints out the (name[i], age[i]) pairs (one per line) in the order determined by the name vector
  void sort(); // sorts the name vector in alphabetical order and reorganizes the age vector to match
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

int main ()
{
  Name_pairs pair;
  pair.read_names();
  //pair.print(); // should throw Invalid{};
  pair.read_ages();
  pair.print();

  /*
  // reset and read the names
  pair.read_names();
  pair.read_ages();
  pair.print();
  */

  pair.sort();
  pair.print();

  return 0;
}
