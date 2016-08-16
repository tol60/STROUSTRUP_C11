// Calculator First attempt
// g++ -std=c++11 -g -o ch7.5_calc_trying_second_version_Modifications.exe ch7.5_calc_trying_second_version_Modifications.C  2>&1 | tee tmp.txt
// Started with ch6.7_calc_trying_second_version.C
// Modifications:
// Added '-' and '+' support to the primary()
// added '%' to term (via fmod from <cmath>) as x%y = x-y*int(x/y); 6.7%3.3=6.7-3.3*int(6.7/3.3) = 0.1
//    problem: 5%3*6 = (5%3)*6 = 12, but 5%(3*6) = 5

//
// This is example code from Chapter 6.7 "Trying the second version" of
// "Software - Principles and Practice using C++" by Bjarne Stroustrup
//

/*
  This file is known as calculator02buggy.cpp

  I have inserted 5 errors that should cause this not to compile
  I have inserted 3 logic errors that should cause the program to give wrong results

  First try to find an remove the bugs without looking in the book.
  If that gets tedious, compare the code to that in the book (or posted source code)

  Happy hunting!

*/

#include "./std_lib_facilities.h"

//---- Global constants ----
const char number = '8'; // t.kind==number means that it is a number Token
const char quit = 'q';  // t.kind==quit means that t is a quit Token
const char print = ';'; // t.kind==print means that t is a print Token

const char name = 'a';  // name token
const char let = 'L';   // declaration token
const string declkey = "let"; // declaration keyword

const string prompt_cap = ">";
const string result_cap = "="; // used to indicate that what follows is a result
const string quit_st(1,quit);  // generate a string from const car quit

//------------------------------------------------------------------------------
class Variable {
public:
  Variable();
  Variable(string var, double val);
  string name;
  double value;
};

Variable::Variable(): name(""), value(0)
{
}

Variable::Variable(string var, double val): name(var), value(val)
{
}


vector <Variable> var_table;

double get_value(string s)
// return the value of the Variable named s
{
  for (const Variable&v : var_table)
    if (v.name == s) return v.value;
  error("get:undefined variable ",s);
}

void set_value(string s, double d)
// set the Variable named s to d
{
  for (Variable& v: var_table)
    if (v.name==s){
      v.value = d;
      return;
    }
  error("set: undefined variable ",s);
}

bool is_declared(string var)
// is var already declared?
{
  for (const Variable& v:var_table)
    if(v.name==var) return true;
  return false;
}

double define_name(string var, double val)
// add (var, val) to var_table
{
  if(is_declared(var)) error(var, " declared twice");
  var_table.push_back(Variable(var,val));
  return val;
}

//------------------------------------------------------------------------------

class Token {
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value
    string name;
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) { }
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) { }
    Token(char ch, string n):kind{ch},name{n}{} // initialize kind and name
};

//------------------------------------------------------------------------------

class Token_stream {
public:
    Token_stream();   // make a Token_stream that reads from cin
    Token get();      // get a Token (get() is defined elsewhere)
    void putback(Token t);    // put a Token back
    void ignore(char c); // discard characters up to and including a c
private:
    bool full;        // is there a Token in the buffer?
    Token buffer;     // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
:full(false), buffer(0)    // no Token in buffer
{
}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

// The ingore member function discards charecters up to and including a c
void Token_stream::ignore(char c) // c repesents the kind of Token
{
  // fist look in bufffer:
  if (full && c==buffer.kind){
    full = false;
    return;
  }
  full = false;

  // now search input:
  char ch = 0;
  while (cin>>ch)
    if (ch==c) return;
}

//------------------------------------------------------------------------------

Token Token_stream::get()
{
    if (full) {       // do we already have a Token ready?
        // remove token from buffer
        full=false;
        return buffer;
    }

    char ch;
    cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
    case print:    // for "print" (;)
    case quit:    // for "quit" (q)
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '=': // new token we need to support for declaration let x = 4;
      return Token(ch);   // let each character represent itself
    case '.':             // a floating point literal can start with a dot
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':  // numeric literal
    {
      cin.putback(ch);         // put digit back into the input stream
      double val;
      cin >> val;              // read a floating-point number
      return Token(number,val);
    }
    default:
      if (isalpha(ch)){
        string s;
        s += ch;
        while (cin.get(ch)&&( isalpha(ch) || isdigit(ch) || ch == '_') ) s+=ch;
        cin.putback(ch);
        if (s==declkey) return Token(let);  // declaration keyword
        return Token(name,s);
      }
      string msg(1,ch);
      //error("Bad token",ch);
      error("Bad token ",msg);
    }
}

//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback()

//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()

//------------------------------------------------------------------------------

// deal with numbers and parentheses
double primary()
{
    Token t = ts.get();
    switch (t.kind) {
    case '(':    // handle '(' expression ')'
        {
            double d = expression();
            t = ts.get();
            if (t.kind != ')') error("')' expected");
            return d;
        }
    case number:
        return t.value;  // return the number's value
    case name:
      return get_value(t.name);
    case '-':
      return - primary();
    case '+':
      return  primary();
    case quit:
      error(quit_st);
    default:
      {
        string msg (1, t.kind);
        msg = msg + " , token name = " + t.name;
        error("primary expected, got token of type ", msg);
      }
    }
}

//------------------------------------------------------------------------------

// deal with *, /, and %
double term()
{
    double left = primary();
    Token t = ts.get();        // get the next token from token stream

    while(true) {
        switch (t.kind) {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
            {
                double d = primary();
                if (d == 0) error("divide by zero");
                left /= d;
                t = ts.get();
                break;
            }
        case '%':
        {
          double d = primary();
          if (d == 0) error("divide by zero");
          left = fmod(left,d); // x%y = x-y*int(x/y); 6.7%3.3=6.7-3.3*int(6.7/3.3) = 0.1
          t = ts.get();
          break;
        }
        case quit:
        {

          error( quit_st);
          break;
        }
        default:
            ts.putback(t);     // put t back into the token stream
            return left;
        }
    }
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
    double left = term();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while(true) {
        switch(t.kind) {
        case '+':
            left += term();    // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -= term();    // evaluate Term and subtract
            t = ts.get();
            break;
        default:
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}

double declaration()
// assume we have seen "let"
// handle: name = expression
// declare a variable called "name" the the initial value "expression"
{
  Token t = ts.get();
  if (t.kind!=name) error("name expected in declaration");
  string var_name = t.name;

  Token t2 = ts.get();
  if (t2.kind != '=') error ("= missing in declaration of", var_name);

  double d = expression();
  define_name(var_name,d);
  return d;
}

double statement()
{
  Token t=ts.get();
  switch (t.kind){
  case let:
    return declaration();
  default:
    ts.putback(t);
    return expression();
  }
}

void clean_up_mess()
{
  ts.ignore(print); // discard characters up to and including print
}

//------------------------------------------------------------------------------
void calculate()  // expression evaluation loop
{
  while (cin)
  try {
    cout << prompt_cap;
    Token t = ts.get();
    while (t.kind==print) t=ts.get(); // eat multiple print messages
    if (t.kind == quit) {
      return;
    }
    ts.putback(t);
    cout << result_cap << statement() << '\n';
  }
  catch (exception& e){
    cerr << e.what() << endl; // write error message
    clean_up_mess();
  }
}

//------------------------------------------------------------------------------

int main()
try
{
    cout << "Welcome to our simple calculator.\n";
    cout << "Please enter expression using floating-point numbers.\n";
    cout << "We support -, +, *, /, (, )\n";
    cout << "When you are done, type \""<<print<<"\", to exit type \""<<quit << "\"" <<endl;

    calculate();
    //keep_window_open(); // cope with Windows console mode (if needed)
    return 0;
}
catch (exception& e) {
    if (*e.what()==quit) {
      cout << "\nDetected request for early termination\n";
      return 0;
    }
    cerr << "error: " << e.what() << '\n';
    //keep_window_open();
    return 1;
}
catch (...) {
    cerr << "Oops: unknown exception!\n";
    //keep_window_open();
    return 2;
}

//------------------------------------------------------------------------------

