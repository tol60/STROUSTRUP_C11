// Ex7. Read five names into a vector<string> name, then prompt the user for the ages of the people named and store the ages in
/*
   for the ages of the people named and store the ages in a vector<double> age.
   Then print out the five (name[i], age[i]) pairs. Sort the names (sort(name.begin(), name.end()) and print out the (name[i], age[i]) pairs.
   The tricky part is to get the age vector in the correct order to match the sorted name vector.
  Hint:
    Before sorting name, take a copy and use that to make a copy  of age in the right order after sorting name.
    Then, do that exercise again but allowing an arbitrary number of names.
 */
// Ex2. Write a function print() that prints a vector of ints to cout.
//  Give it two arguments:
//    1. a string for "labeling"
//    2. a vector
// g++ -std=c++11 -g -o ch8.e.7_name_age_sort.exe ch8.e.7_name_age_sort.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"


// A function prints a vector of int (the label first) to cout
void print(const string& str, const vector<int>& v) {
  cout << str;  // label
  for (int i=0; i<v.size(); i++)
    cout << v[i]<<" ";

  cout << endl; // get to a new line after we complete the output
}

// A function prints a vector of strings (the label first) to cout
void print(const string& str, const vector<string>& v) {
  cout << str;  // label
  for (int i=0; i<v.size(); i++)
    cout << "\"" <<v[i]<<"\" ";

  cout << endl; // get to a new line after we complete the output
}

double find_age(const string& name, const vector<string>& Names, const vector<double>& Ages){
  if (Names.size() != Ages.size()){
    string msg = "find_age: Error: input array sizes do not match " + to_string(Names.size()) + " != " + to_string(Ages.size());
    error (msg);
  }

  int i =0;
  while (i<Names.size() && Names[i] != name )
    i++;

  // check that we found something
  if (i>= Names.size())
    error("find_age: Error: the name was not found");

  // we found the name in the list, return the age:
  return Ages[i];
}

int main ()
{
  vector <string> name;
  vector <double> age;
  // input 5 names
  for (int i=0; i<5;i++) {
    string str;
    cout << "Please enter the name["<<i<<"]:";
    cin>> str;
    name.push_back(str);
  }

  // input the age's
  for (int i=0; i<name.size(); i++ ) {
    double d_age = -1;
    cout << "Please enter "<< name[i] <<"'s age: \n";
    cin >> d_age;
    age.push_back(d_age);
  }

  // create a copy of names
  vector <string> name_unsorted(name);

  // sort the names.
  sort(name.begin(),name.end());

  // output the pairs:
  cout << "After sorting the names:\n";
  try {
    for (int i=0; i<name.size(); i++ ) {
      cout<< i<< " " << name[i] << "'s age is " << find_age(name[i], name_unsorted, age) << endl;
    }
  }
  catch(runtime_error& e) {
    cerr << e.what() << endl;
  }
  return 0;
}
