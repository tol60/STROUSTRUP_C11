/*
 * Book.h
 *
 *  Created on: Nov 29, 2015
 *      Author: tony
 */

#ifndef BOOK_H_
#define BOOK_H_

#include "std_lib_facilities.h"

#include "Chrono.h"


namespace Library {

enum class Genre {
  fiction, nonfiction, periodical, biography, children
};

const vector <string> genre_tbl{"fiction", "nonfiction", "periodical", "biography", "children"};

ostream& operator <<(ostream& os, const Genre& g);


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

bool operator == (const Book& a, const Book& b);

bool operator != (const Book& a, const Book& b);

ostream& operator<<(ostream& os, const Book& b);

} /* namespace Library */

#endif /* BOOK_H_ */
