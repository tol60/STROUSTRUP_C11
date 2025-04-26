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
// g++ -std=c++11 -o test_Roman.exe -g test_Roman.C  Roman.C 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"
#include "Roman.h"


int main ()
{
  vector<Roman::Roman_int> inputRomans;
  vector<Roman::Roman_int> outputRomans;

  cout <<"Please enter the file name\n";
  string iname;
  cin >> iname;

  ofstream ost{iname};
  if(!ost) error("can not open output file",iname);
  ost.exceptions(ost.exceptions()|ios::badbit); // throw for bad()

  for (int i=1;i<3001;++i){
    Roman::Roman_int r(i);
    cout << "i = "<< r.as_int() << ", Roman = "<<r<<endl;
    ost << r << "\n";
    outputRomans.push_back(r);
  }
  ost.close(); // make sure we dump finish writing the file.

  /*
  for (int i=-11;i<11;++i){
    Roman::Roman_int r(i);
    cout << "i = "<< r.as_int() << ", Roman = "<<r<<endl;
  }

  for (int i=2989;i<3011;++i){
    Roman::Roman_int r(i);
    cout << "i = "<< r.as_int() << ", Roman = "<<r<<endl;
  }
  cout << endl;
  */



  ifstream ist{iname};
  if(!ist) error("can not open input file",iname);

  ist.exceptions(ist.exceptions()|ios::badbit); // throw for bad()

  for (Roman::Roman_int r; ist>>r; ) {
    inputRomans.push_back(r);
  }

  if (outputRomans.size()!= inputRomans.size()) {
    cout << "outputRomans.size() = " << outputRomans.size() << endl;
    cout << "inputRomans.size() = " << inputRomans.size() << endl;
    error("The number of elements does not match between the vectors");
  }
  cout<< "Ouput matched!\n\n";

  for (int i=0;i<inputRomans.size();++i) {
    if (outputRomans[i] != inputRomans[i])
      error ("vectors don't match at index ",i);
  }

  cout << "Please input Roman number:\n";
  for(Roman::Roman_int r;cin>>r;){
    cout << "You entered: "<< r << ", which is = " << r.as_int()<<endl;
  }

  return 0;
}


