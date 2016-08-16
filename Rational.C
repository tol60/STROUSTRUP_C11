/*
 * Rational.C
 *
 *  Created on: Feb 20, 2016
 *      Author: tony
 */
#include "Rational.h"

string Rational::whole_part_repr()
{
  this->simplify();
  stringstream ss;
  string str;
  if (n!=1 && abs(m) > n){
    long int whole = abs(m) /n;
    long int rem = abs(m) % n;
    if (m<0) ss << "-(";
    ss << whole<< '+' << rem<< '/' <<n ;
    if (m<0) ss << ')';
  }
  return ss.str();
}

Rational::Rational(double f) // construct from floating point Rational approximation.
:m{(long int)(f)},  // int approximation
 n{1}
{
  double remainder = abs(f - double (m)/n);
  double adjF = f; // this will be used in calculating the next approximation
  //cout << "m = "<< m <<", remainder = "<< remainder << endl;
  while (remainder>0 && abs(m)< LONG_MAX/10 && n<LONG_MAX/10){
    adjF *=10; // eventually we should drive the decimal part out.
    m = (long int) adjF;
    n *=10;
    remainder = abs(f - double (m)/n);
    //cout << "m = "<< m <<", remainder = "<< remainder << endl;
  }
}

Rational::Rational(long int in_m, long int in_n)
: m{in_m},
  n{in_n}
{
  if (n==0) error("we can not have 0 in denominator");

  if (n<0) { // keep denominator positive at all times
    m=-m;
    n=-n;
  }

  // can we simplify the fraction?
  long int divider = abs(gcd(m,n));
  if (divider != 1) {  // divide numerator and denominator by the same number.
    m /= divider;
    n /= divider;
  }
}

ostream& operator <<(ostream& os, const Rational & r){
  os << r.num();
  if (r.den()!=1){
    os <<  '/'
        << r.den();
  }
  return os;
}

Rational operator-(const Rational& a) // unary '-'
{
  return Rational (- a.num(), a.den()); // flip the sign in the numerator
}

Rational& Rational::operator*=(const Rational& mul) // unary '*='
{
  m *=mul.num();
  n *=mul.den();
  this->simplify(); // is there a common multiple between numerator and denominator?
  return *this;
}

Rational& Rational::operator/=(const Rational& mul) // unary '/='
{
  if (mul.num()==0)
    error ("can not delete by zero");
  m *=mul.den();
  n *=mul.num();
  this->simplify(); // is there a common multiple between numerator and denominator? Also make sure denominator is non-negative (25 Jun 2016)
  return *this;
}

Rational& Rational::operator+=(const Rational& b) // unary '+='
{
  // bring the two numbers to the least common denominator and then do the action.

  // 1. greatest common denominator of the fractions.
  long int com_factor = this->gcd (n, b.den());

  m = m * (b.den()/com_factor) + b.num() *(n/com_factor); // numerator
  n = n / com_factor *b.den(); // denominator least common denominator

  this->simplify(); // is there a common multiple between numerator and denominator?
  return *this;

}
Rational& Rational::operator-=(const Rational& b) // unary '-='
{
  // bring the two numbers to the least common denominator and then do the action.

  // 1. greatest common denominator of the fractions.
  long int com_factor = this->gcd (n, b.den());

  m = m * (b.den()/com_factor) - b.num() *(n/com_factor); // numerator
  n = n / com_factor *b.den(); // denominator least common denominator

  this->simplify(); // is there a common multiple between numerator and denominator?
  return *this;
}

void Rational::simplify() // will try to simplify fraction (in case there are common factors in numerator and denominator)
{
  long int com_factor = this->gcd (abs(m), n);
  if (com_factor !=1)
  {
    m /= com_factor;
    n /= com_factor;
  }

  // make sure denominator is non-negative 25 Jun 2016
  if (n<0) { // keep denominator positive at all times
    m=-m;
    n=-n;
  }
}

Rational operator+(const Rational & a, const Rational & b) // add
{
  // bring the two numbers to the least common denominator and then do the action.

  // 1. greatest common denominator of the fractions.
  long int com_factor = a.gcd (a.den(), b.den());

  long int numer = a.num() * (b.den()/com_factor) + b.num() *(a.den()/com_factor); // numerator
  long int denom = a.den() / com_factor *b.den(); // denominator least common denominator

  return Rational(numer, denom);
}

Rational operator-(const Rational &a, const Rational &b) //subtract
{
  return a + (-b);
}


Rational operator*(const Rational & a, const Rational & b) // multiplication
{
  long int numer = a.num() * b.num(); // num * num
  long int denom = a.den() * b.den(); // den * den

  return Rational (numer, denom); // the constructor will automatically simplify the fraction
}

Rational operator/(const Rational &a, const Rational & b) // Division
{
  // need an extra checker on the denominator non-zero.
  if (b.num()==0)
    error ("can not delete by zero");

  long int numer = a.num() * b.den(); // num * den (division = multiplication of inverse)
  long int denom = a.den() * b.num(); // den * num (division = multiplication of inverse)

  return Rational (numer, denom); // the constructor will automatically simplify the fraction
}

long int Rational::gcd(long int a, long int b) const // greatest common divisor Euclid's algorithm
// Euclid's algorithm
// gcd(a,0)=a
// gcd(a,b) = gcd(b, a mod b)
// where a mdo b = a -b *floor(a/b)
{
  // for now let's assume a and b are positive
  if (b==0) {
    return a; // gcd(a,0)=a
  }
  return gcd(b, a%b); // gcd(a,b) = gcd(b, a mod b)
}

