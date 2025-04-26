/*
 * Lib.h
 *
  ch9 excercise 9:
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

#ifndef LIB_H_
#define LIB_H_
#include "std_lib_facilities.h"

#include "Book.h"
#include "Patron.h"

namespace Library {

class Lib {
public:
  struct Transaction{
    Book mBook;             // book
    Patron mPatron;         // patron
    Chrono::Date mTransDate;// date of transaction
    Transaction(const Book& book, const Patron& patron, const Chrono::Date& date)
    :mBook{book},
     mPatron{patron},
     mTransDate{date}
     {}
  };
  void add_a_book(const Book& b); // add a book
  void add_a_patron(const Patron& p); // add a patron
  void check_out_book(const Book&b, const Patron& p, Chrono::Date& transaction_date); // Check out the Book.
          // Make sure that Patron and the Book are in the Library. If they aren't report an error.
          // Then check to make sure that the user owes no fees. If the user does, report an error.
          // If not, create a Transaction, and place it in the vector of Transactions.
  void check_in_book(const Book&b, const Patron& p, Chrono::Date& transaction_date); // check in the Book.
          // Make sure that Patron and the Book are in the Library. If they aren't report an error.
          // create a Transaction, and place it in the vector of Transactions.
private:
  vector<Book> mBooks;        // available books
  vector<Patron> mPatrons;    // all the Patrons
  vector<Transaction> mTrans; // all the transactions

  int find_book(const Book& b); // find an index of the Book in the mBook vector. In not found, return negative number.
  int find_patron(const Patron& p); // find an index of the Patron in the mPatrons vector. In not found, return negative number.
};

} /* namespace Library */

#endif /* LIB_H_ */
