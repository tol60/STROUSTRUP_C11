// g++ -std=c++11 -g -o ch7.d.2.calculator08buggy_comments.exe ch7.d.2.calculator08buggy_comments.C  2>&1 | tee tmp.txt
// Original calculator08buggy.cpp

/*
  calculator08buggy.cpp

  Adding comments.
  Bugs were already fixed.
*/

/*
  Simple calculator.
  Supports:
    variables (let var_name = value;)
    functions:
      sqrt();
      pow(x,i) //where i is integer
  The grammar:
  Calculate:
    Print (;)
    Quit  (Q)
    Statement

  Statement:
    Declaration
    Expression

  Declaration
    "let" var_name "=" Expression

  Expression
    Term
    Term + Term
    Term - Term

  Term
    Primary
    Primary * Primary
    Primary / Primary
    Primary % Primary

  Primary
    Number
    ( Expression)
    Variable
    Function ( Expression)
    - Primary
    + Primary

    Number
      floating-point-literal

    Function
      sqrt(x);
      pow(x,i); // i is integer

   Input comes from cin through the Token_stream called ts
 */

/*
 Note:
   set_value - is never used in the code (so bound bug can never be caught
 */

#include "std_lib_facilities.h"

struct Token {
  char kind;
  double value;
  string name;
  Token(char ch) :kind(ch), value(0) { }                // Extra literals
  Token(char ch, double val) :kind(ch), value(val) { }  // Number
  Token(char ch, string s) :kind(ch), name(s) { }       // initialize token for variable // problem01
};

class Token_stream {
  bool full;
  Token buffer;
public:
  Token_stream() :full(0), buffer(0) { }

  Token get();
  void unget(Token t) { buffer=t; full=true; } // put a token back onto the stream

  void ignore(char); // discard characters up to and including a c
};

//---- Global constants ----
const char let = 'L';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';

const string prompt = "> ";
const string result = "= ";

Token Token_stream::get()
{
  if (full) { full=false; return buffer; } // do we already have a Token ready?
  char ch;
  cin >> ch;
  switch (ch) {
  case '(':
  case ')':
  case '+':
  case '-':
  case '*':
  case '/':
  case '%':
  case ',': // for pow(x,i)
  case print:
  case quit:  // problem08 - there was no entry for quit token. Fixed
  case '=':
    return Token(ch); // let each character represent itself
  case '.': // a floating point literal can start with a dot
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
  { cin.unget(); // put digit back into the input stream
    double val;
    cin >> val;
    return Token(number,val); // read a floating point number
  }
  default:
    if (isalpha(ch)) {
      string s;
      s += ch;
      while(cin.get(ch) && (isalpha(ch) || isdigit(ch))) s+=ch;  // problem02 += was missing. need variable of more then one letter to catch
      cin.unget();
      if (s == "let") return Token(let);
      if (s == "quit") return Token(name);
      return Token(name,s);  // return declaration keyword
    }
    string msg(1,ch);
    error("Bad token ",msg);
  }
}

// discard characters up to and including a c
void Token_stream::ignore(char c)
{
  // fist look in bufffer:
  if (full && c==buffer.kind) {
    full = false;
    return;
  }
  full = false;

  // now look at the input
  char ch;
  while (cin>>ch)
    if (ch==c) return;
}

struct Variable {
  string name;
  double value;
  Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> names;   // store the values of user defined variables here

// retrieve the value of user -defined variable
double get_value(string s)
{
  for (int i = 0; i<names.size(); ++i)
    if (names[i].name == s) return names[i].value;
  error("get: undefined name ",s);
}

// assign user-defined variable a value
void set_value(string s, double d)
{
  //for (int i = 0; i<=names.size(); ++i) // problem03 go out of bounds
  for (int i = 0; i<names.size(); ++i)
    if (names[i].name == s) {
      names[i].value = d;
      return;
    }
  error("set: undefined name ",s);
}

// check if the variable has been declared (to avoid redefining a variable caused by a typo)
bool is_declared(string s)
{
  for (int i = 0; i<names.size(); ++i)
    if (names[i].name == s) return true;
  return false;
}

double define_name(string var, double val)
// add (var, val) to names
{
  if(is_declared(var)) error(var, " declared twice, =" + to_string( get_value(var) )  );
  names.push_back(Variable(var,val));
  return val;
}

Token_stream ts;

double expression();

double primary()
{
  Token t = ts.get();
  switch (t.kind) {
  case '(':   // handle ( Expression )
  { double d = expression();
    t = ts.get();
    //if (t.kind != ')') error("'(' expected"); // problem05
    if (t.kind != ')') error("')' expected");
    return d;  // problem07 return was missing (1); would catch it
  }
  case '-':
    return - primary();
  case '+':
    return primary(); // problem06 did not handle + sign +2-3;
  case number:  // hanlder Numbers
    return t.value;
  case name:  // handle Variables and functions
    if (t.name == "sqrt") { // sqrt ( Expression ) function
      t = ts.get();  // expect '('
      if (t.kind != '(') error("sqrt function call, expected '('");
      double d = expression();
      if (d < 0) error("Attempt to take sqrt of a negative number " + to_string(d));
      t = ts.get(); // expect ')'
      if (t.kind != ')') error("sqrt function call, expected ')'");
      return sqrt(d);
    } else if (t.name == "pow") { // pow(x, i) function
      t = ts.get();  // expect '('
      if (t.kind != '(') error("pow function call, expected '('");
      double d = expression();
      // if (d < 0) error("Attempt to take pow of a negative number " + to_string(d));
      t = ts.get(); // expect ','
      if (t.kind != ',') error ("pow function call, after the first parameter expect ','");
      double w = expression ();
      //int i2 = narrow_cast<int> (w);  // cast to int
      t = ts.get(); // expect ')'
      if (t.kind != ')') error("pow function call, expected ')'");
      return pow(d,w);
    } else  // variable
      return get_value(t.name);
  default:
  {
    string msg (1, t.kind);
    msg = msg + " , token name = " + t.name;
    error("primary expected, got token of type ", msg);
  }
  }
}

double term()
{
  double left = primary();
  while(true) {
    Token t = ts.get();  // get the next Token from the stream
    switch(t.kind) {
    case '*':
      left *= primary();
      break;
    case '/':
    { double d = primary();
      if (d == 0) error("divide by zero");
      left /= d;
      break;
    }
    default:
      ts.unget(t);  // put the Token back onto the stream (we did not do any action here)
      return left;
    }
  }
}

double expression()
{  // deal we A+B and A-B
  double left = term();
  while(true) {
    Token t = ts.get(); // get the next Token from the stream
    switch(t.kind) {
    case '+':
      left += term();
      break;
    case '-':
      left -= term();
      break;
    default:
      ts.unget(t); // put the Token back onto the stream (we did not do any action here)
      return left;
    }
  }
}

double declaration()
// "let" var_name "=" Expression
{
  Token t = ts.get();
  if (t.kind != 'a') error ("name expected in declaration");
  string name = t.name;
  if (is_declared(name)) error(name, " declared twice");
  Token t2 = ts.get();
  if (t2.kind != '=') error("= missing in declaration of " ,name);
  double d = expression();
  names.push_back(Variable(name,d));
  return d;
}

double statement()
{
  Token t = ts.get();
  switch(t.kind) {
  case let:
    return declaration();
  default:
    ts.unget(t);
    return expression();
  }
}

// discard cin content up to the first print symbol
void clean_up_mess()
{
  ts.ignore(print);
}

void calculate()
{
  while(true) try {
    cout << prompt;
    Token t = ts.get();
    while (t.kind == print) t=ts.get();
    if (t.kind == quit) return;
    ts.unget(t);
    cout << result << statement() << endl;
  }
  catch(runtime_error& e) {
    cerr << e.what() << endl;
    clean_up_mess();
  }
}

int main()

  try {
    // predefine names:
    define_name("pi",3.1415926535);
    define_name("e", 2.7182818284);

    calculate();
    return 0;
  }
  catch (exception& e) {
    cerr << "exception: " << e.what() << endl;
    char c;
    while (cin >>c&& c!=';') ;
    return 1;
  }
  catch (...) {
    cerr << "exception\n";
    char c;
    while (cin>>c && c!=';');
    return 2;
  }
