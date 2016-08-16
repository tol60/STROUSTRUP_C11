/* Write the code to read structured file. More advanced file
 *
 * Example:
 * {year 1990}
 * {year 1991 {month jun}}
 * {year 1992 {month jan (1 0 61.5)} {month feb (1 1 64) (2 2 65.2)}}
 * {year 2000
 *  {month feb (1 1 68) (2 3 66.66) (1 0 67.2)}
 *  {month dec (15 15 -9.2) (15 14 -8.8) (14 0 -2)}
 * }
 *
 * Viewing the context of a Vector:
 *   print *(your_vector._M_impl._M_start)@your_vector_size
 * Viewing an element i [0,vector_size-1] of a vector
 *   print *(your_vector._M_impl._M_start + i)
 * From http://www.math-linux.com/c/faq-c/faq-c-stl/article/how-to-print-the-elements-of-a-c-std-vector-with-gnu-debugger-gdb
 *
 * As far as this example:
 * (gdb) p (month.day._M_impl._M_start+0)
 * $24 = (Day *) 0x6050e0
 * (gdb) p *(month.day._M_impl._M_start+0)
 * $25 = {hour = {<std::vector<double, std::allocator<double> >> = std::vector of length 24, capacity 24 = {-7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777}, <No data fields>}}
 *
 * (gdb) p (month.day._M_impl._M_start+0).hour
 * (gdb) p (month.day._M_impl._M_start+5).hour
 * $18 = {<std::vector<double, std::allocator<double> >> = std::vector of length 24, capacity 24 = {-7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777}, <No data fields>}
 *
 * (gdb) p *((month.day._M_impl._M_start+5).hour._M_impl._M_start+3)
 * $21 = -7777
 *
 * (gdb) p *((month.day._M_impl._M_start+5).hour._M_impl._M_start+3)@2
 * $22 = {-7777, -7777}
 *
 *
 * Note: the debugger does not check if you go over the limits (in this case 24)
 * (gdb) p *((month.day._M_impl._M_start+5).hour._M_impl._M_start+0)@24
 * $31 = {-7777 <repeats 24 times>}
 * (gdb) p *((month.day._M_impl._M_start+5).hour._M_impl._M_start+0)@25
 * $32 = {-7777 <repeats 24 times>, 0}
 * (gdb) p *((month.day._M_impl._M_start+5).hour._M_impl._M_start+0)@26
 * $33 = {-7777 <repeats 24 times>, 0, 1.0325971998082053e-321}
 *
 * (gdb) p bugday
 * $1 = {hour = {<std::vector<double, std::allocator<double> >> = std::vector of length 2, capacity 2 = {24, -7777}, <No data fields>}}
* (gdb) p day
 * $2 = {hour = {<std::vector<double, std::allocator<double> >> = std::vector of length 24, capacity 24 = {-7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777}, <No data fields>}}
 *
 * (gdb) p month.day
 * $3 = {<std::vector<Day, std::allocator<Day> >> = std::vector of length 32, capacity 32 = {{hour = {<std::vector<double, std::allocator<double> >> = std::vector of length 24, capacity 24 = {-7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777, -7777}, <No data fields>}}, {hour = {<std::vector<double, std::allocator<double> >> = std::vector of length 24, capacity 24 = {-77
 *
 * Debug Note:
 * I was getting
 * Segmentation fault (core dumped)
 * on the following line of code:
 *     Year y; // get a freshly initialized Year each time around
 *     if (!(ist>>y)) break;  // <= Segmentation fault
 *
 * The reason for the problem was that in
 *   istream& operator>>(istream& is, Year& y)
 * I forgot to put
 *   return is;
 *
 * The easy way to find it was to use -Wall optiong during compilation:
 * g++ -std=c++11 -g -Wall -o ch10.11.2_ReadStructuredFile.exe ch10.11.2_ReadStructuredFile.C     2>&1 | tee tmp.txt
 * ch10.11.2_ReadStructuredFile.C: In function ‘std::istream& operator>>(std::istream&, Year&)’:
 * ch10.11.2_ReadStructuredFile.C:230:1: warning: control reaches end of non-void function [-Wreturn-type]
 * }
 * ^
 *
 * Note:
 * Also, original version of the code requires a space after the month:
 * Example:
 * {year 1991 {month jun}} - will trip the code
 * {year 1991 {month jun }} - will work just fine
 *
 */
// g++ -std=c++11 -g -o ch10.11.2_ReadStructuredFile.exe ch10.11.2_ReadStructuredFile.C     2>&1 | tee tmp.txt

#include "std_lib_facilities.h"


const int not_a_reading = -7777; // less then absolute zero
const int not_a_month  = -1;

struct Day{
  vector<double> hour{vector<double>(24, not_a_reading)};
};

struct Month{ // a month of temerature readings
  int month {not_a_month}; // [0:11] January is 0
  vector<Day> day{32};      // [1:31] one vector reading per date.// we waste day[0] to keep the code simple
};

struct Year{
  int year; // positive = AD
  vector<Month> month{12};
};

//struct BugDay{
//  vector<double> hour{24, not_a_reading};  // this will create a vector of just 2 elements
//};

struct Reading{
  int day;
  int hour;
  double temperature;
};

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

constexpr int implausible_min = -200;
constexpr int implausible_max = 200;

bool is_valid(const Reading&r)
// a rough test for reading validity
{
  if ( r.day<1 || 31<r.day ) return false;
  if ( r.hour<0 || 23<r.hour ) return false;
  if ( r.temperature<implausible_min || implausible_max<r.temperature )
    return false;
  return true;
}

const vector<string> month_input_tbl = {
    "jan","feb","mar","apr","may","jun",
    "jul","aug","sep","oct","nov","dec"
};

int month_to_int(string s)
// is s the name of a month? If so return its index [0:11] otherwise -1
// Note: the simpler way to do this is to use map<string,int>
{
  for (int i=0;i<12; ++i) if (month_input_tbl[i]==s) return i;
  return -1;
}

const vector<string> month_print_tbl = {
    "January","February","March","April","May","June",
    "July","August","September","October","November","December"
};

string int_to_month(int i)
// months [0:11]
{
  if (i<0 || 12<=i) error("bad month index");
  return month_print_tbl[i];
}

istream& operator>>(istream& is, Reading& r)
// reading a temperature reading from is into r
// format: (3 4 9.7)
// check format, but don't bother with data validity
{
  char ch1;
  if (is>>ch1 && ch1!='(' ) { // could it be a Reading?
    is.unget();
    is.clear(ios_base::failbit);
    return is;
  }

  char ch2;
  int d;
  int h;
  double t;
  is >> d >> h >> t >>  ch2;
  if( !is || ch2!=')' ) error("bad reading"); // messed-up reading
  r.day = d;
  r.hour = h;
  r.temperature = t;
  return is;
}

istream& operator>> (istream& is, Month& m)
// read a month from is into m
// format: {month feb ...}
{
  char ch;
  if (is>>ch && ch!='{' ) {
    is.unget();
    is.clear(ios_base::failbit); // we failed to read a Month
    return is;
  }

  string month_marker;
  string mm;
  //is >> month_marker >> mm;  // jun}} will cause a fail
  is >> month_marker;

  is >>ch; // this will make sure that we don't trip on the previous space
  mm = string(1,ch);
  while (is.get(ch) && isalpha(ch)){
    mm += string(1,ch);  // hopefully
  }
  is.unget();

  if ( !is || month_marker!="month" ) error("bad start of month");
  m.month = month_to_int(mm);

  int duplicates = 0;
  int invalids = 0;
  for (Reading r; is>>r; ) {
    if( is_valid(r) ) {
      if( m.day[r.day].hour[r.hour] != not_a_reading)
        ++duplicates;
      m.day[r.day].hour[r.hour] = r.temperature;
    } else {
      ++invalids;
    }
  }
  if (invalids) error("invalid readings in month", invalids);
  if (duplicates) error("duplicate readings in month",duplicates);
  end_of_loop(is, '}', "bad end of month");

  return is;
}

istream& operator>>(istream& is, Year& y)
// read a year from is into y
// format: {year 1972 ...}
// Note: add the code to detect double month entry (throw an error)
{
  char ch = 0;
  is>> ch;
  if( ch!='{' ) {
    is.unget();
    is.clear(ios::failbit); // set failbit
    return is;
  }

  string year_marker;
  int yy;
  is >> year_marker >> yy;
  if ( !is || year_marker!="year") error ("bad start of year");
  y.year = yy;

  while(true) {
    Month m; // get a clean m each time around
    if (!(is>>m)) break;
    y.month[m.month] = m;
  }
  end_of_loop( is,'}', "bad end of year");
  return is;
}

//ostream& operator<< (ostream&, const Year& y);
void print_year(ostream& ost, const Year& year)
/* {year 2000
 *   {month feb (1 1 68) (2 3 66.66) (1 0 67.2)}
 *   {month dec (15 15 -9.2) (15 14 -8.8) (14 0 -2)}
 * }
*/
{
  ost << "{ year " << year.year << ' '; // { year 2000
  bool b_month_printed = false;
  for (const Month& m:year.month){
    // we have 12 months. But we might only have information on some of the months
    if (m.month!=not_a_month) {
      // print this month
      b_month_printed = true; // keep track if we had a least one month
      ost << "\n\t" << "{ month " << int_to_month(m.month) << " "; // "  { month February "
      for (int i=1; i<32; ++i) { // check all 31 days (entry zero was redundant to simplify the code)
        for (int j=0;j<24;++j) { //  check all 24 hour entries
          double tempr = m.day[i].hour[j];
          if (tempr!=not_a_reading) {
            // looks like we have a valid reading
            ost << '(' << i << ' ' << j << ' ' << tempr << ") ";
          }
        }
      }
      // at this point we checked all days/hours in a month. This particular month is done
      ost << '}';   // {month February (1 1 68) (2 3 66.66) (1 0 67.2)}
    }
  } // end for loop over 12 months
  if (b_month_printed) ost << endl;

  ost << '}' << endl; //{ year 2000 }

}


int main ()
{
  // open an input file:
  cout <<"Please enter input file name\n";
  string iname;
  cin >> iname;
  ifstream ist{iname};
  if(!ist) error("can not open input file",iname);

  ist.exceptions(ist.exceptions()|ios::badbit); // throw for bad()

  // open an output file:
  cout << "Please enter output file name\n";
  string oname;
  cin >> oname;
  ofstream ost{oname};
  if(!ost) error("can not open ouput file",oname);

  // read an arbitrary number of years:
  vector<Year> ys;
  while(true) {
    Year y; // get a freshly initialized Year each time around
    if (!(ist>>y)) break;
    //ist>> y;
    //if(!ist) break;
    ys.push_back(y);
  }

  cout << "read "<<ys.size() << " years of readings\n";
  for(Year& y:ys) print_year(ost,y);

  /*
  Day day;
  Month month;
  Year year;
  */
  // this will create a vector of just 2 elements
  // BugDay bugday;

  return 0;
}


