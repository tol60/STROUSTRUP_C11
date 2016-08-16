// EX11. Write a function that finds the smallest and the largest element of a vector arguments and also computes the mean and a median
//   Either return a struct containing the results or pass them back through reference arguments.
// EX10. Write a function maxv() that returns the largest element of a vector argument
// Ex9. Write a function that given two vector<double> s price and weight computes a value (an "index") that is
//    the sum of all price[i]*weight[i]. Make sure to have weight.size()==price.size().
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
// g++ -std=c++11 -g -o ch8.e.11_vector_stats.exe ch8.e.11_vector_stats.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

// the structure used to return the results from vector_stats() function
struct stat_results_S {
  double min;
  double max;
  double mean;
  double median;
};

// vector_stats() calculates min, max, mean, and median
// as we need to sort the vector, we will pass vector by value (and thus create an internal copy)
void vector_stats(vector<double> v, stat_results_S& results){
  int sz = v.size();
  if (sz == 0)
    results = {0.0, 0.0, 0.0, 0.0 }; // if empty, return all zeroes
  else {
    sort(v.begin(), v.end()); // sort internal copy.  DO NOT pass by reference
    results.min = v[0]; // first element of the sorted vector
    results.max = v[sz-1]; // last element of the sorted vector

    // mean
    double sum=0.0;
    for (int i=0; i<sz; ++i)
      sum += v[i];
    results.mean = sum/sz; // this will be a double division

    // median - this is why we needed to sort the vector
    if ((sz & 0x1)==1) { // if we have odd number of elements, just take the one in the middle
      results.median = v[(sz-1)/2];
    } else { // we have even number of elements, index start at zero
      // 0, 1, 2, 3; sz=4; sz/2 = 2. Need to take average of 1 and 2
      int half = sz/2; // as we checked, sz is even, integer division, no rounding
      results.median = (v[half-1] + v[half]) / 2.0;
    }
  }
}


double maxv(const vector<double>& v){
  // make sure an array is non-empty
  if (v.size() == 0)
    error("Error: maxv: the input array is empty");

  double max = v[0];
  for (int i=1; i<v.size();i++)
    if (v[i]>max)
      max = v[i];

  return max;
}

double price_weight_index(const vector<double>& prices, const vector<double>& weights){
  // check the sizes
  if (prices.size() != weights.size()){
    string msg = "price_weight_index: Error: input vector sizes do not match " + to_string(prices.size()) + " != " + to_string(weights.size());
    error (msg);
  }

  // do the calculation
  double answer = 0.0;
  for (int i=0; i<prices.size(); i++)
    answer += prices[i]*weights[i];

  return answer;
}

// A function prints a vector of int (the label first) to cout
void print(const string& str, const vector<int>& v) {
  cout << str;  // label
  for (int i=0; i<v.size(); i++)
    cout << v[i]<<" ";

  cout << endl; // get to a new line after we complete the output
}

// A function prints a vector of doubles (the label first) to cout
void print(const string& str, const vector<double>& v) {
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
  stat_results_S res;
  string msg;
  // EX 11
  vector <double> v1{-3.4};
  msg = "v1 = ";
  print(msg, v1);
  vector_stats(v1, res);
  cout << "min = " << res.min <<", max = "<< res.max <<", mean = " << res.mean << ", median = "<< res.median << endl;
  print(msg,v1);
  cout << endl;

  v1.clear(); // now it is empty vector
  msg = "v1 = ";
  print(msg, v1);
  vector_stats(v1, res);
  cout << "min = " << res.min <<", max = "<< res.max <<", mean = " << res.mean << ", median = "<< res.median << endl;
  print(msg,v1);
  cout << endl;

  v1 = {4.1, -3, -4, 7, 6, 5.1};
  msg = "v1 = ";
  print(msg, v1);
  vector_stats(v1, res);
  cout << "min = " << res.min <<", max = "<< res.max <<", mean = " << res.mean << ", median = "<< res.median << endl;
  print(msg,v1);
  cout << endl;

  v1 = {4.1, -3, -4, 7, 6};
  msg = "v1 = ";
  print(msg, v1);
  vector_stats(v1, res);
  cout << "min = " << res.min <<", max = "<< res.max <<", mean = " << res.mean << ", median = "<< res.median << endl;
  print(msg,v1);
  cout << endl;

  /* EX10
  string msg;
  vector<double> v0;
  msg = "v0 = ";
  print(msg, v0);
  try {
    cout << "maxv returned = " << maxv(v0) << endl<< endl;
  }
  catch(runtime_error& e) {
    cerr << e.what() << endl;
  }

  v0 = {3,4,5,6.5,4};
  print(msg, v0);
  try {
    cout << "maxv returned = " << maxv(v0) << endl<< endl;
  }
  catch(runtime_error& e) {
    cerr << e.what() << endl;
  }
  */
  /*
  string msg;
  vector <double> p1{5.1, 6.1, 7.1, 6.1};
  vector <double> w1{0.25, 0.25, 0.25, 0.25};

  msg = "p1: ";
  print(msg,p1);
  msg = "w1: ";
  print(msg,w1);
  try {
    cout << "price_weight_index = " << price_weight_index(p1,w1) << endl << endl;
  }
  catch(runtime_error& e) {
    cerr << e.what() << endl;
  }

  vector <double> p2{5.1, 6.1, 7.1};
  vector <double> w2{0.25, 0.25, 0.25, 0.25};

  msg = "p2: ";
  print(msg,p2);
  msg = "w2: ";
  print(msg,w2);
  try {
    cout << "price_weight_index = " << price_weight_index(p2,w2) << endl << endl;
  }
  catch(runtime_error& e) {
    cerr << e.what() << endl;
    cout << endl;
  }

  vector <double> p3{5.1, 6.1, 7.1};
  vector <double> w3{1.0/3, 1/3.0, 1/3.0};

  msg = "p3: ";
  print(msg,p3);
  msg = "w3: ";
  print(msg,w3);
  try {
    cout << "price_weight_index = " << price_weight_index(p3,w3) << endl << endl;
  }
  catch(runtime_error& e) {
    cerr << e.what() << endl;
    cout << endl;
  }
  */

  /*
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
  */
  return 0;
}
