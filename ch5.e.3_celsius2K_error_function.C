// Convert Celcius to Kelvin Check for input errors in the function
// g++ -std=c++11 -g -o ch5.e.3_celsius2K_error_function.exe ch5.e.3_celsius2K_error_function.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

constexpr double abs_zero = -273.15;

// convert Celcius to Kelvin
// throws exception if we below absolut min
double ctok(double c)
{
  if (c< abs_zero) {
    error ("Bad argument for ctok. Input less then absolute zero");
  }
  double k = c - abs_zero;
  return k;
}

double ktoc (double k)
{
  if (k<0) {
    error ("Bad argument for ktoc. Input less then zero");
  }
  double c = k + abs_zero;
  return c;
}

int main ()
{
  double temp = 0;
  cout << "Please enter the temperature in Celcius or Kelvin: 23C or 35K \n";
  char unit = ' ';
  cin >> temp >> unit;
  if (cin) {
    try {
      double output = 0;
      switch (unit) {
      case 'C': case 'c':
        cout << "You entered " << temp << " degrees Celcius\n";
        output= ctok(temp);
        cout << "Is equivalent to "<< output << " degrees Kelvin\n";
        break;
      case 'K': case 'k':
        cout << "You entered " << temp << " degrees Kelvin\n";
        output = ktoc(temp);
        cout << "Is equivalent to "<< output << " degrees Celcius\n";
        break;
      default:
        cout << "Sorry, I did not recognize the unit " << unit << endl;
        break;
      }
    }
    catch (exception& e) {
      cerr << "error: " << e.what() << endl;
      return 1;
    }
    catch (...) {
      cerr << "Oops: unknown exception!\n";
      return 2;
    }
  } else {
    cout << "You input was not recognized\n";
  }
  return 0;
}


