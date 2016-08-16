// Input the name and the score, terminate input with "NoName 0". Make sure input is unique.
// based on ch4.e.19_score_list.C, but now we use vector of Name_value class instead of two vectors
// g++ -std=c++11 -g -o ch6.e.4_score_list_class.exe ch6.e.4_score_list_class.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

class Name_value{
public:
  string name;
  int value;
  Name_value(string in_name, int in_value)
          :name{in_name}, value {in_value} {}
};

int main ()
{
  //vector <string> vnames; // names that 1 to 1 with scores
  //vector <int> vscores; // scores that 1 to 1 with names
  vector <Name_value> vstorage;

  const string term_name = "NoName"; // this would be a terminating string.
  string name{" "};
  int score {0};

  bool terminate_input = false;
  // Input
  cout << "Please enter the names and the scores, terminate by \""<< term_name << " 0\"\n";
  while ( !terminate_input ) {
    cin >> name;
    if (! (cin >> score)) {
      cout << "Did not recognize you entry: "<< name << " " << score <<endl;
      cout << "\tIf you wish to terminate your input, please enter: "<< term_name << " 0\"\n";
      name = "error"; // just to mark an error message
      score = -1; // just ot mark an error message
      cin.clear();  // clear error flags
      cin.ignore(10000,'\n'); // remove a bunch of characters that are still in the buffer up to a new line
    } else if (name == term_name && score == 0) {
      cout << "\tTerminating the input\n";
      terminate_input = true;
    } else {
      // enter a new entry
      cout << "You entered: "<< name << " " << score << endl;
      bool unique_flag = true;
      // verify that name is unique and add the name/ score combo
      for (int i=0; i<vstorage.size(); ++i) {
        if (vstorage[i].name == name) {
          unique_flag = false;
          //cout << "Error: Not unique name! It appears that you already entered: "<< name << " " << vscores[i] ;
          cout << "Error: Not unique name! It appears that you already entered: "<< name << " " << vstorage[i].value ;
          cout << "; The new entry will be discarded ("<< score<<")\n";
          break; // no need to traverse to the end of the array
        }
      }

      // record a new pair
      if (unique_flag) {
        //vnames.push_back(name);
        //vscores.push_back(score);
        Name_value tmp(name, score);
        vstorage.push_back(tmp);
      }
    }
  }

  // Workload: Just pring out all the entries (one per line)
  cout << "Printing out our record:\n";
  for (int i=0; i<vstorage.size(); ++i) {
    cout << "En"<<(i+1) << ": "<< vstorage[i].name << " " << vstorage[i].value<< endl;
  }

  return 0;
}


