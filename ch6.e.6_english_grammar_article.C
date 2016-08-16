// Add the article the to the "English" grammar in $6.4.1, so that it can describe
// birds fly but the fish swim
// g++ -std=c++11 -g -o ch6.e.6_english_grammar_article.exe ch6.e.6_english_grammar_article.C  2>&1 | tee tmp.txt

// Grammar:
// Sentence:
//  Noun Verb
//  Article Noun Verb
//  Sentence Conjunction Sentence
// Conjunction:
//  "and"
//  "or"
//  "but"
// Noun:
//  "birds"
//  "fish"
//  "C++"
// Verb:
//  "rules"
//  "fly"
//  "swim"
// Article:
//  "the"

#include "std_lib_facilities.h"

// global variables
const vector <string> vConjunction = {"and", "or", "but"};
const vector <string> vNoun = {"birds", "fish", "C++"};
const vector <string> vVerb = {"rules", "fly", "swim"};
const vector <string> vArticle = {"the"};

bool val = false; // keep track of the current Sentence status
string fullSentence ="";

// do we recognize this str as a noun?
bool noun(string str) {
  for (int i=0; i<vNoun.size(); ++i) {
    if (vNoun[i] == str) {
      return true;   // we recognized the word
    }
  }
  return false;
}

// do we recognize this str as a verb?
bool verb(string str) {
  for (int i=0; i<vVerb.size(); ++i) {
    if (vVerb[i] == str) {
      return true;   // we recognized the word
    }
  }
  return false;
}

// do we recognize this str as a Conjunction?
bool conjunction(string str) {
  for (int i=0; i<vConjunction.size(); ++i) {
    if (vConjunction[i] == str) {
      return true;   // we recognized the word
    }
  }
  return false;
}

// do we recognize this str as an Article?
bool article(string str) {
  for (int i=0; i<vArticle.size(); ++i) {
    if (vArticle[i] == str) {
      return true;   // we recognized the word
    }
  }
  return false;
}

// Sentence:
//  Noun Verb  (case I)
//  Article Noun Verb (case Ib)
//  Sentence Conjunction Sentence (case II)
bool sentense(string str) {
  //string str;
  //cin >> str;
  if (val) {
    //(case II)
    //  Sentence Conjunction Sentence
    // str has to be a Conjunction
    if (conjunction(str)) {
      cin >> str; // enter the next word (it should be a beginning of a new sequence
      fullSentence = fullSentence + " " + str;
      val = false;
      return sentense (str);
    } else {
      return false;
    }

  } else {
    // (case I)
    //  Noun Verb
    //  Article Noun Verb

    // allow for a single article (need to enter next string, which would have to be a noun)
    if (article(str)){
      // now the next word would have to be a noun
      cin >> str; // enter the next word
      fullSentence = fullSentence + " " + str;
    }
    // no else required, the regular case will handle this as well.

    if (noun(str)) {
      // Noun Verib
      // Now the next word (string) should be a verb
      cin >> str; // enter the next word
      fullSentence = fullSentence + " " + str;
      return verb(str);
    } else {
      return false;  // we expected str to be a noun
    }
  }

}

int main ()
try
{
    cout << "Welcome to our english grammar checker.\n";
    cout << "Please enter sentence like birds fly but the fish swim . \n";
    cout << "Make sure the sentence is terminated by \" . \"\n";
    cout << "When you are done, type =, to exit type x\n";

    cout << "I recognize the following nouns:\n";
    for (auto str:vNoun) {
      cout << "\t" << str<<",";
    }
    cout <<endl;

    cout << "I recognize the following verbs:\n";
    for (auto str:vVerb) {
      cout << "\t" << str<<",";
    }
    cout <<endl;

    cout << "I recognize the following conjunctions:\n";
    for (auto str:vConjunction) {
      cout << "\t" << str<<",";
    }
    cout <<endl;

    cout << "I recognize the following articles:\n";
    for (auto str:vArticle) {
      cout << "\t" << str<<",";
    }
    cout <<endl;

    val = false;
    while (cin) {
        string str;
        cin >> str;
        //if (t.kind == 'q') break; // 'q' for quit
        if (str == "x") break; // 'x' for quit
        //if (t.kind == ';')        // ';' for "print now"
        if (str == ".")        // '=' for "print now"
        {
          //cout << "=" << val << '\n';
          if (val) {
            cout << "OK:\n";
          } else {
            cout << "Not ok:\n";
          }
          cout << "\t"<< fullSentence<<endl;

          val = false;  // prepare to process a new sentence
          fullSentence = ""; // prepare to process a new sentence
        } else {
        //    ts.putback(t);
          fullSentence = fullSentence + " " + str;
          val = sentense(str);

          if (!val) {
            cout << "Not ok:\n";
            cout << "\t"<< fullSentence<<endl;
            fullSentence = ""; // prepare to process a new sentence
            cin.clear();
            cin.ignore(10000,'\n'); // remove a bunch of characters that are still in the buffer up to a new line
          }
        }
    }
    //keep_window_open();
}
catch (exception& e) {
    if (*e.what()=='x') {
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


