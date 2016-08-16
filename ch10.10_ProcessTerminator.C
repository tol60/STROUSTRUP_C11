/* This code will try to read a set of Dates and check for a terminator symbol.
 *
 * Note:
 * This function is of limited use. It assumes
 * for(My_type var; ist>>var;) {}
 *    will restore All symbols in ist in case of fail(). (which we can only do if we consume one symbol at a time.
 *
 * If we were to use it on our Chrono::Date  type, the following problem will occur:
 *    Input:
 *    (2016,3,19) (2016,3,22] | (2016,3,25) (2016,3,28) (2016,3,31) (2016,4,3)
 *
 *    Output:
 *    (2016,mar,19)
 *    * the second entry was mis-formatted ']' instead of ')'. We failed to enter it, but as the state of the stream was not restored.
 *
 * make sure we call on in the code:
 * ist.exceptions(ist.exceptions()|ios_base::badbit);
 */
// g++ -std=c++11 -g -o ch10.10_ProcessTerminator.exe ch10.10_ProcessTerminator.C  Chrono.C   2>&1 | tee tmp.txt

#include "std_lib_facilities.h"
#include "Chrono.h"


void end_of_loop (istream& ist, char term, const string& message)
/*
 * This function is of limited use. It assumes
 * for(My_type var; ist>>var;) {}
 *    will restore All symbols in ist in case of fail(). (which we can only do if we consume one symbol at a time.
 *
 * If we were to use it on our Chrono::Date  type, the following problem will occur:
 *    Input:
 *    (2016,3,19) (2016,3,22] | (2016,3,25) (2016,3,28) (2016,3,31) (2016,4,3)
 *
 *    Output:
 *    (2016,mar,19)
 *      the second entry was mis-formatted ']' instead of ')'. We failed to enter it, but as the state of the stream was not restored.
 *      the '|' was passed as terminator symbol
*/
{
  if (ist.eof()) return; // we reached eof. fail bit will probably also be set.
  if (ist.fail()) { // use term as terminator and/or separator
    ist.clear();
    char ch;
    if (ist>>ch && ch==term) return; // all is fine. we found a terminator
    error(message);
  }
}

int main ()
{
  // make sure put somewhere
  //ist.exceptions(ist.exceptions()|ios_base:badbit);

  string fname = "dates_file.txt";

  // the following block will generate the original file (can comment it out if yo modifying by hand)
  if (0) {
    ofstream ost {fname}; // if this file already existed, this will wype it clean
    if(!ost) error ("can not open output file ",fname);
    Chrono::Date date(2016, Chrono::Month::mar, 19);
    //Chrono::Date date; // we will try default constructor
    const int num_dates = 6;
    for (int i=0;i<num_dates; ++i){
      ost << date << " ";
      date.add_day(3);
    }
    ost.close();  // close the file to flus the data out
  }

  ifstream ist {fname};
  if(!ist) error ("can not open input file ",fname);
  ist.exceptions(ist.exceptions()|ios_base::badbit);

  cout<< "We are reading the values from the file "<< fname<<endl;
  for (Chrono::Date day; ist>>day; ) { // read until end of file
    // do something with day
    cout << day << "\t";
  }
  cout << endl;
  end_of_loop(ist,'|',"Bad termination of file"); // test if we can continue

  // carry on: we found the end of file or a terminator

  return 0;
}


