//
/* Ex14. Write a program that reads a text file and writes out how many characters of eachcharacter classification ($11.6) are in the file.
 */
// g++ -std=c++11 -g ch11.e.14_file_char_classification.C  -o ch11.e.14_file_char_classification.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

enum class CharCount{plain_cnt,space,alpha,digit,xdigit,upper,lower,alnum,cntrl,punct,print,graph,end}; // the last CharCount::end is for the loops
vector<string> CharCount_tbl = {"plain_cnt","white space","alpha","digit","xdigit","upper","lower","alnum","cntrl","punct","print","graph","end"};
ostream& operator << (ostream& os, CharCount cc)
{
  return os <<CharCount_tbl[int(cc)];
}
CharCount operator++(CharCount& cc){  // prefix increment operator
  cc = (cc==CharCount::end)? CharCount::plain_cnt : CharCount(int(cc)+1); // "wrap around"
  return cc;
}

void CntUpdate(char ch, vector<int> & cnt_v){
  cnt_v[int(CharCount::plain_cnt)]++; // increment plain counter (total number of characters)
  if (isspace(ch))
    cnt_v[int(CharCount::space)]++;
  if (isalpha(ch))
    cnt_v[int(CharCount::alpha)]++;
  if (isdigit(ch))
    cnt_v[int(CharCount::digit)]++;
  if (isxdigit(ch))
    cnt_v[int(CharCount::xdigit)]++;
  if (isupper(ch))
    cnt_v[int(CharCount::upper)]++;
  if (islower(ch))
    cnt_v[int(CharCount::lower)]++;
  if (isalnum(ch))
    cnt_v[int(CharCount::alnum)]++;
  if (iscntrl(ch))
    cnt_v[int(CharCount::cntrl)]++;
  if (ispunct(ch))
    cnt_v[int(CharCount::punct)]++;
  if (isprint(ch))
    cnt_v[int(CharCount::print)]++;
  if (isgraph(ch))
    cnt_v[int(CharCount::graph)]++;
}


int main ()
{
  cout << "The program will reverse the order of words in a string from a text file"<< endl;
  cout << "Please enter input file name:\n";
  string iname;
  cin >> iname;
  ifstream ifs(iname); // text file
  if (!ifs) error ("can't open input file", iname);

  vector<int> cnt_v;  // initialize the counter vector
  for(CharCount cc=CharCount::plain_cnt; cc<CharCount::end; ++cc ){
    cnt_v.push_back(0);
  }

  // read in the file and update counts
  for (char ch; ifs.get(ch); ){
    CntUpdate(ch,cnt_v);
  }

  // print out the results:
  cout<< "Totals:" << endl;
  for(CharCount cc=CharCount::plain_cnt; cc<CharCount::end; ++cc ){
    cout << '\t' << cc << ": " << cnt_v[int(cc)]<<endl;
  }

  return 0;
}


