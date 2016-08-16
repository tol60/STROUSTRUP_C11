//
/* D6. Print the data elements from both vectors.
 * D5. Close the ofstream and then open an ifsteam for mydata.txt.
 *     Read the data from mydata.txt and store it in a new vector called processed_points.
 * D4. Open an ofstream and output each point to a file named mydata.txt.
 * D3. Print the data in original_points to see what it looks like
 * D2. Using the code and discussion in 10.4, prompt the user to input seven (x,y) pairs.
 *     As the data is entered, store it in a vector of Points called original_points
 * D1. Start a program to work with points, discussed in 10.4. Begin by defining the data type Point that has two coordinate nembers x and y.
 */
// g++ -std=c++11 -g ch10.d.2_Point_prompt.C  -o ch10.d.2_Point_prompt.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

struct Point {
  int x;
  int y;
  Point ():x{0},y{0}{}
  Point (int a, int b) :x{a},y{b}{}
};

bool operator == (const Point &a, const Point &b) {
  return ( (a.x == b.x) && (a.y == b.y) );
}

bool operator != (const Point &a, const Point &b) {
  return !(a==b);
}
ostream& operator<< (ostream& os, const Point& p) {
  return os << '('<< p.x
      <<','<< p.y << ')';
}

istream & operator>> (istream & is, Point&p){
     int x, y;
     char ch1, ch2, ch3;
     is >> ch1>> x >> ch2 >> y >> ch3;

     if (!is) return is;
     if (ch1!='(' || ch2!=',' || ch3!=')') {
       is.clear(ios_base::failbit);   // set the fail bit
       return is;
     }

      p= Point(x,y); // update Point p

     return is;
}

int main ()
{
  //D2. Using the code and discussion in 10.4, prompt the user to input seven (x,y) pairs.
  vector <Point> original_points;
  const int NUM_POINTS = 7;
  // prompt the user for the entrance:
  cout << "Please enter " << NUM_POINTS <<" points in the format (x,y) \n";

  // enter the points
  for (int i=0; i< NUM_POINTS;++i){
    Point p;
    cin >> p;
    if (!cin) error ("Encountered error reading the point ",i);
    original_points.push_back(p);
  }

  // D3. Print the data in original_points to see what it looks like
  for (int i=0; i< original_points.size();++i){
    cout << "Original Point["<<i<< "] = " << original_points[i] << endl;
  }

  // D4. Open an ofstream and output each point to a file named mydata.txt.
  ofstream ost {"mydata.txt"}; // output stream for a file mydata.txt
  for (auto p:original_points)
    ost << p <<endl;

  // D5. Close the ofstream and then open an ifsteam for mydata.txt. Read the data from mydata.txt and store it in a new vector called processed_points.
  ost.close();

  vector <Point> processed_points;
  ifstream ist{"mydata.txt"};
  for (Point p; ist>>p; )
    processed_points.push_back(p);

  // D6. Print the data elements from both vectors.
  for (int i=0; i< original_points.size();++i){
    cout << "Original Point["<<i<< "] = " << original_points[i] << endl;
  }
  for (int i=0; i< processed_points.size();++i){
    cout << "Processed Point["<<i<< "] = " << processed_points[i] << endl;
  }

  // D7. Compare the two vectors and print Something's wrong if the number of elements or the values of elements differ.
  if (original_points.size() != processed_points.size()) {
    cout << "Something is wrong! The sizes are different \n";
  } else {
    for (int i=0; i<processed_points.size(); ++i) {
      if (original_points[i] != processed_points[i]) {
        cout << "Something is wrong, Mismatch detected in entrie " << i<< endl;
      }
    }

  }

  /* D1 Point type
  Point pA;
  cout << "Default Point A = " << pA<< endl;

  Point pB{-45, 7};
  cout << "Point B = " << pB<< endl;

  Point pC(pB); // Copy constructor
  cout << "Point C (initialized by Point B) = " << pC<< endl;
  pC.y +=3;
  cout << "After incrementing y by 3, Point C = " << pC << endl;
  */
  return 0;
}


