// Impurt a text an do simple manipulations
// g++ -std=c++11 -g -o ch4.6.4_text_example.exe ch4.6.4_text_example.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

vector <string> disliked_vec = {"Broccoli","Carrots", "Onions"};
bool is_in_disliked_vec(string & in_word) {
  for (string str:disliked_vec)
    if (str == in_word)
      return true;
  return false;
}

int main ()
{
  vector <string> words;
  cout << "The following words are going to be replaced by a BLEEP:\n";
  for (string str:disliked_vec)
    cout << str << " ";
  cout << endl;

  cout << "Please enter some words to be manipulated:\n";
  for (string temp; cin>>temp;) // read whitespace-separated words
    words.push_back(temp);
  cout << "Number of words: "<< words.size() << endl;

  /* Dictionary example
  sort(words); // sort the words

  for (int i = 0; i<words.size(); ++i)
    if (i==0 || words[i-1] !=  words[i]) // is this a new words?
      cout << words[i]<< endl;
  */

  //string disliked = "Broccoli";

  for (int i=0; i<words.size(); ++i)
    //if (words[i] == disliked)
    if (is_in_disliked_vec(words[i]))
      cout << "BLEEP ";
    else
      cout << words[i] << " ";
  cout <<endl;

  return 0;
}


