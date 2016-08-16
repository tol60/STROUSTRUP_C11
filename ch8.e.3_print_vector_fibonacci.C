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
// g++ -std=c++11 -g -o ch8.e.3_print_vector_fibonacci.exe ch8.e.3_print_vector_fibonacci.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

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

int main ()
{
  vector<int> iv;
  fibonacci(1,2,iv,10);
  string message = "iv vector = ";
  print (message, iv);

  return 0;
}
