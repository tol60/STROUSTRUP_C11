// Do some prompts for information and then generate a simple latter
// g++ -std=c++11 -g -o ch3.d_letter.exe ch3.d_letter.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"
int main ()
{
  int correct? {3};
  // Step 1: name
  cout << "Please enter the name of the person you want to write to (followed by 'enter'):" << endl;
  string first_name {""};
  cin >> first_name;

  // Step 2: friend's name:
  cout << "Please enter the name of your common friend\n";
  string friend_name {"???"};
  cin >> friend_name;

  // Step 3: friend's sex:
  cout << "Please enter your common friend's sex (m/f)\n";
  char friend_sex {0};
  cin >> friend_sex;

  // Age
  cout << "Please enter the person's age (in years)\n";
  int age{0};
  cin >> age;
  if (age <=0 || age>= 110) {
    simple_error("you are kidding!");
  }

  cout << "\tDear " << first_name << ",\n";
  cout << "How are you? I am fine. I miss you.\n";

  // comments based on sex
  if (friend_sex == 'm') {
    cout << "If you see " << friend_name << " please ask him to call me.\n";
  } else if (friend_sex == 'f'){
    cout << "If you see " << friend_name << " please ask her to call me.\n";
  }

  // optional comments based on age
  if (age < 12) {
    cout << "Next year you will be "<< age+1<< '.'<<endl;
  } else if (age == 17) {
    cout << "Next year you will be able to vote.\n";
  } else if (age>70) {
    cout << "I hope you are enjoying retirement.\n";
  }

  // signature
  cout << "Yours sincerely, \n\n\n";
  cout << "\t\tTony\n";

  return 0;
}
