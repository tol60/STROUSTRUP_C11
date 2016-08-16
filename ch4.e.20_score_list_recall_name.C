// Input the name and the score, terminate input with "NoName 0". Make sure input is unique.
// If you enter the name, the program will retrieve the score or type "name not found"
// g++ -std=c++11 -g -o ch4.e.20_score_list_recall_name.exe ch4.e.20_score_list_recall_name.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

int main ()
{
  vector <string> vnames; // names that 1 to 1 with scores
  vector <int> vscores; // scores that 1 to 1 with names

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
      for (int i=0; i<vnames.size(); ++i) {
        if (vnames[i] == name) {
          unique_flag = false;
          cout << "Error: Not unique name! It appears that you already entered: "<< name << " " << vscores[i] ;
          cout << "; The new entry will be discarded ("<< score<<")\n";
          break; // no need to traverse to the end of the array
        }
      }

      // record a new pair
      if (unique_flag) {
        vnames.push_back(name);
        vscores.push_back(score);
      }
    }
  }

  // Workload: Just pring out all the entries (one per line)
  cout << "Printing out our record:\n";
  for (int i=0; i<vnames.size(); ++i) {
    cout << "En"<<(i+1) << ": "<< vnames[i] << " " << vscores[i]<< endl;
  }

  // If you enter the name, the program will retrieve the score or type "name not found"
  cout <<endl;
  cout << "You can enter the name, and I will retrieve the score or type \"name not found\"\n";

  while (cin>>name) {
    bool name_found = false;
    for (int i=0; i<vnames.size(); ++i) {
      if (vnames[i] == name) {
        cout << "En"<<(i+1) << ": "<< vnames[i] << " " << vscores[i]<< endl;
        name_found = true;
        break; // should break out of the for loop
      }
    }
    if (!name_found) {
      cout << "name " << name << " not found\n";
    }
  }

  return 0;
}


