/*
 * Roman.h
 *
 * Define a Roman_int class for holding Roman numerals (as ints) with a << and >>
 * Provide Roman_int with an as_int() member that returns the int value, so that if r is a Roman_int,
 * we can write cout << "Roman" << r << " equals " << r.as_int() << endl;
 * I
 * II
 * III
 * IV
 * V
 * VI
 * VII
 * VIII
 * IX
 * X
 *
 * I 1
 * V 5
 * X 10
 * L 50
 * C 100
 * D 500
 * M 1000
 *
 * I to the left of V(=5) or X (=10) represent 1 less: IV(=4), IX(=9)
 * X to the left of L(=50) or C(=100) represent 10 less: XL(=40), XC(=90)
 * C to the left of D(=500) or M(=1000) represent 100 less: CD(=400), CM(=900)
 *
 * Interesting observation:
 * MCD = 'M' + "CD" = 1000+400 = 1400
 * DCM = 'D' + "CM" = 500 + 900 = 1400 (although the natural order is violated. But you can say that MCD = DCM
 *
 * Similar
 * XIV and VIX
 */

#ifndef ROMAN_H_
#define ROMAN_H_

#include "std_lib_facilities.h"
using namespace std;

namespace Roman {

const vector<int> RomDigValues{ 1000,500,100,50,10,5,1 }; // digits in decreasing value order
const vector<char>RomDigChars{'M','D','C','L','X','V','I'};// digits in decreasing value order
// RomHundreds                            0, 100,200, 300,  400, 500,600, 700,   800,  900
const vector<string> RomHundreds{"","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"};
// RomTens                            0, 10, 20,  30,   40,  50, 60,  70,   80,   90
const vector<string> RomTens{"","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"};
// RomOnes                            0, 1,  2,   3,    4,   5,  6,   7,    8,    9
const vector<string> RomOnes{"","I","II","III","IV","V","VI","VII","VIII","IX"};

class Roman_int {
public:
  Roman_int():mValue(0) {}
  Roman_int(int n):mValue(n){}
  int as_int() const {return mValue;}
private:
  int mValue;
};

bool operator==(const Roman_int& r1, const Roman_int& r2);

bool operator!=(const Roman_int& r1, const Roman_int& r2);

int findRomanDigitIndex(char ch); // helper function used in the input operator

ostream& operator<< (ostream& ost, const Roman_int& r);
istream& operator>> (istream& ist, Roman_int& r);



}


#endif /* ROMAN_H_ */
