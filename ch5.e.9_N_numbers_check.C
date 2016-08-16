// Enter several numbers and then enter N first
// g++ -std=c++11 -g -o ch5.e.9_N_numbers_check.exe ch5.e.9_N_numbers_check.C  2>&1 | tee tmp.txt

#include "std_lib_facilities.h"

int main ()
{
  cout << "Please enter the number of values you want to sum:\n";
  int N{0};
  cin >> N;
  if (!cin) {
    cout << "Your input was not recognized. Terminating\n";
    return 1; // error termination.
  } else {
    cout << "You entered "<< N<< endl;
  }

  cout << "Please enter some integers (pres \'|\' to stop):\n";
  vector<int> numbers;
  int tmp;
  while (cin>>tmp){
    numbers.push_back(tmp);
  }

  if (N>numbers.size()) {
    cout << "Error: Number " << N << " of integers you wanted to be summed is greater "
        <<"then the number " << numbers.size() << " of integers you entered.\n";
    return 2; // error termination
  }

  cout << "The sum of the first " << N << " numbers ( ";
  int sum = 0;
  try {
    for (int i=0; i<N; i++) {
      sum += numbers[i];
      cout << numbers[i] << " ";
      if (sum < 0)
        error ("The sum can not be represented as int");
    }
  }
  catch (exception& e) {
    cerr << "error: " << e.what() << endl;
    return 1;
  }
  catch (...) {
    cerr << "Oops: unknown exception!\n";
    return 2;
  }
  cout << " ) is " << sum <<'.' << endl;
  return 0;
}


