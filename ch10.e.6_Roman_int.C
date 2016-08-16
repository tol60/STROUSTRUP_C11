/* Define a Roman_int class for holding Roman numerals (as ints) with a << and >>
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
// g++ -std=c++11 -g ch10.e.6_Roman_int.C  -o ch10.e.6_Roman_int.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

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

bool operator==(const Roman_int& r1, const Roman_int& r2) {
  return (r1.as_int()==r2.as_int());
}

bool operator!=(const Roman_int& r1, const Roman_int& r2) {
  return (r1.as_int()!=r2.as_int());
}

ostream& operator<< (ostream& ost, const Roman_int& r) {
  int val = r.as_int();
  if (val<0) { // do we need to support negatives?
    ost << "-";
    val = -val;
  }
  int digVal = RomDigValues[0];
  // we execute the following loop only if val>= digVal
  for (int i=0;i<val/digVal;++i) {
    ost << RomDigChars[0]; // example 3000 will print out MMM
  }
  val %= digVal; // at this point val < 1000;

  int hundreds = val/100;
  val -= hundreds*100;

  int tens = val/10;
  int ones = val - tens *10;
  return ost << RomHundreds[hundreds]
                            << RomTens[tens]
                            << RomOnes[ones];
}

int findRomanDigitIndex(char ch) {
  // given a char as in input, tries to find if it matches the entry in the RomDigChars vector.
  // if match not found, return a negative number, otherwise return an index into RomDigCars/RomDigValues
  int indexRoman=-1;
  //const vector<char>RomDigChars{'M','D','C','L','X','V','I'};// digits in decreasing value order
  for (int i=0;i<RomDigChars.size();++i) {
    if (RomDigChars[i]==ch) { // this is a Digit that is part of a Roman number
      indexRoman = i;
      break;  // done with the search. Break out
    }
  }
  return indexRoman;
}

istream& operator>> (istream& ist, Roman_int& r){
  // read the first character. See if it is one of the Roman Digits
  char ch;
  if (!(ist>>ch)) return ist; // read the first symbol. If failed, we are done

  int indexRoman=findRomanDigitIndex(ch); // is it a Roman Digit? It is if non-negative result.
  if (indexRoman<0){ // We did not recognize the symbol => this is not a Roman Number, fail the input
    ist.unget();
    ist.clear(ios_base::failbit);
    return ist;
  }
  vector<int> indexRomDigits = {indexRoman}; // We will use this vector to keep track of input digits
                                             // (as indexes into RomDigChars and RomDigValues

  // read the rest of the digits
  while (ist.get(ch) ){  // unformatted input. If we were to use ist>>ch, then two different numbers would merge (Ex "IV V" -> IVV)
    indexRoman=findRomanDigitIndex(ch);
    if(indexRoman<0){  // Not a Roman Digit. Put the char back into the input stream.
      ist.unget();
      break; // Input complete, we need to process
    } else {
      indexRomDigits.push_back(indexRoman);
    }
  }

  // Now, convert The digits into Roman numbers.
  // As long as the digits are in the natural order (decreasing value), we take the digit at a face value.
  // Otherwise, two digits will be translated as:
  // * I to the left of V(=5) or X (=10) represent 1 less: IV(=4), IX(=9)
  // * X to the left of L(=50) or C(=100) represent 10 less: XL(=40), XC(=90)
  // * C to the left of D(=500) or M(=1000) represent 100 less: CD(=400), CM(=900)

  int val = 0; // this is the integer representation of the Roman number.
  const int lastIndex = indexRomDigits.size()-1;
  for (int i=0; i<=lastIndex;++i) {
    int digitVal = RomDigValues[indexRomDigits[i]]; // if we process two digits at once, we adjust this value
    if(i != lastIndex) { // is the a digit that follows right after this one?
      const int indexDelta = indexRomDigits[i+1]-indexRomDigits[i]; // normally this should be >=0 (Digit values are decreasing)
      if ( indexDelta < 0 ) { // this is the case where the normal order is broken. This is where we handle two symbol combination
        // we will modify the digitVal
        // and then increment i to indicate we processed two digits:
        switch (indexDelta) {
        case -1:  // CD(=400), XV(=40), IV(=4)
          switch (RomDigChars[indexRomDigits[i]]) {
          case 'C': // CD(=400)
            digitVal = 400;
            break;
          case 'X': // XV(=40)
            digitVal = 40;
            break;
          case 'I': // IV(=4)
            digitVal = 4;
            break;
          default:  // unexpected combination:
          {
            // string msg(1,ch);
            string msg = string(1,RomDigChars[indexRomDigits[i]]) + string(1,RomDigChars[indexRomDigits[i+1]]);
            error("Do not expect the following combination ",msg);
            break;
          }
          }
          break;
        case -2:  // CM(=900), XC(=90), IX(=9)
          switch (RomDigChars[indexRomDigits[i]]) {
          case 'C': // CM(=900)
            digitVal = 900;
            break;
          case 'X': // XC(=90)
            digitVal = 90;
            break;
          case 'I': // IX(=9)
            digitVal = 9;
            break;
          default:  // unexpected combination:
          {
            // string msg(1,ch);
            string msg = string(1,RomDigChars[indexRomDigits[i]]) + string(1,RomDigChars[indexRomDigits[i+1]]);
            error("Do not expect the following combination ",msg);
            break;
          }
          }
          break;
        default:  // unexpected combination:
        {
          // string msg(1,ch);
          string msg = string(1,RomDigChars[indexRomDigits[i]]) + string(1,RomDigChars[indexRomDigits[i+1]]);
          error("Do not expect the following combination ",msg);
          break;
        }
        }
        // we have modified the digitVal
        ++i; // and then increment i to indicate we processed two digits:
      }// if ( indexDelta < 0 ) { // we processed double symbols;
    } // if(i != lastIndex) { // is the a digit that follows right after this one?
    val += digitVal;
  } // loop by i = index of the Roman digit to be processed.
  r = Roman_int(val);
  return ist;
}

int main ()
{
  vector<Roman_int> inputRomans;
  vector<Roman_int> outputRomans;

  cout <<"Please enter the file name\n";
  string iname;
  cin >> iname;

  ofstream ost{iname};
  if(!ost) error("can not open output file",iname);
  ost.exceptions(ost.exceptions()|ios::badbit); // throw for bad()

  for (int i=1;i<3001;++i){
    Roman_int r(i);
    cout << "i = "<< r.as_int() << ", Roman = "<<r<<endl;
    ost << r << "\n";
    outputRomans.push_back(r);
  }
  ost.close(); // make sure we dump finish writing the file.

  /*
  for (int i=-11;i<11;++i){
    Roman_int r(i);
    cout << "i = "<< r.as_int() << ", Roman = "<<r<<endl;
  }

  for (int i=2989;i<3011;++i){
    Roman_int r(i);
    cout << "i = "<< r.as_int() << ", Roman = "<<r<<endl;
  }
  cout << endl;
  */



  ifstream ist{iname};
  if(!ist) error("can not open input file",iname);

  ist.exceptions(ist.exceptions()|ios::badbit); // throw for bad()

  for (Roman_int r; ist>>r; ) {
    inputRomans.push_back(r);
  }

  if (outputRomans.size()!= inputRomans.size()) {
    cout << "outputRomans.size() = " << outputRomans.size() << endl;
    cout << "inputRomans.size() = " << inputRomans.size() << endl;
    error("The number of elements does not match between the vectors");
  }

  for (int i=0;i<inputRomans.size();++i) {
    if (outputRomans[i] != inputRomans[i])
      error ("vectors don't match at index ",i);
  }

  cout << "Please input Roman number:\n";
  for(Roman_int r;cin>>r;){
    cout << "You entered: "<< r << ", which is = " << r.as_int()<<endl;
  }

  return 0;
}


