// Redo "Bulls & Cows" game from exercise 12 in Chapter 5 to use four letters rather than four digits.
// g++ -std=c++11 -g -o ch6.e.8_bulls_cows_letter_rand_time.exe ch6.e.8_bulls_cows_letter_rand_time.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

int main ()
{
  cout << "Let's play modified Bulls and Cow game (Four Letters)!\n";
  cout << "I selected four different letters (a-z) in arbitrary order and you need to guess them\n";
  cout << "Example:\n";
  cout << "If my letters were \"afgz\" and you entered \"agkz\"\n";
  cout << "I would say 2 Bulls and 1 Cow\n";
  cout << "\t Bull => letter and position matched: (a and z)\n";
  cout << "\t Cow => letter matched, but not the position (letter g)\n";
  //cout << "First, please enter an integer number to set the seed\n";

  int seed=0;
  /*cin >> seed;
  if (!cin) {
    cout << "You input was not recognized. Terminating\n";
    return 10;
  }*/

  /* initialize random seed: */
  srand (time(NULL));
  //srand (seed);

  constexpr int ndig = 4; // we are guessing 4 numbers (=letters)
  vector <char> numbers = {'a','f','g','z'}; // the numbers the user is trying to guess (have to be unique)

  while (true) { // main loop
    // generate a random number to be guessed
    numbers.clear(); // should set numbers.size() to zero
    while (numbers.size()!= ndig) {
      //int num = randint(10); // for some reason did not work
      //int num = rand()%10;
      const int n_pos_digits = 'z'-'a'+1; // should get 26
      int num = rand()%n_pos_digits;
      char letter = 'a'+num;
      bool unique_flag = true;
      for (char k:numbers){
        if (k==letter) {
          unique_flag = false; // this number (letter) was already selected
          break; // no need to go to the end of the queue. break the for loop
        }
      }
      if (unique_flag) {
        numbers.push_back(letter); // now we store letters instead of numbers
      }
    }
    // at this point all the numbers should be unique.
    if (numbers.size()!= ndig) {
      error ("Error generating a random letters");
    }
     /*if you want to print out (debug)
    for (char k:numbers){
      cout << k;
    }
    cout <<endl;
    char ch;
    cin>> ch;
  }

  {
    */
    vector <char> input; // user's guess
    bool need_guess = true;
    int cnt_guess = 0; // keep track of how many guesses taken

    cout << endl;  // to separate a new test.
    cout << "Please enter your choice (4 letters): ";
    while (need_guess){


      char ch;
      bool b_need_more = true;
      input.clear();
      // input the new guess
      while (b_need_more && (cin >> ch)) {
        if (ch >= 'a' && ch <='z') {
          //int number  = ch -'0';
          //cout << "You entered number "<< number<< endl;
          //input.push_back(number);
          input.push_back(ch);
          if (input.size()==ndig) {
            b_need_more = false;   // we got all the digits we need
          }
        } else {
          cout << "Character \'"<< ch << "\'was not recognized\n";
        }
      }

      // check that we are in a good state
      if (b_need_more) {
        cout << "I don't have enough letters. I assume you terminated prematurely\n";
        return 1;
      }

      cout << "Your guess "<< ++cnt_guess << " is: ";
      for (int i=0; i<input.size(); ++i){
        //cout << "I["<<i<<"] = "<<input[i]<<endl;
        cout << input[i];
      }
      cout << " => ";

      // do the match
      int cnt_bull = 0; // counting bools
      int cnt_cow = 0; // counting cows
      for (int i=0; i<input.size(); ++i){
        // check one digit at a time
        if (input[i] == numbers[i]) {
          cnt_bull++; // found bool
        } else {
          for (int k:numbers){
            if (input[i] == k) {
              cnt_cow++; // found cow. Assume that all the digits (letters) are different.
            }
          }
        }
      }

      // count and report results
      if (cnt_bull+cnt_cow > ndig) {
        error("Internal error");
      } else if (cnt_bull == ndig) {
        cout << "4 Bulls. You got it!\n";
        need_guess = false; // we are done
      } else {
        // output the normal line
        cout << cnt_bull <<" Bull";
        if (cnt_bull!=1) cout<< 's'; // print s for plural
        cout << ", " << cnt_cow << " Cow";
        if (cnt_cow!=1) cout<< 's'; // print s for plural
        cout<< ".\n";
      }

    }
  }
  return 0;
}


