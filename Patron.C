/*
 * Patron.C
 *
 *  Created on: Nov 29, 2015
 *      Author: tony
 */

#include "Patron.h"

namespace Library {
Patron::Patron(const string& name, int CardNumber, double fee)
:mName{name},
 mCardNumber{CardNumber},
 mFee{fee}
 {}

ostream& operator << (ostream& os, const Patron& p){
  return os << "Name: " << p.get_name() << ", Card Number: " << p.get_CardNumber() << ", fee: " <<setprecision(2) << fixed << p.get_fee() << endl;
}
} /* namespace Library */
