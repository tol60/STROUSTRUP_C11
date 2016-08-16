// Ex 15: Refine the Noney class by adding a currency (given as a constructor argument
/* Accept a floating-point initializer as long as it can be exactly represented as a long int.
 * Don't accept illegal operations. For example Money*Money doesn't make sense,
 * and USD1.23+DKK5.0 makes sense only if you provide a conversion table defining the conversion factor between U.S. dollars(USD) and Danish kroner DKK)
 *
 * ex 14:Design and implement a Money class.
 * for calculations involving dollars and cents where arithmetic has to be accurate to the last cent using the 4/5 rounding rule
 *  (0.5 cents rounds up, anything less than .5 rounds down). Represent a monetary amount as a number of cents in a long int,
 *  but input and output as dollars and cents, e.g., $123.45. Do not worry about amounts that don't fit into a long int.

 */
// g++ -std=c++11 -g ch9.e.15_MoneyClassCurrency.C  -o ch9.e.15_MoneyClassCurrency.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

enum class Currency {
  usd, dkk, pound, rub
};
const vector <string> currency_tbl{"$","dkk","pnd","rub"};
const vector <double> dollar_rate{1.0,1.5,0.8,67.43};

class Money {
public:
  Money (Currency cur, long int cent):mCurrency{cur},mCent{cent}{};
  Money (Currency cur, double cent);  // Accept a floating-point initializer as long as it can be exactly represented as a long int.
  Money (Currency cur, const Money& m ); // Convert to a new currency
  //Money(Currency cur, double dollar); // Accept a floating-point initializer as long as it can be exactly represented as a long int.
  Currency get_currency() const {return mCurrency;}
  long int get_cents() const {return mCent;}
  double get_dollars() const {return mCent/100.0;}
  double get_exchRate(Currency cur_from, Currency cure_to) const; // calculate the rate from to
private:
  long int mCent;
  Currency mCurrency;
};

double Money::get_exchRate(Currency cur_from, Currency cur_to) const // calculate an exchange rate from to
{
   return dollar_rate[int(cur_to)]/dollar_rate[int(cur_from)];
}
Money::Money (Currency cur, double cent)  // Accept a floating-point initializer as long as it can be exactly represented as a long int.
:mCurrency{cur},
 mCent{(long int) cent} // this should also do the rounding. But we still need to verify if we within the range.
{
  if (abs(mCent - cent) > 0) {
    // means the value can not be represented as long int, throw an error
    error("The value passed to the money constructor can not be represented as a long int");
  }
}

Money::Money (Currency cur, const Money& m )  // Convert to a new currency
:mCurrency{cur},
 mCent{m.get_cents()}
{
  if (mCurrency != m.get_currency()){
    // the conversion is necessary
    mCent *= get_exchRate(m.get_currency(), mCurrency);
  }

}
/*
Money::Money(Currency cur, double dollar) // Accept a floating-point initializer as long as it can be exactly represented as a long int.
  :mCurrency{cur},
   mCent{(long int) (dollar *100.0)} // this should also do the rounding. But we still need to verify if we within the range.
{
  if (abs(get_dollars() - dollar) >= 0.01) {
    // means the value can not be represented as long int, throw an error
    error("The value passed to the money constructor can not be represented as a long int");
  }
}
*/

ostream& operator <<(ostream& os, const Currency& cur){
  return os << currency_tbl[int(cur)];
}

ostream& operator <<(ostream& os, const Money & m){
  if(m.get_dollars()<0) { // don't forget about the possibility of negative amounts
    os << "-"<< m.get_currency()  << setfill('0') << fixed << setprecision(2) << -m.get_dollars();  // handle negatives
  } else {
    os << m.get_currency() << setfill('0') << fixed << setprecision(2) << m.get_dollars();
  }
  return os;
}

Money operator + (Money &a, Money &b)
{
  if (a.get_currency()!=b.get_currency()) {
    Money mon(a.get_currency(),b); // convert to the same currency as a
    return a+mon;
  }
  return Money{a.get_currency(),a.get_cents()+b.get_cents()};
}

Money operator - (Money &a, Money &b)
{
  if (a.get_currency()!=b.get_currency()) {
    Money mon(a.get_currency(),b); // convert to the same currency as a
    return a+mon;
  }
  return Money{a.get_currency(),a.get_cents()-b.get_cents()};
}

int main ()
{
  // vector <Money> wallet = {Money(Currency::dkk,1),Money(Currency::usd,10),Money(Currency::dkk,-20),Money(Currency::dkk,12), Money(Currency::dkk,133), Money(Currency::dkk,-777), Money(Currency::dkk,0), Money(Currency::dkk,-5), Money(Currency::dkk,19345)};

  Money A (Currency::usd,10.0);
  Money B (Currency::usd,(long int) 10);
  cout << "A = " << A << endl;
  cout << "B = " << B << endl;

  vector <Money> wallet = {Money(Currency::usd, (long int)10 ),Money(Currency::usd,10.0), Money(Currency::rub, (long int)10098 )};
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

  vector<Currency> currencyBasket = {Currency::usd, Currency::dkk, Currency::pound, Currency::rub};
  cout << "Exchange Rate:\n";
  // Print the Header of the table
  cout << "From:\\ To: ";
  for (auto cur_to:currencyBasket){
    cout << "\t" << cur_to;
  }
  cout << endl;

  for (auto cur_from:currencyBasket){
    cout << cur_from << "\t"; // new line
    for (auto cur_to:currencyBasket) {
      cout << "\t" << A.get_exchRate(cur_from, cur_to);
    }
    cout << endl;
  }
  cout << endl;

  for (int i=0; i<wallet.size(); ++i){
    cout << "\t wallet["<<i<<"] = "<< wallet[i] << endl;
    for (auto cur_to:currencyBasket) {
      Money mon(cur_to, wallet[i]);
      cout << "\t\t equivalent: " << mon<< endl;
    }

  }

  return 0;
}


