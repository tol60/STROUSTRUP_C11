/*
 * Book.C
 *
 *  Created on: Nov 29, 2015
 *      Author: tony
 */

#include "Book.h"

namespace Library {

// Genre
ostream& operator <<(ostream& os, const Genre& g){
  return os << genre_tbl[int(g)];
  //return os << int(m);
}

// Book
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

} /* namespace Library */
