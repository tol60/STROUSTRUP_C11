// Design and implement a Money class.
/* for calculations involving dollars and cents where arithmetic has to be accurate to the last cent using the 4/5 rounding rule
 *  (0.5 cents rounds up, anything less than .5 rounds down). Represent a monetary amount as a number of cents in a long int,
 *  but input and output as dollars and cents, e.g., $123.45. Do not worry about amounts that don't fit into a long int.

 */
// g++ -std=c++11 -g ch9.e.14_MoneyClass.C  -o ch9.e.14_MoneyClass.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"


class Money {
public:
  Money (long int cent):mCent{cent}{};
  long int get_cents() const {return mCent;}
  double get_dollars() const {return mCent/100.0;}
private:
  long int mCent;
};

ostream& operator <<(ostream& os, const Money & m){
  if(m.get_dollars()<0) { // don't forget about the possibility of negative amounts
    os << "-$" << setfill('0') << fixed << setprecision(2) << -m.get_dollars();  // handle negatives
  } else {
    os << "$" << setfill('0') << fixed << setprecision(2) << m.get_dollars();
  }
  return os;
}

Money operator + (Money &a, Money &b)
{
  return Money{a.get_cents()+b.get_cents()};
}

Money operator - (Money &a, Money &b)
{
  return Money{a.get_cents()-b.get_cents()};
}

int main ()
{
  vector <Money> wallet = {Money(1),Money(10),Money(-20),Money(12), Money(133), Money(-777), Money(0), Money(-5), Money(19345)};
  for (int i=0; i<wallet.size(); ++i){
    cout << "\t wallet["<<i<<"] = "<< wallet[i] << endl;
  }
  cout << endl;

  for (auto a:wallet){
    for (auto b:wallet){
      cout << "\t" << a << " + " << b << " = " << a+b << endl;
      cout << "\t" << a << " - " << b << " = " << a-b << endl;
    }
  }

  return 0;
}


