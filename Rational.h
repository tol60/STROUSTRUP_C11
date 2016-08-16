// Design and implement a rational number class, Rational.
/* A rational number has two parts: a numerator and a denominator, for example 5/6 (five-sixths, also know approximately .83333).
 * Provide assignment, addition, subtraction, multiplication, division, and equality operators. Also, provide a conversion to double.
 *
 * Log:
 * simplify() -- make sure denominator non-zero. 25 Jun 2016

 */
// g++ -std=c++11 -g -o ch9.e.13_RationalNumberClass.exe ch9.e.13_RationalNumberClass.C  2>&1 | tee tmp.txt

#ifndef RATIONAL_H_
#define RATIONAL_H_

#include "std_lib_facilities.h"
#include <climits> // LONG_MAX  Maximum value for an object of type long int  2147483647 (231-1) or greater*

class Rational {
public:
  class Invalid{};             // to throw an exception
  Rational():m{0},n{1}{};
  Rational (long int m, long int n); // constructor m/n; Automaitcally simplifies it
  Rational (long int a):m{a},n{1}{}; // constructor m/1
  Rational (double f); // construct from floating point Rational approximation.
  long int num() const {return m;}  // return numerator
  long int den() const {return n;}  // return denominator
  double con_double() const {return double(m) / double (n);} // convert to double

  // share algorithm with the world
  long int gcd(long int a, long int b) const;  // greatest common divisor Euclid's algorithm
  void simplify(); // will try to simplify fraction (in case there are common factors in numerator and denominator). Will also make denominator non-negative
  Rational& operator*=(const Rational& mul); // unary '*='
  Rational& operator/=(const Rational& mul); // unary '/='
  Rational& operator+=(const Rational& mul); // unary '+='
  Rational& operator-=(const Rational& mul); // unary '-='
  string whole_part_repr();
private:
  long int m; // numerator
  long int n; // denominator. For simplicity keep it >0
};

// Operators:
ostream& operator <<(ostream& os, const Rational & r);

Rational operator-(const Rational&); // unary '-'


Rational operator+(const Rational &, const Rational &); // add
Rational operator-(const Rational &, const Rational &); //subtract

Rational operator*(const Rational &, const Rational &); // multiplication
Rational operator/(const Rational &, const Rational &); // Division

// helper functions


#endif  /* PATRON_H_ */



