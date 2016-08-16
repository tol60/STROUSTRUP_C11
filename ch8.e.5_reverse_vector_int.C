// Ex5. Write two functions that reverse the order of elements in a vector<int>.
/*
    For example, 1, 3, 5, 7, 9 becomes 9,7,5,3,1.
    The first reverse function should produce a new vector with the the reversed sequence, leaving the original vector unchanged.
    The other reverse function should reverse the elements of its vector without using any other vectors (hint: swap)
 */
// Ex4. An int can hold integers only up ot a maximum number. Find an approximantion of that maximum number by using fibonacci() = 2^31-1
// Ex3. Create a vector of Fibonacci numbers an print them using the function from Exercise 2.
/*
  To create a vector, write a function, fibonacci(x,y,v,n),
    where integers x and y are ints, v is an empty vector<int>, and n is the number of elements to put into v;
    v[0] will be x and v[1] will be y.
  A Fibonacci number i sone that is part of a sequence where each element is the sum of the two previous ones.
  For example, starth with 1 and 2, we get 1, 2, 3, 5, 8, 13, 21, ..
*/
// Ex2. Write a function print() that prints a vector of ints to cout.
//  Give it two arguments:
//    1. a string for "labeling"
//    2. a vector
// g++ -std=c++11 -g -o ch8.e.5_reverse_vector_int.exe ch8.e.5_reverse_vector_int.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

// reverse an integer vector. Create a brand new vector.
vector<int> reverse(const vector<int>& v){
  vector<int> w;
  for(int i=v.size()-1; i>=0;i--)
    w.push_back(v[i]);
  return w;
}

// reverse this int vector
void reverse(vector<int>& v)
{
  int i=0;
  int j=v.size()-1;
  while (i<=j)
    swap(v[i++], v[j--]);  // do the swap and then increment the left index, decrement the right index
}

// reverse a string vector. Create a brand new vector.
vector<string> reverse(const vector<string>& v){
  vector<string> w;
  for(int i=v.size()-1; i>=0;i--)
    w.push_back(v[i]);
  return w;
}

// reverse this string vector
void reverse(vector<string>& v)
{
  int i=0;
  int j=v.size()-1;
  while (i<=j)
    swap(v[i++], v[j--]);  // do the swap and then increment the left index, decrement the right index
}

// generates the Fibonacci sequence starting with x and y (and then adds n number to vector v
void fibonacci(int x, int y, vector<int>& v, int n) {
  v.push_back(x); // v[0]=x
  v.push_back(y); // v[1]=y
  for (int i=0; i<n; i++)
    v.push_back(v[i]+v[i+1]);
}

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

int main ()
{
  const vector<int> cv{1,2,3,4,5};
  vector <int> answ1 = reverse(cv);
  string label = "answ1 = ";
  print(label, answ1);

  vector <int> reg_v{10,11,12,13,14,15};
  reverse (reg_v);
  label = "reversing reg_v = ";
  print(label,reg_v);

  vector <int> reg_v2{20,21,22,23,24};
  reverse (reg_v2);
  label = "reversing reg_v2 = ";
  print(label,reg_v2);

  const vector <string> str_cv{"one", "two", "three"};
  vector<string> str_answ1 = reverse(str_cv);
  label = "str_answ1 = ";
  print (label,str_answ1);

  vector <string> str_v{"one", "two", "three", "four", "five"};
  reverse (str_v);
  label = "reversing str_v = ";
  print (label, str_v);

  //vector<int> iv;
  //fibonacci(1,2,iv,66);
  //string message = "iv vector = ";
  //print (message, iv);

  return 0;
}
