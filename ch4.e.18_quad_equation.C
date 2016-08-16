// solve the quadratic equation a*x^2 + b*x + c = 0
// g++ -std=c++11 -g -o ch4.e.18_quad_equation.exe ch4.e.18_quad_equation.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

// this functions will be used to verify our solution.
double quad (double a, double b, double c, double x) {
  return a*x*x + b*x + c;
}

int main ()
{
  cout << "I will try to solve the quadratic equation a*x^2 + b*x + c = 0" << endl;
  cout << "Please enter the 3 coefficients a b c:" << endl;
  double a, b, c;
  cin >> a >> b >> c;
  cout << "Trying to solve " << a << "*x^2 + "<< b << "*x + "<< c << " = 0" << endl;

  if (a==0.0) {
    // solve linear equation
    if (b == 0.0) {
      // equation simplifies to c = 0
      if (c==0) {
        cout << "Infinitely many answers: (-inf; inf) - the whole real line\n";
      } else {
        cout << "This equation does not have a solution\n";
      }
    } else {
      // equation simplifies to b*x + c = 0, where b !=0
      double x = -c/b;
      cout << "This Linear equation has one solution: x = "<< x << " \t(a*x^2 + b*x + c = "<< quad(a,b,c,x) << ")" << endl;
    }
  } else {
    // a*x^2 + b*x + c = 0, where a != 0.0
    double D = b*b - 4*a*c;
    if (D<0.0) {
      cout << "This quadratic equation has no real solutions: Determinate ="<< D << " is less then 0\n";
    } else if (D==0.0) {
      double x = -b/(2*a);
      cout << "This quadratic equation has two equal roots: x1 = x2 = " << x << " \t(a*x^2 + b*x + c = "<< quad(a,b,c,x) << ")" << endl;
    } else {
      double x1 = (-b - sqrt(D))/(2*a);
      double x2 = (-b + sqrt(D))/(2*a);
      cout << "This quadratic equation has two roots:\n";
      cout << "\tx1 = " << x1 << " \t(a*x^2 + b*x + c = "<< quad(a,b,c,x1) << ")" <<endl;
      cout << "\tx2 = " << x2 << " \t(a*x^2 + b*x + c = "<< quad(a,b,c,x2) << ")" << endl;
    }
  }
  return 0;
}


