// Design and implement a rational number class, Rational.
/* A rational number has two parts: a numerator and a denominator, for example 5/6 (five-sixths, also know approximately .83333).
 * Provide assignment, addition, subtraction, multiplication, division, and equality operators. Also, provide a conversion to double.

 */
// g++ -std=c++11 -g Rational.C ch9.e.13_RationalNumberClass.C  -o ch9.e.13_RationalNumberClass.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"
#include "Rational.h"

int main ()
{
  vector <int> numbers; // = {6, -6, 27, -27};

  /*
  const int divider = 1;
  cout << "Illustrating mod operation with divider " << divider << endl;

  for (int i=-(divider+1);i<= (divider+1); ++i ){
    cout << "\t" << i << " % " << divider << " = " << i%divider << endl;
    numbers.push_back(i);
  }
*/

  const int limit = 5;
  for (int i=1;i<= limit; ++i ){
    cout << "\t" << i << " = " << i << endl;
    numbers.push_back(i);
  }

  Rational A(45,9);
  Rational B(-1,6);
  Rational C(1,3);
  Rational D(4,6); // == 2/3



  vector<Rational> rationals= {A,B,C,D};
  for (auto a:rationals){
    cout << "a = " << a << " (double form = "<< a.con_double()  << ")"<<endl;
      for (auto b: rationals){
        cout << "\t "<< a <<" + " << b<< " = "<< a+b << endl;
        cout << "\t "<< a <<" - " << b<< " = "<< a-b << endl;
        cout << "\t "<< a <<" * " << b<< " = "<< a*b << endl;
        cout << "\t "<< a <<" / " << b<< " = "<< a/b << endl;
        cout << endl;
      }
    }

  cout << "##############################################"<< endl;
  // one more time:
  cout << endl;
  rationals.clear(); // clear the old array
  rationals = {Rational(1,2), Rational(1,10), Rational(-1,2), Rational(1,-10)};
 /*
  for (int a:numbers){
    for (int b: numbers){
      if (b!=0)  // we can not have zero in denominator
        rationals.push_back(Rational(a,b));
    }
  }
*/
  for (auto a:rationals){
    cout << "a = " << a << " (double form = "<< a.con_double()  << ")"<<endl;
      for (auto b: rationals){
        cout << "\t "<< a <<" + " << b<< " = "<< a+b << endl;
        cout << "\t "<< a <<" - " << b<< " = "<< a-b << endl;
        cout << "\t "<< a <<" * " << b<< " = "<< a*b << endl;
        cout << "\t "<< a <<" / " << b<< " = "<< a/b << endl;
        cout << endl;
      }
    }

  // output today and tomorrow
  //cout << "A: " << A << endl;
  //cout << "B: " << B << endl;
  //cout << "C: " << C << endl;

  /*
  for (int a:numbers){
    for (int b: numbers){
      cout << "\t gcd("<< a <<", " << b<< ") = "<< A.gcd(a,b) << endl;
    }
  }
*/
  cout << endl;
  double x = 1.0;
  double z = x/3;
  double u = z+z;
  double v = u+z;
  cout << z << " = " << z << endl;
  cout << z << " + "<< z << " + " << z << " = " << z+z+z << " (delta = " << x - (z+z+z) << ")" <<endl;
  cout << z << " * 3.0 "<< z  << " = " << 3.0 * z << " (delta = " << x - (3.0*z) << ")" <<endl;
  cout << endl;
  cout << "u = z+z = " << u<< endl;
  cout << "v = u+z = " << v<< endl;
  cout << "v- x = " << v-x << endl;

  cout << "Illustration when Rational is better then the double\n";
  long int den = 0x100000000000001;//0x100_0000_0000_0001
  Rational One(1,1);
  Rational smalRat(1,den);
  Rational two_smalRat = smalRat+smalRat;
  cout << "smalRat = "<< smalRat<<endl;
  cout << "two_smalRat = "<< two_smalRat<<endl;
  cout << "One + smalRat = " << One << " + " << smalRat << " = " << One + smalRat << endl;
  cout << "(One + smalRat) - One = "  << (One + smalRat) - One << endl;
  double oneD = 1.0/den;
  double twoD = oneD+oneD;
  cout << "oneD = " << oneD << endl;
  cout << "twoD = " << twoD << endl;
  cout << "1.0 + oneD = " << 1.0 + oneD << endl;
  cout << "(1.0 + oneD) - 1.0 = " << (1.0 + oneD) - 1.0 << endl;

  double dd_01 = 52.796;
  Rational rr_01 = dd_01;
  cout << "dd_01 = " << dd_01<< ", rr_01 = " << rr_01<< endl;
  rr_01.simplify();
  cout << "rr_01 (after simplification) is " << rr_01;
  cout << endl;

  double dd_02 = -52.796;
  Rational rr_02 = dd_02;
  cout << "dd_02 = " << dd_02<< ", rr_02 = " << rr_02<< endl;
  rr_02.simplify();
  cout << "rr_02 (after simplification) is " << rr_02;
  cout << endl;

  Rational rr_03((long int)5);
  cout << "rr_03 = " << rr_03<< endl;

  cout<< "Compound assignment operator:\n";
  cout << "rr_02 *= rr_03\n";
  rr_02 *= rr_03;
  cout << "rr_02 = " << rr_02 << " = "<< rr_02.whole_part_repr() << endl;

  rr_03 += rr_03;
  cout << "rr_03 += rr_03; result: "<< rr_03 <<endl;
  return 0;
}


