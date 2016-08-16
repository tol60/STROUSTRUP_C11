// Input the name and the score, terminate input with "NoName 0". Make sure input is unique.
// g++ -std=c++11 -g -o ch4.z.19_cin_error.exe ch4.z.19_cin_error.C  2>&1 | tee tmp.txt
// http://www.cplusplus.com/reference/istream/istream/ignore/
// http://www.cplusplus.com/reference/ios/ios/clear/

//#include "std_lib_facilities.h"
#include<iostream>
#include<string>

using namespace std;

int main ()
{
  string name="name";
  int score = -1;

  cout << "Please enter a string and a number (separated by space)\n";
  cin >> name;
  cin >> score;

  if (cin.fail() ) {
    cout << "After the first entry cin appears to have failed. Trying to clear\n";
    cin.clear();  // clear error flags
    cin.ignore(10000,'\n'); // remove a bunch of characters that are still in the buffer up to a new line
  } else {
    cout << "After the first entry cin appears to be good\n";
  }

  string name_two = "name_two";
  int score_two =-1;
  cout << "Please enter anoter string and a number (separated by space)\n";
  cin >> name_two;
  cin >> score_two;

  cout<< "name = "<<name << endl;
  cout<< "score = "<<score << endl;

  cout<< "name_two = "<<name_two << endl;
  cout<< "score_two = "<<score_two << endl;

  return 0;
}


