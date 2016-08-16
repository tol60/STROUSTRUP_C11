// Enter several numbers and then enter N first
// g++ -std=c++11 -g -o ch5.e.8_N_numbers.exe ch5.e.8_N_numbers.C  2>&1 | tee tmp.txt

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
  for (int i=0; i<N; i++) {
    sum += numbers[i];
    cout << numbers[i] << " ";
  }

  cout << " ) is " << sum <<'.' << endl;
  return 0;
}


