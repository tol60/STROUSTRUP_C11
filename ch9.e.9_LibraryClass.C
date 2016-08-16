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

  excercise 9:
  Create a Library class.
  Include vectors of Books and Patrons.
  Include a struct called Transaction.
  Have it include a Book, a Patron, and a Date from the chapter.
  Make a vector of Transactions.
  Create functions to add books to the library, add patrons to the library, and check out books.
  Whenever a user checks out a book, have the library make sure that both the user and the book are in the library. If they aren't report an error.
  Then check to make sure that the user owes no fees. If the user does, report an error.
  If not, create a Transaction, and place it in the vector of Transactions.
  Also write a function that will return a vector that contains the names of all Patrons who owe fees.

 */
// g++ -std=c++11 -g -o ch9.e.9_LibraryClass.exe ch9.e.9_LibraryClass.C Chrono.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

#include "Chrono.h"

class Patron {
public:
  Patron(const string& name, int CardNumber, double fee = 0.0);

  string get_name() const { return mName;}
  int get_CardNumber() const {return mCardNumber;}
  double get_fee() const {return mFee;}
  void set_fee(double fee) {mFee=fee;}
  bool is_fee_owned() const {return mFee>0.0;}
private:
  string mName;
  int mCardNumber;
  double mFee;
};

Patron::Patron(const string& name, int CardNumber, double fee)
:mName{name},
 mCardNumber{CardNumber},
 mFee{fee}
 {}

ostream& operator << (ostream& os, const Patron& p){
  return os << "Name: " << p.get_name() << ", Card Number: " << p.get_CardNumber() << ", fee: " <<setprecision(2) << fixed << p.get_fee() << endl;
}

bool operator == (const Patron& a, const Patron& b){
  return a.get_CardNumber() == b.get_CardNumber();
}

bool operator != (const Patron& a, const Patron& b){
  return a.get_CardNumber() != b.get_CardNumber();
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

struct LibTransaction{
  Book book;
  Patron patron;
  Chrono::Date date; // date of the transaction
  bool in_out; // if checking in in_out = true, if checking out then in_out = false;
  LibTransaction(const Book& book, const Patron& patron, const Chrono::Date& date, bool in_out):
    book{book},
    patron{patron},
    date{date},
    in_out{in_out}
    {}
};

ostream& operator<<(ostream& os, const LibTransaction& b){
  os << "\t Book:\n" << b.book << endl
      << "\t Patron:\n" << b.patron <<endl
      << "\t Transaction Date: " << b.date << endl
      << "\t Transaction Type: ";
  if (b.in_out)
    os << "Checking the book In" << endl;
  else
    os << "Checking the book Out" <<endl;
  return os;
}

class Library{
public:
  void add_book(const Book& book); // add a book to the library
  void add_patron(const Patron& patron); // add a patron to the library
  void check_InOut (const Book& book, const Patron& patron, const Chrono::Date& date, bool in_out); // if in_out == true, check the book in/ otherwise check the book out
  // Make sure that both Book and Patron are in the Library
  // Make sure that the Book is in the proper check in/ check_InOut state (matchin in_out), so we do not check out the book to two different patrons
  // Make sure that Patron does not own any fees
  // Create a transaction record

  // Debug functions
  void print_books(); // will print all the books in the library
  void print_patrons(); // will print all the patrons in the library
  void print_transactions(); // will print all the transactions in the library

  void get_fee_owned_patrons(vector<Patron>& owned_patrons); // generate a vector of patrons that owned

private:
  vector<Book> mBooks; // vector of Books
  vector<Patron> mPatrons; // Vector of Patrons
  vector<LibTransaction> mTransactions; // Vector of transactions
};

void Library::add_book(const Book& book) // add a book to the library
{
  // check if the book was already added to the library
  for (int i=0; i<mBooks.size(); i++){
    if (mBooks[i] == book) {
      cerr << "Library::add_book Error: The book already exists (don not support multiple books)\n";
      cerr << "book = " << book << endl;
      error("Trying to add a book that is already in the library") ;
    }
  }

  mBooks.push_back(book); // add the book to the library.
}

void Library::print_books() // will print all the books in the library
{
  for (int i=0; i<mBooks.size(); i++)
    cout << "book["<< i << "] is: \n" << mBooks[i] << endl;
}

void Library::add_patron(const Patron& patron) // add a patron to the library
{
  // check if the patron was already added to the library
  for (int i=0; i<mPatrons.size(); i++){
    if (mPatrons[i] == patron) {
      cerr << "Library::add_patron Error: The patron already exists (don not support multiple patrons)\n";
      cerr << "patron = " << patron << endl;
      error("Trying to add a patron that is already in the library") ;
    }
  }

  mPatrons.push_back(patron); // add the patron to the library.
}

void Library::print_patrons() // will print all the patrons in the library
{
  for (int i=0; i<mPatrons.size(); i++)
    cout << "patron["<< i << "] is: \n" << mPatrons[i] << endl;
}

void Library::check_InOut (const Book& book, const Patron& patron,const Chrono::Date& date, bool in_out) // if in_out == true, check the book in/ otherwise check the book out
// Make sure that both Book and Patron are in the Library
// Make sure that the Book is in the proper check in/ check_InOut state (matchin in_out), so we do not check out the book to two different patrons
// Make sure that Patron does not own any fees
// Create a transaction record (Book, Patron, Date, in_out)
{
  // check that the book was added to the library
  bool bookNotFound = true;
  int ind_book = -1; // need to preserve the index into book vector for later check_InOut
  for (int i=0; i<mBooks.size(); i++){
    if (mBooks[i]==book){
      bookNotFound = false; // record that we found the book.
      ind_book = i;
      // if book is already checked out and we are trying to check it out or
      // if book is already checked in and we are trying to check it in (the second time?) throw an error
      if(mBooks[i].get_checkin_status() == in_out){
        cerr << "book = " << mBooks[i] << endl;
        if (in_out)
          error("The book is already checked in");
        else
          error("The book is already checked out");
      }

      break; // break out of the for loop
    }
  }
  if (bookNotFound) {
    cerr << "Library::check_InOut Error: The book is not registered in the library \n";
    cerr << "book = " << book << endl;
    error("Book not found") ;
  }

  // check that the patron was added to the library
  bool patronNotFound = true;
  int ind_patron = -1; // need to preserve the index into Patron vector for later fee verification
  for (int i=0; i<mPatrons.size(); i++){
    if (mPatrons[i]==patron){
      patronNotFound = false; // record that we found the patron.
      ind_patron = i; //
      break;
    }
  }
  if (patronNotFound) {
    cerr << "Library::check_InOut Error: The patron is not registered in the library \n";
    cerr << "patron = " << patron << endl;
    error("Patron not found") ;
  }

  // Now check that the user owes no fees
  if ( mPatrons[ind_patron].is_fee_owned() ) // Make sure you are checking the Library version of the fee record!!. Otherwise we might check wrong fee!!
    error("The patron owes a fee");

  // Create a transaction record
  mTransactions.push_back(LibTransaction(mBooks[ind_book],mPatrons[ind_patron],date,in_out));

  // check the book in or out
  if (in_out) // if in_out == true, check the book in/ otherwise check the book out
    mBooks[ind_book].check_in();
  else
    mBooks[ind_book].check_out();

}

void Library::print_transactions() // will print all the transactions in the library
{
  for (int i=0; i<mTransactions.size(); i++)
    cout << "transaction["<< i << "] is: \n" << mTransactions[i] << endl;
}

void Library::get_fee_owned_patrons(vector<Patron>& owned_patrons) // generate a vector of patrons that owned
{
  owned_patrons.clear();
  for (int i=0; i<int(mPatrons.size()); i++){
    if (mPatrons[i].is_fee_owned())
      owned_patrons.push_back(mPatrons[i]);
  }
}

int main ()
{
  Chrono::Month mm {Chrono::Month::jan};
  cout << "mm = " << mm << endl;
  Chrono::Date today {2015,Chrono::Month::dec,30};
  Chrono::Date date_A {2013,Chrono::Month::nov,9};
  Chrono::Date date_B {2013,Chrono::Month::jan,31};
  cout << "Date today = " << today << endl;
  cout << "Date date_A = " << date_A << endl;
  cout << "Date date_B = " << date_B << endl;
  // cout << "Enter a new date (yyyy,mm,dd)\n";
  // cin >> today;
  // cout << "Date = " << today << endl;

  string ISBN = "23-4567-012-X";
  string title = "Quincy the dog";
  string author = "Jason Crosby";
  Book bookA(ISBN,title,author,date_A,Genre::children);
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
  Book bookC(ISBN,title,author,date_B,Genre::biography);

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

  fee = 23;
  Patron pat_C("Patron C",10003,fee);
  cout<<"Patron C: "<< pat_C << endl;

  Patron pat_D("Patron D",10004);
  cout<<"Patron D: "<< pat_D << endl;

  fee = 27.09;
  Patron pat_E("Patron E",10005,fee);
  cout<<"Patron E: "<< pat_E << endl;

  // Exercise 9 portion: Library
  cout << endl;
  cout<< "######################" << endl
      << "Testing Library Portion" << endl;

  // Library definition:
  Library bookLib;

  // add books to the library
  cout << "Adding books to the library\n";
  bookLib.add_book(bookA);
  //bookLib.add_book(bookB); // error, books A and B are the same. Can not add the same book twice (do not support muliple copies)
  bookLib.add_book(bookC);
  cout<<"The library contains the following books:\n";
  bookLib.print_books();

  // add patrons to the library
  cout << "Adding patrons to the library\n";
  bookLib.add_patron(pat_A);
  bookLib.add_patron(pat_B);
  bookLib.add_patron(pat_C);
  bookLib.add_patron(pat_D);
  bookLib.add_patron(pat_E);
  cout<<"The library contains the following patrons:\n";
  bookLib.print_patrons();

  // Checking book out
  bookLib.check_InOut(bookA,pat_B,today,false); // checking the book out
  //bookLib.check_InOut(bookB,pat_B,today,false); // error: bookB = bookA. book was already checked out // checking the book out

  bookLib.check_InOut(bookA,pat_B,today,true);
  bookLib.check_InOut(bookB,pat_B,today,false);

  // bookLib.check_InOut(bookC,pat_A,today,false); // error: patron has a fee
  cout<<"The library contains the following transactions:\n";
  bookLib.print_transactions();

  cout << endl;
  cout<< "######################" << endl
      << "Patrons that have a fee" << endl;
  vector<Patron> owe_fees;
  bookLib.get_fee_owned_patrons(owe_fees);
  for (int i=0;i<owe_fees.size();i++){
    cout << "Patron["<< i <<"]:\n"
        << owe_fees[i];
  }

  return 0;
}


