// g++ -g -w -Wall -std=c++11 ch18.e.9_memory_layout.C -o ch18.e.9_memory_layout.exe 2>&1 | tee tmp.txt
/* 1. Write a function, char* strdup (const char*), that copies a C-style string
 *    into memory it allocates on the free store. Do not use any standard library
 *    functions. Do not use subscripting; use the dereference operator * instead.
 * 2. Write a function, char* findx(const char* s, const char*x), that finds the first
 *    occurrence of the C-style string x in s. Do not use any standard library functions.
 *    Do not use subscripting; use the dereference operator* instead.
 *    functions. Do not use subscripting; use the dereference operator * instead.
 * 3. Write a function, int cmpstr(const char* s1, const char* s2), that compares
 *    C-style strings. Let it return a negative number if s1 is lexicographically before s2,
 *    zero if s1 equals s2, and a positive number if s1 is lexicographically after s2.
 *    Do not use any standard library functions.
 *    Do not use subscripting; use the dereference operator* instead.
 * 4. Consider what happens if you give strdup(), findx() and strcmp() an  argument
 *    that is not a C-style string. Try it! First figure out how to get a char* that
 *    doesn't point to a zero-terminated array of characters and then use it
 *    (never do this in real- non-experimental - code; it can create havoc).
 *    Try it with free-store-allocated and stack-allocated "fake C-style strings".
 *    If the results still look reasonable, rurn off debug mode. Redesign and re-implement
 *    those three functions so that they take another argument giving the maximum number of
 *    elements allowed in argument strings. Then test that with correct C-style strings and "bad" strings.
 * 5. Write a functions, string cat_dot(const string& s1, const string& s2), that concatenates
 *    two strings with a dot in between. For example, cat_dot("Niels", "Bohr") will
 *    return a string Niels.Bohr.
 * 6. Modify cat_dot() from the previous exercise to take a string to be used as the
 *    separator (thather than dot) as its third argument
 * 7. Write versions of the cat_dot()s from the previous exercisers to take C-style strings
 *    a arguments and return a free-store-allocated C-style string as the result. Test these
 *    functions with several strings. Be sure to free (using delete) all the memory you
 *    allocated from free store (using new). Compare the effort involved in this exercise
 *    with the effort involved for exercises 5 and 6.
 * 8. Rewrite all the functions in $18.7 to use the approach of making a backward copy of
 *    the string and then comparing; for example, take "home", generate "emoh", and compare
 *    those two strings to see that they are different, so home isn't a palindrome.
 * 9. Consider the memory layout in $17.4. Write a program that tells the order in which
 *    static storage, the stack, and the free store are laid out in memory. In which direction
 *    does the stack grow: upward toward higher addresses or downward toward lower addresses?
 *
 */

#include <iostream>


using namespace std;
/*
char* strdup (const char* aa){
  // 1. calculate the length of the input string
  // 2. allocate the memory
  // 3. do the copy


  // calculate the length of an input string
  const char* aa_2 = aa;
  int n=1; // to account for zero that terminates a C-style string
  while (*aa_2) {n++; aa_2++;}

  char* bb = new char[n];
  char* bb_2 = bb;

  while (*aa) {
    *bb_2 = *aa;
    aa++;
    bb_2++;
  }

  // copy the zero termination symbol (last one)
  *bb_2 = *aa;
  return bb;
}

char* findx(const char* s, const char* x) {
  if (!*s && !*x) // both strings are empty
    return (char *) s;
  while (*s)  // till we hit the end of the input string
  {
    // at this point *s is non-zero (not the end of the string)
    if (*s != *x)  { // trying to match the first character of x
      // the first character of x did not match, advance
      s++;
    } else {
      // the first character matched, see if we matched the rest of the symbols
      const char* s2 = s;
      const char* x2 = x;
      while (*s2 && *x2 && *s2 == *x2){
        s2++;
        x2++;
      }
      if (*x2) { // if we did not hit the end of the short line to match = mismatch
        s++; // advance the start location in the input string
      } else {
        return (char *) s; // full match found
      }
    }
  }
  return nullptr;
}

int strcmp (const char* s1, const char* s2){
  while (*s1 && *s2) {
    if (*s1 < *s2)
      return -1;
    else if (*s1 > *s2)
      return +1;
    else { // advance
      s1++;
      s2++;
    }
  }

  // at this point at least one of the pointers points to \000 termination index
  if (*s2)
    return -1;
  else if (*s1)
    return +1;
  return 0; // equal
}


string  cat_dot(const string& s1, const string& s2){
  return s1 +'.' + s2;
}


string  cat_dot(const string& s1, const string& s2, const string& separator = "."){
  return s1 +separator + s2;
}



int str_len(const char* s) {
  int n=0;
  while (*s) {
    s++;
    n++;
  }
  return n;
}

char* C_style_cat_dot(const char* s1, const char* s2, const char* separator = ".") {
  int len = str_len(s1)+str_len(s2) + str_len(separator) + 1; // extra 1 for end of line
  char* str = new char[len];
  char* ch = str;
  while (*s1) {
    *ch = *s1;
    ch++;
    s1++;
  }
  while (*separator) {
    *ch = *separator;
    ch++;
    separator++;
  }
  while (*s2) {
    *ch = *s2;
    ch++;
    s2++;
  }
  *ch = 0; // end of line symbol
  return str;
}
*/

/*
// Palindromes using string
bool is_palindrome_string( const string& s){
  int last = s.length()-1;
  string rev;
  while (last>=0) {
    rev += s[last];
    --last;
  }
  return rev==s;
}


// Palindromes using arrays
bool is_palindrome( const char s[], int n) {
  // s points to the first character of an array of n characters
  char* rev = new char[n+1];
  rev[n]=0; // do not really need that extra symbol, but just to be consistent with the C  strings
  int first = 0;
  int last = n-1;
  while (last>=0){
    rev[first] = s[last];
    first++;
    last--;
  }

  first =0;
  while (first < n){
    if (s[first]!= rev[first]) {
      delete[] rev;
      return false;
    }
    ++first;
  }

  delete[] rev;
  return true;
}
*/

void print(int &n){
  cout << &n <<":"<<n << endl;
}

void recursive_call(int n){
  // recursively call itself n times.
  int r_int = n;
  print (r_int);
  if (n>0)
    recursive_call(n-1);
}

int g1 = 1;
int g2 = 2;
int g3 = 3;
int main()
{
  int l1 = 11;
  int l2 = 12;
  int l3 = 13;

  cout << "*************************************\n";
  cout << "Inside main function \n";
  cout << "*************************************\n";

  cout << "Printing globals:"<<endl;
  print (g1);
  print (g2);
  print (g3);

  cout << endl;
  cout << "Printing locals:"<<endl;
  print (l1);
  print (l2);
  print (l3);

  cout << endl;
  cout << "Recursive call:"<<endl;
  recursive_call(3);

  cout << endl;
  int* p1 = new int{21};
  int* p2 = new int{22};
  int* p3 = new int{23};
  cout << "Printing free store:"<<endl;
  print (*p1);
  print (*p2);
  print (*p3);
  delete p1;
  delete p2;
  delete p3;
/*
  // char a[] = "What a nice day!";
  // char a[] = {'W','h','a','t'};
  char * a = new char [4];
  a[0] = 'W';
  a[1] = 'h';
  a[2] = 'a';
  a[3] = 't';
  cout << "a = " << a << endl;

  char* b = strdup(a);
  cout << "char* b = strdup(a); produced: \n";
  cout << b << endl;
  delete[] b;

  cout << "***************\n";
  cout <<"char* findx(const char* s, const char* x)"<<endl;

  char* input = "at";
  char* ch = findx(a,input);
  cout << "input = " << input << endl;
  if (ch)
    cout << "output = " << ch << endl;
  else
    cout << "no match found" <<endl;

  input = "bat";
  ch = findx(a,input);
  cout << "input = " << input << endl;
  if (ch)
    cout << "output = " << ch << endl;
  else
    cout << "no match found" <<endl;

  input = a;
  ch = findx(a,input);
  cout << "input = " << input << endl;
  if (ch)
    cout << "output = " << ch << endl;
  else
    cout << "no match found" <<endl;

  input ="";
  cout << "ch = findx(input,input);"<<endl;
  ch = findx(input,input);
  cout << "input = " << input << endl;
  if (ch)
    cout << "output = " << ch << endl;
  else
    cout << "no match found" <<endl;

  char* s1 = a;
  char* s2 = a;
  cout << "s1="<<s1 << endl;
  cout << "s2="<<s2 << endl;
  cout << "strcmp(s1,s2) = " << strcmp(s1,s2) << endl;

  s2 = "What";
  cout << "s1="<<s1 << endl;
  cout << "s2="<<s2 << endl;
  cout << "strcmp(s1,s2) = " << strcmp(s1,s2) << endl;

  s1 = "What";
  s2 = a;
  cout << "s1="<<s1 << endl;
  cout << "s2="<<s2 << endl;
  cout << "strcmp(s1,s2) = " << strcmp(s1,s2) << endl;

  s1 = "What";
  s2 = "what";
  cout << "s1="<<s1 << endl;
  cout << "s2="<<s2 << endl;
  cout << "strcmp(s1,s2) = " << strcmp(s1,s2) << endl;

  s1 = "";
  s2 = "";
  cout << "s1="<<s1 << endl;
  cout << "s2="<<s2 << endl;
  cout << "strcmp(s1,s2) = " << strcmp(s1,s2) << endl;

  s1 = "";
  s2 = " ";
  cout << "s1="<<s1 << endl;
  cout << "s2="<<s2 << endl;
  cout << "strcmp(s1,s2) = " << strcmp(s1,s2) << endl;



  string s1 = "Niels";
  string s2 = "Bohr";
  string s3 = cat_dot(s1,s2);
  cout << "s1="<<s1<<endl;
  cout << "s2="<<s2<<endl;
  cout << "s3="<<s3<<endl;

  s3 = cat_dot(s1,s2,"__");
  cout << "s1="<<s1<<endl;
  cout << "s2="<<s2<<endl;
  cout << "s3="<<s3<<endl;



  char* s1 = "Niels";
  char* s2 = "Bohr";
  char* s3 = C_style_cat_dot(s1,s2);
  cout << "s1="<<s1<<endl;
  cout << "s2="<<s2<<endl;
  cout << "s3="<<s3<<endl;
  delete[] s3;

  s3 = C_style_cat_dot(s1,s2,"__");
  cout << "s1="<<s1<<endl;
  cout << "s2="<<s2<<endl;
  cout << "s3="<<s3<<endl;
  delete[] s3;


  for (string s; cin>>s;){
    cout << s << " is";
    if (!is_palindrome_string(s)) cout << " not";
    cout << " a palindrome\n";
  }


  char one[] = "mom";
  char two[] = "haah";
  char three[] = "haaha";
  int n =3;
  char* s = one;
  for (int i=0; i<4; ++i) {
    switch (i){
    case 0:
      s = one;
      n = 3;
      break;
    case 1:
      s = two;
      n = 4;
      break;
    case 2:
      s = three;
      n = 5;
      break;
    default:
      s = three;
      n = 4;
    }


    cout << "s="<<s<<", n="<<n<< ", is_palindrome returned ";
    if (is_palindrome(s,n)){
      cout << "true";
    } else {
      cout << "false";
    }
    cout << endl;
  }
  */

  cout << "*************************************\n";
  cout << "main() function is done\n";
  cout << "*************************************\n";
}
