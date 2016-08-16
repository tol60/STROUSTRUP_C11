// This exercise and the next few require you to design and implement a Book class, such as you can imagine as part of software for a library.
/*
  Class Book should have members for the
  ISBN, title, author, and copyright date.
  Also store data on whether or not the book is checked out.
  Create functions for returning those data values.
  Create functions for checking a book in and out.
  Do simple validation on data entered into a Book; for example, accept ISBNs only of the form n-n-n-x
  where n is an integer and x is a digit or a letter. Store an ISBN as a string.

  excercise 6:
  Have the == operator check whether the ISBN numbers are the same for two books
  Have the != also compare the ISBN numbers.

  excercise 7:
  Create an enumerated type for the book class called Genre. Have the types be
  fiction, nonfiction, periodical, biography, and children.
  Give each book a Genre and make appropriate changes to the Book constructor and member functions.

  excercise 8:
  Create a Patron class for the library. The class will have a
  user's name, library card number, and library fees (if owed).
  Have functions that access this data, as well as a function to set the fee of the user.
  Have a helper function that returns a Boolean (bool) depending on whether or not the user owes a fee.

 */
// g++ -std=c++11 -g -o ch9.e.8_BookClass.exe ch9.e.8_BookClass.C Chrono.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

#include "Chrono.h"

class Patron {
public:
  Patron(const string& name, int CardNumber, double fee = 0.0);

  string get_name() const { return mName;}
  int get_CardNumber() const {return mCardNumber;}
  double get_fee() const {return mFee;}
  void set_fee(double fee) {mFee=fee;}
private:
  string mName;
  int mCardNumber;
  double mFee;
  bool is_fee_owned() {return mFee>0.0;}
};

Patron::Patron(const string& name, int CardNumber, double fee)
:mName{name},
 mCardNumber{CardNumber},
 mFee{fee}
 {}

ostream& operator << (ostream& os, const Patron& p){
  return os << "Name: " << p.get_name() << ", Card Number: " << p.get_CardNumber() << ", fee: " <<setprecision(2) << fixed << p.get_fee() << endl;
}

enum class Genre {
  fiction, nonfiction, periodical, biography, children
};

const vector <string> genre_tbl{"fiction", "nonfiction", "periodical", "biography", "children"};

ostream& operator <<(ostream& os, const Genre& g){
  return os << genre_tbl[int(g)];
  //return os << int(m);
}

class Book {
public:
  Book(const string& ISBN, const string& title, const string& author, const Chrono::Date& copyright_date, Genre genre); // Constructor, checks the book in
  string get_ISBN() const {return mISBN;}
  string get_title() const {return mTitle;}
  string get_author() const {return mAuthor;}
  Chrono::Date get_copyright_date() const {return mCopyright_date;}
  Genre get_genre() const {return mGenre;}
  bool get_checkin_status() const {return mChecked_in;}
  bool check_in(); // check the book in (returns false to indicate an attempt to check the book twice)
  bool check_out(); // check the book out (returns false to indicate an attempt to check out the book twice)
private:
  string mISBN;
  string mTitle;
  string mAuthor;
  Chrono::Date mCopyright_date;
  Genre mGenre;
  bool mChecked_in;
};

bool operator == (const Book& a, const Book& b){
  return a.get_ISBN() == b.get_ISBN();
}

bool operator != (const Book& a, const Book& b){
  return a.get_ISBN() != b.get_ISBN();
}

ostream& operator<<(ostream& os, const Book& b){
  os << "\tISBN-10: " << b.get_ISBN() << endl
      << "\tTitle: " << b.get_title() <<endl
      << "\tAuthor: " << b.get_author() << endl
      << "\tCopyright date: " << b.get_copyright_date() <<endl
      << "\tGenre: " << b.get_genre() << endl
      << "\tStatus: ";
  if (b.get_checkin_status())
    os << "Checked In" << endl;
  else
    os << "Checked Out" <<endl;
  return os;
}

Book::Book(const string& ISBN, const string& title, const string& author, const Chrono::Date& copyright_date, Genre genre) // Constructor, checks the book in
  :mISBN{ISBN},
   mTitle{title},
   mAuthor{author},
   mCopyright_date{copyright_date},
   mGenre{genre},
   mChecked_in{true} //checks the book in right away
{
  // Do simple validation on data entered into a Book; for example, accept ISBNs only of the form n-n-n-x
  // where n is an integer and x is a digit or a letter. Store an ISBN as a string.

  bool number_check = false; // will use as a flag to make sure there was at least one symbol between '-'
  int count = 0;

  string::iterator my_iter = mISBN.begin();
  for(; my_iter != mISBN.end(); ++my_iter)
  {
      //cout<<*my_iter;
    switch (*my_iter)
    {
    case '-':
      if (number_check) {
        number_check = false;  // prepare for the next n or x processing
        count++;  // we want to count n-n-n- till 3
        if (count == 3){
          // So far we confirmed n-n-n-

          ++my_iter;
          // n-n-n-x, make sure x -is a digit of a latter
          if (my_iter == mISBN.end()) // if we reached the end of the sting
            error ("ISBN construction failure");
          char ch = *my_iter;
          if ( (ch>='a' && ch <='z') || (ch>='A' && ch <='Z') || (ch >='0'&& ch <='9') )
          {
            // x was confirmed. Now we need to make sure there is no other characters.
            ++my_iter;
            if(my_iter != mISBN.end()) // for normal termination we expect to be at the end of the string at this point
              error ("error: ISBN number is too long. Constructor error");
            else
              return;  // this is a good termination
          }
        }
      } else { // number_check = false
        error ("error: ISBN constructor, a leading number is missing or double \'-\'");
      }
      break;
    case '1': case '2': case '3': case '4': case '5':
    case '6': case '7': case '8': case '9': case '0':
      number_check = true;
      break;
    default:
      error ("ISBN constructor error, unexpected character");
    } // end switch
  } // end for loop
  error ("ISBN constructor error, entry is too short");
}

bool Book::check_in() // check the book in (returns false to indicate an attempt to check the book twice)
{
  if (mChecked_in)
    return false; // signal an attempt to check the book in twice
  mChecked_in = true;
  return true; // signal normal termination
}

bool Book::check_out() // check the book out (returns false to indicate an attempt to check out the book twice)
{
  if (!mChecked_in) // already checked out
    return false; // signal an attempt to check the book out twice
  mChecked_in = false;
  return true; // signal normal termination
}

int main ()
{
  Chrono::Month mm {Chrono::Month::jan};
  cout << "mm = " << mm << endl;
  Chrono::Date today {2013,Chrono::Month::nov,9};
  cout << "Date = " << today << endl;
  // cout << "Enter a new date (yyyy,mm,dd)\n";
  // cin >> today;
  // cout << "Date = " << today << endl;

  string ISBN = "23-4567-012-X";
  string title = "Quincy the dog";
  string author = "Jason Crosby";
  Book bookA(ISBN,title,author,today,Genre::children);
  cout << "Book:\n" << bookA << endl;

  // ISBN = "23-4567-012-XX"; // error constructor is too long
  // ISBN = "23-4567-012-X "; // error constructor is too long (extra space)
  // ISBN = "23-4567-012X"; // error unexpected character
  // ISBN = "23-4567--012-X "; // error double --
  // ISBN = "-23-4567-0 "; // error
  //Book bookB(ISBN,title,author,today);

  cout << "Checking the book out" <<endl;
  bookA.check_out();
  cout << "Book:\n" << bookA << endl;

  Book bookB = bookA;

  cout << "Checking the book in" <<endl;
  bookA.check_in();
  cout << "Book:\n" << bookA << endl;

  cout << "Book B:\n" << bookB <<endl;
  if (bookB == bookA)
    cout << "Books A and B are the same\n";
  else
    cout << "Books A and B are different\n";

  ISBN = "2-999-12-X";
  title = "Quincy the cat";
  author = "Jason Crosby";
  Book bookC(ISBN,title,author,today,Genre::biography);

  cout << "Book C:\n" << bookC <<endl;
  if (bookC == bookA)
    cout << "Books A and C are the same\n";
  else
    cout << "Books A and C are different\n";

  string name = "Tony Blake";
  int card_num = 10001;
  double fee = 99923.06;
  Patron pat_A(name, card_num, fee);
  cout<<"Patron A: "<< pat_A << endl;

  Patron pat_B("Quincy Jones",10002);
  cout<<"Patron B: "<< pat_B << endl;

  return 0;
}


