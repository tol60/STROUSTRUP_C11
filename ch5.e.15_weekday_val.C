// Read (day-o-the-week,value) pairs
// Example Tuesday 23 Friday 56 Tuesday -3 Thursday 99
// accept common synonyms such as Mon and monday.
// g++ -std=c++11 -g -o ch5.e.15_weekday_val.exe ch5.e.15_weekday_val.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

int main ()
{
  cout << "Please enter (day-o-the-week, integer-value) pairs.\n";
  cout << "\tExample: Tuesday 23 Mon 56 thursday -3 mon 99:\n";

  constexpr int ndays = 7; // number of days is a week
  string in_string;
  int in_number;
  const vector <string> weekdays_vec = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"}; // full name
  const vector <string> wdays_vec = {"Sun","Mon","Tue","Wed","Thu","Fri", "Sat"}; // short notation

  int num_rejects = 0; // wee need to keep track of number of rejected values

  // each day will contain it's own vector of int numbers
  vector<int> vec_sun;
  vector<int> vec_mon;
  vector<int> vec_tue;
  vector<int> vec_wed;
  vector<int> vec_thu;
  vector<int> vec_fri;
  vector<int> vec_sat;

  vector <int> * ptr;  // pointer to a vector

  vector<string> lcase_weekdays_vec; // To reduce the amount of comparison, we will compare to lower case version
  for (string st:weekdays_vec){
    std::transform(st.begin(), st.end(), st.begin(), ::tolower); // convert to lower case:
    lcase_weekdays_vec.push_back(st);
  }
  if (lcase_weekdays_vec.size()!= ndays) {
    error("lcase_weekdays_vec size does not match ndays"); // check invariant
  }

  vector<string> lcase_wdays_vec; // To reduce the amount of comparison, we will compare to lower case version
  for (string st:wdays_vec){
    std::transform(st.begin(), st.end(), st.begin(), ::tolower); // convert to lower case:
    lcase_wdays_vec.push_back(st);
  }
  if (lcase_wdays_vec.size()!= ndays) {
    error("lcase_wdays_vec size does not match ndays"); // check invariant
  }

  bool input_more = true;
  while (input_more) {
    cin >> in_string >> in_number;
    //cout << "in_string = " << in_string<< ", in_number = "<<in_number<< endl;
    if (cin){ // if there is no Input error
      // process the input
      std::transform(in_string.begin(), in_string.end(), in_string.begin(), ::tolower); // convert to lower case
      //cout << "\tAfter conversion to lower case, in_string = " << in_string<< ", in_number = "<<in_number<< endl;

      //find if matches any entries in the full name array (converted to the lower case)
      bool match_found = false;
      for (int i=0; i< ndays;i++) {
        if (lcase_weekdays_vec[i] == in_string || lcase_wdays_vec[i] == in_string){
          match_found = true;
          switch (i) {
          case 0:
            vec_sun.push_back(in_number);
            break;
          case 1:
            vec_mon.push_back(in_number);
            break;
          case 2:
            vec_tue.push_back(in_number);
            break;
          case 3:
            vec_wed.push_back(in_number);
            break;
          case 4:
            vec_thu.push_back(in_number);
            break;
          case 5:
            vec_fri.push_back(in_number);
            break;
          case 6:
            vec_sat.push_back(in_number);
            break;
          default:
            error ("Unexpected state");
            break;
          } // end switch
          break; // break out of the for loop - we already found the match and processed the entry.
        } // end if statement to check if the current day of the week matches in_string
      } // end for loop that iterates by the day of the week
      if (!match_found){
        ++num_rejects;
        cout << "The entry " << in_string << " " << in_number << " has been rejected. num_rejects = " << num_rejects<< ")\n";
      }

    } else { // error condition in the input detected
      // stop the input, process the statistics for the input we accepted up to this point
      input_more = false;
    }
  } // input loop ends

  // PROCESSING
  cout << "\nPROCESSING:\n";
  //vector <int> * ptr;  // pointer to a vector
  for (int i=0; i<ndays;++i) {
    switch (i) {
    case 0:
      ptr = &vec_sun;
      break;
    case 1:
      ptr = &vec_mon;
      break;
    case 2:
      ptr = &vec_tue;
      break;
    case 3:
      ptr = &vec_wed;
      break;
    case 4:
      ptr = &vec_thu;
      break;
    case 5:
      ptr = &vec_fri;
      break;
    case 6:
      ptr = &vec_sat;
      break;
    default:
      error ("Unexpected index");
      break;
    } // end switch
    cout << weekdays_vec[i] << ": ";
    int sum = 0;
    for (int k: (*ptr)){
      cout << k << " "; // print out one element at a  time
      sum += k;
    }
    cout << "\n\tThe sum of all the values for " << wdays_vec[i] << " is "<< sum<< endl;
  }
  cout << "The number of entries rejected = "<< num_rejects << endl;

  return 0;
}


