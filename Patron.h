/*
 * Patron.h
 *
 *  Created on: Nov 29, 2015
 *      Author: tony
 */

#ifndef PATRON_H_
#define PATRON_H_

#include "std_lib_facilities.h"

namespace Library {


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

ostream& operator << (ostream& os, const Patron& p);

} /* namespace Library */

#endif /* PATRON_H_ */
