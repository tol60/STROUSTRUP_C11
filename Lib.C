/*
 * Lib.C
 *
 *  Created on: Nov 29, 2015
 *      Author: tony
 */

#include "Lib.h"

namespace Library {

  void Lib::add_a_book(const Book& b) // add a book
  {
    mBooks.push_back(b);
  }
  void Lib::add_a_patron(const Patron& p) // add a patron
  {
    mPatrons.push_back(p);
  }

  int Lib::find_book(const Book& b) // find an index of the Book in the mBook vector. In not found, return negative number.
  {
    int i=0;
    for (; i<mBooks.size(); ++i)
      if (mBooks[i]== b)
        return i; // return the index
    return -1; // signal a failure
  }

  int Lib::find_patron(const Patron& p) // find an index of the Patron in the mPatrons vector. In not found, return negative number.
  {
    int i=0;
    for (; i<mPatrons.size(); ++i)
      if (mPatrons[i]== p)
        return i; // return the index
    return -1; // signal a failure
  }


  void Lib::check_out_book(const Book&b, const Patron& p, Chrono::Date& transaction_date) // Check out the Book.
          // Make sure that Patron and the Book are in the Library. If they aren't report an error.
          // Then check to make sure that the user owes no fees. If the user does, report an error.
          // If not, create a Transaction, and place it in the vector of Transactions.
  {
    // make sure the book is in the library
    int ind_book = find_book(b);
    if (ind_book<0)
      error ("Book is not found in the library");

    Book & lib_book = mBooks[ind_book]; // reference to a book
    if ( !lib_book.get_checkin_status() )
      error("The book is checked out");

    // make sure the patron is in the library
    int ind_patron = find_patron(p);
    if (ind_patron<0)
      error ("Patron is not found in the library");

    Patron& lib_patron = mPatrons[ind_patron];
    // Then check to make sure that the user owes no fees. If the user does, report an error.
    if (lib_patron.is_fee_owned())
      error ("Patron owns the fee");

    // create a Transaction, and place it in the vector of Transactions
    lib_book.check_out(); // check out the book
    Transaction tr(lib_book, lib_patron, transaction_date);
    mTrans.push_back(tr); // record
  }
} /* namespace Library */
