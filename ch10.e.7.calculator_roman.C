// g++ -std=c++11 -g -o ch10.e.7.calculator_roman.exe ch10.e.7.calculator_roman.C Roman.C 2>&1 | tee tmp.txt
/* Changes:
 * Include Roman::Roman_int
 *   statement(): return Roman::Roman_int ->statementRoman()
 *   Token Token_stream::get(): Allow Roman numerals: 'M','D','C','L','X','V','I'
 *
 */


// Previous version ch7.e.7.calculator08buggy_fixed.C
// Original calculator08buggy.cpp

/* Change log
  calculator08buggy.cpp

  Adding comments.
  Bugs were already fixed.
  E1. Allow underscores in the calculator's variable names.
  E2. Provide an assignment operator, =, so that you can change the value of a variable after you introduce it using let
  E3. Provide named constants that you really can't change the value of (add a member to Variable  that
      distinguishes between constants and variables and check for it in set_value(). Notation const pi=3.14;
  E4. The get_value(), set_value(), is_declared() and define_name() functions all operate on the variable var_table.
      Define a class called Symbol_table with a member names of type vector<Variable> and
      member functions get(),set(),is_declared() and declare().
      Rewrite the calculator to use a variable of type Symbol_table.
  E5. Modify Token_stream::get() to return Token(print) when it sees a new line.
      This implies looking for whitespace characters and treating newline ('\n') specially.
      You might find the standard library function isspace(ch), which returns true if ch is a whitespace character, useful
      Note:
        We need to add similar fix to Token_stream::ignore()
  E6. Have the calculator print out some instructions for how to use the calculator if the user presses H key (both upper- and lowercase).
  E7. Change the q and h commands to be quit and help respectively

*/

/*
  Simple calculator.
  Supports:
    variables (let var_name = value;)
    constants (const var_name = value;) // E3
    functions:
      sqrt();
      pow(x,i); //where i is real number
  The grammar:
  Calculate:
    Print (;)
    Quit  (Q)
    Statement
    Statement ; Statement

  Statement:
    Declaration
    Declaration_Const
    Assignment
    Expression

  Declaration
    "let" var_name "=" Expression

  Declaration_Const
    "const" var_name "=" Expression (can overwrite previously declared variable, like const)

  Assignment
    var_name "=" Expression

  Expression
    Term
    Term + Term
    Term - Term

  Term
    Primary
    Primary * Primary
    Primary / Primary

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
#include "Roman.h"

struct Token {
  char kind;
  double value;
  string name;
  Token(char ch) :kind(ch), value(0) { }                // Extra literals
  Token(char ch, double val) :kind(ch), value(val) { }  // Number
  Token(char ch, string s) :kind(ch), name(s),value(0) { }       // initialize token for variable // problem01
};

class Token_stream {
  bool full;
  Token buffer;
public:
  Token_stream() :full(0), buffer(0) { }

  Token get();
  void unget(Token t) { buffer=t; full=true; } // put a token back onto the stream

  void ignore(char); // discard characters up to and including a c
                       // Also treat new line as the print as part of  E5. Modify Token_stream::get() to return Token(print) when it sees a new line.
};

//---- Global constants ----
const char let = 'L';
const char con = 'C';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char help = 'H'; // this token will indicate user requested the help

const string prompt = "> ";
const string result = "= ";

const string quit_str = "q"; // string that will be used to quit the calculator
const string let_str = "let"; // string used to denote variables
const string const_str = "const"; // string used to denote constants
const string help_str = "H"; // string that will be used for user to request help (upper or lower case)

string upper_str (const string &s) // put into upper case
{
  string str;
  for (const char& x:s) str += toupper(x);
  return str;
}

void print_help(){
  cout << "  Simple calculator.\n";
  cout << "    For help enter "<<help_str <<" (upper or lower case)\n";
  cout << "    To quit enter "<<quit_str <<"\n";
  cout << "  Supports:\n";
  cout << "    variables (" <<let_str<<" var_name = value;)\n";
  cout << "    constants (" <<const_str<<" var_name = value;)\n"; // E3
  cout << "    functions:\n";
  cout << "      sqrt();\n";
  cout << "     pow(x,i); \n";
}

Token Token_stream::get()
{
  if (full) { full=false; return buffer; } // do we already have a Token ready?
  char ch;
  //  E5. Modify Token_stream::get() to return Token(print) when it sees a new line.
  // cin >> ch; // note that >> skips whitespace (space, newline, tab, etc.)
  // cin.getchar(ch); // Extracts characters from the stream, as unformatted input (includes white spaces, like '\n')
  while (cin.get(ch) && isspace(ch)) { // skip through whitespaces, but check for
    if (ch == '\n') return Token(print);
  }
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
  // case quit:  // problem08 - there was no entry for quit token. Fixed <== Wrong!
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
  case 'M': // Roman Numerals
  case 'D':
  case 'C':
  case 'L':
  case 'X':
  case 'V':
  case 'I':
  { cin.unget(); // put digit back into the input stream
    Roman::Roman_int val;
    cin >> val;
    return Token(number,val.as_int()); // Roman integer, convert to int
  }
  default:
    if (isalpha(ch)) {
      string s;
      s += ch;
      while(cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch=='_')) s+=ch;  // problem02 += was missing. need variable of more then one letter to catch
      cin.unget();
      if (s == let_str) return Token(let); // "let"
      if (s == const_str) return Token(con); // "const"
      if (s == quit_str) return Token(quit);  // "Q" for "quit" // Problem08 <= real one
      if (upper_str(s) == help_str) return Token(help); //user has requested help
      return Token(name,s);  // return variable name
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

  // Also treat new line as a print symbol as part of  E5. Modify Token_stream::get() to return Token(print) when it sees a new line.
  if (c != print) { // not a print symbol, original loop
    while (cin>>ch)  // note that >> skips whitespace (space, newline, tab, etc.)
      if (ch==c) return;
  } else {          // ignoring print. two options: print symbol and end of line
    while (cin.get(ch)) // Extracts characters from the stream, as unformatted input (includes white spaces, like '\n')
      if (ch==print || ch=='\n') return;
  }
}

struct Variable {
  string name;
  double value;
  bool constant;
  Variable(string n, double v, bool constant = false) :name(n), value(v), constant(constant) { }
};

// vector<Variable> names;   // store the values of user defined variables here

class Symbol_table {
public:
  Symbol_table(){var_table.clear();} // constructor
  double get(string s);         // retrieve the value of user-defined variable (or constant)
  void set(string s, double d); // assign user-defined variable a value
  bool is_declared(string s);   // check if the variable has been declared (to avoid redefining a variable caused by a typo)
  double declare(string var, double val, bool constant=false); // define a new variable (constant if constant=true) and assign it a new value
          // if the variable was defined, through an error. We can redefine a variable into a constant
private:
  vector <Variable> var_table;
};

Symbol_table STable;  // this object will contain all the information about the variables (in place of vector<Variable> names;

// retrieve the value of user-defined variable (or constant)
double Symbol_table::get(string s) {
  for (int i = 0; i<var_table.size(); ++i)
    if (var_table[i].name == s) return var_table[i].value;
  error("get: undefined name ",s);
}

// retrieve the value of user -defined variable
/*
double get_value(string s)
{
  for (int i = 0; i<names.size(); ++i)
    if (names[i].name == s) return names[i].value;
  error("get: undefined name ",s);
}
*/

// assign user-defined variable a value
void Symbol_table::set(string s, double d) {
  for (int i = 0; i<var_table.size(); ++i)
    if (var_table[i].name == s) {
      if (var_table[i].constant) error("can not modify constant ",s);
      var_table[i].value = d;
      return;
    }
  error("set_value: undefined name ",s);
}

// assign user-defined variable a value
/*
void set_value(string s, double d)
{
  //for (int i = 0; i<=names.size(); ++i) // problem03 go out of bounds
  for (int i = 0; i<names.size(); ++i)
    if (names[i].name == s) {
      if (names[i].constant) error("can not modify constant ",s);
      names[i].value = d;
      return;
    }
  error("set_value: undefined name ",s);
}
*/

// check if the variable has been declared (to avoid redefining a variable caused by a typo)
bool Symbol_table::is_declared(string s)
{
  for (int i = 0; i<var_table.size(); ++i)
    if (var_table[i].name == s) return true;
  return false;
}

// check if the variable has been declared (to avoid redefining a variable caused by a typo)
/*bool is_declared(string s)
{
  for (int i = 0; i<names.size(); ++i)
    if (names[i].name == s) return true;
  return false;
}
*/

// define a new variable (constant if constant=true) and assign it a new value
//     if the variable was defined, through an error. We can redefine a variable into a constant
// double Symbol_table::declare(string name, double val, bool constant=false)
double Symbol_table::declare(string name, double val, bool constant)
{
  // see if the variable (or constant) has already been defined, and if it has, get the index
  int indx=-1;
  for (int i = 0; i<var_table.size(); ++i){
    if (var_table[i].name == name) {
      indx = i; // we need to get this index out of the loop
      break;
    }
  }

  // treat differently based on weather the variable has been defined before
  if (indx >= 0 ) { // it appears that a variable with this name has already been defined
    if (var_table[indx].constant) error ("trying to redefine previously defined constant"); // old variable was marked as constant
    if (!constant) error ("trying to redefine previously defined variable"); // old variable, new variable, user can simply do assignment
    // remaining case: old variable, new constant: we can redefine a variable (so that user can redefine the constant that calculator has declared)
    var_table[indx].constant = true;  // redefine variable as a const
    var_table[indx].value = val;      // assign a new value
  } else { // brand new variable
    var_table.push_back(Variable(name,val,constant)); // add a new element (and mark it as a variable or constant as user has requested
  }

  return val;
}

/*double define_name(string var, double val)
// add (var, val) to names
{
  if(is_declared(var)) error(var, " declared twice, =" + to_string( get_value(var) )  );
  names.push_back(Variable(var,val));
  return val;
}
*/

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
      return STable.get(t.name); //get_value(t.name);
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
    case '%':
    {
      double d = primary();
      if (d == 0) error("divide by zero");
      left = fmod(left,d); // x%y = x-y*int(x/y); 6.7%3.3=6.7-3.3*int(6.7/3.3) = 0.1
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
  if (t.kind != name) error ("name expected in declaration");
  string name = t.name;
  if (STable.is_declared(name)) error(name, " declared twice");
  Token t2 = ts.get();
  if (t2.kind != '=') error("= missing in declaration of " ,name);
  double d = expression();
  // names.push_back(Variable(name,d)); // New Variable is marked as variable (no as a const)
  STable.declare(name,d,false); // define a variable
  return d;
}

double declaration_const()
// "const" var_name "=" Expression
// we can redeclare variable as a const
{
  Token t = ts.get();
  if (t.kind != name) error ("name expected in declaration_const");
  string name = t.name;
  // we can redeclare variable as a const
  // if (is_declared(name)) error(name, " declared twice");
  Token t2 = ts.get();
  if (t2.kind != '=') error("= missing in declaration of " ,name);
  double d = expression();
  STable.declare(name,d,true); // try to declare. Note we can redeclare variable as a constant, but can not redeclare constants
  return d;
}

// we determined that this is going to be an assignment
// need to read '=' and Expression
double assignment(string s) {
  double d = expression();
  STable.set(s,d); // set_value(s,d);
  return d;
}

double statement()
{
  Token t = ts.get();
  switch(t.kind) {
  case let:  // declaration
    return declaration();
  case con: // declaration constant
    return declaration_const();
  case name:  // this can be either variable or variable assignment. Need to check first
    // check if '=' follows, this will let us decide
  {
    char ch;
    cin >> ch;
    if (ch == '=') return assignment (t.name); // assignment
    // otherwise this is the variable that will go into expression
    cin.unget();
    // can fall through into the default
    //ts.unget(t);
    //return expression();
  }

  default:
    ts.unget(t);
    return expression();
  }
}

Roman::Roman_int statementRoman(){
  int parm =  int (statement());
  Roman::Roman_int r(parm);
  return r;
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
    if (t.kind == help) {
      print_help();
    } else {
      ts.unget(t);
      //cout << result << statement() << endl;
      cout << result << statementRoman() << endl;
    }
  }
  catch(runtime_error& e) {
    cerr << e.what() << endl;
    clean_up_mess();
  }
}

int main()

  try {
    // predefine names:
    STable.declare("pi",3.1415926535,false); // user can redeclare them later as a constant // define_name("pi",3.1415926535);
    STable.declare("e", 2.7182818284,false); // user can redeclare them later as a constant // define_name("e", 2.7182818284);

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
