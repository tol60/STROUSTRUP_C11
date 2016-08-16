//
/* Ex07: Modify the program from the previous exercise so that
 * 1. it replaces don't with do not, can't with can not, ets.;
 * 2. leaves hyphens within words intact (so that we get "do not use the as-if rule"); and
 * 3. converts all characters to lower case.
 *
 * Previous:
 * Ex06: Write a program that replaces punctuation with whitespace.
 * Consider . (dot), ; (semicolon), , (comma), ? (question mark), - (dash), ' (single quote) punctuation characters
 * Don't modify characters within a pair of double quotes.
 * Example:
 *   "- don't use the as-if rule."
 *   Becomes:
 *   "  don t use the as if rule "
 */
// g++ -std=c++11 -g ch11.e.8_Dictionary.C  -o ch11.e.8_Dictionary.exe 2>&1 | tee tmp.txt

#include "std_lib_facilities.h"


int main (int argc, char * argv[])
{
  cout << "There are " << argc << " arguments" << endl;
  for (int i=0; i<argc; i++){
    cout << "\t Argument[" << i <<"] is " << argv[i] << endl;
  }

  if (argc !=3)
    error ("we expect 2 file arguments, got", argc);

  ifstream inFile{argv[1]};
  ofstream outFile{argv[2]};

  if (! inFile)
    error ("Can not open a file", argv[1]);


  const string puncts = ".;,?\""; // the characters (within semicolon) will be removed ("-'" we will handle separately)
  string line; // we will read one line at a time
  while (getline(inFile,line)) { // when we read the line, it is missing '\n' = endl now
    // modify the line
    // A. We will first put everything to lower case, and remove general punctuation (we handle '-' and ''' separately)
    for (char& ch:line) {
      if (ispunct(ch)) {
        // ispunct(c): is not a letter, digit, whitespace or individual control character
        // we restrict it further
        for (char psymb:puncts) {
          if (ch == psymb){
            // match found. Do some work!
            ch = ' '; // was a reference, so we do modify line here
            break;
          }
        }
      } else {
        ch = tolower(ch);
      }
    }

    // B. Let's handle don't -> do not and as-is (hyphens within words)
    bool b_no_insertion{true}; // if we convert don't to do not, we need to start pick up where we ended up last time
    int st_index = 0; // After insertion, we keep track of the starting position of the part of the string we already modified
    do {
      b_no_insertion = true; // if we convert don't to do not, we need to start pick up where we ended up last time
      for (int i=st_index; i<line.length(); i++){
        // ST1 take care of the hyphen
        char& ch = line[i]; // reference to a character in a line
        if (ch == '-')  { // process hyphen within the words
          if (i==0 || i ==line.length()-1) { // if the very first or very last character => not in the middle of a word
            ch = ' '; // remove this hyphen (substitute by a space)
          } else { // we are in the middle of a word,
            // check previous and the following letter to see if it is a literal.
            if (!isalpha(line[i-1]) || !isalpha(line[i+1]) ){
              ch = ' '; // remove this hyphen (substitute by a space)
            }
          }
        }

        // I won't allow it == I will not.
        // I wouldn't allow it == I would not
        // I can't allow it == I can not
        // I don't allow it == I do not

        // ST2  Need to handler don't => do not
        if (ch == '\'') {
          if (i<=3 || i ==line.length()-1) { // less then 3 letters before apostrophe (which would be 4-th) or very last character => not in the middle of a word
            // not enough space for won't or don't or can't...
            ch = ' '; // remove the single apostrophe
          } else { // we are in the middle of a word,
            if (line[i-1] == 'n' && line[i+1] == 't') { // n't
              // ########### string is updated here #########################
              // convert "n't" > " not"
              // Note: we need to make sure we check for "won't". In this case we need more work to do -> "will not"
              if (line[i-3] == 'w' && line[i-2]=='o' ) { // won't
                // won't -> will not
                line = line.substr(0,i-2) + "ill no" + line.substr(i+1,string::npos); // string::npos - till the end of the string
                st_index = i+7;  // advanced by the length of "ill not"
              } else if (line[i-3] == 'c' && line[i-2]=='a' ) {
                // can't -> can not
                // i points to ', so we want to remove 't and add " not"
                // we will take characters [0..(i-1)] drop i (=='\'') and then [i+1, .. end]
                //     can                " no"   "t ...."
                line = line.substr(0,i) + " no" + line.substr(i+1,string::npos); // string::npos - till the end of the string
                // advance by the length of " not" - 4 symbols
                st_index = i+4; // we processed index i (=='\''), next time we would like to start with i+1. But we also added "not" - extra 3 letters
              } else {
                // wouldn't -> would not
                // don't -> do not

                // i points to ', so we want to remove n't and add not
                // no we need to go one extra symbol to the left
                // we will take characters [0..(i-1-1)] drop i (=='\'') and then [i+1, .. end]
                //     would                " not"  "t ..."
                line = line.substr(0,i-1) + " no" + line.substr(i+1,string::npos); // string::npos - till the end of the string
                // advance by the length of " not" - 4 symbols
                st_index = i+4; // we processed index i (=='\''), next time we would like to start with i+1. But we also added "not" - extra 3 letters
              }
              // Note: at this point we "extended" the line. So we need to break out of the for loop and repeat it again (end of line)
              b_no_insertion = false;
              break; // break out of the loop that was processing the string. We need to pick up the corrected string value (finish the rest of the string


            } else {
              ch = ' '; // else remove single apostrophe  (note brent's book -> brent s book)
            }

          }
        }
      }
    } while ( b_no_insertion == false);

    // do not forget to write the modified line out
    outFile << line << endl;  // extra endl (which we lost when we used getline

  }

  return 0;
}


