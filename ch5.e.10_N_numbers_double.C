// Enter several numbers and then sum N first. Create and print N-1 differences
// g++ -std=c++11 -g -o ch5.e.10_N_numbers_double.exe ch5.e.10_N_numbers_double.C  2>&1 | tee tmp.txt

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
  vector<double> numbers;
  double tmp;
  while (cin>>tmp){
    numbers.push_back(tmp);
  }

  if (N>numbers.size()) {
    cout << "Error: Number " << N << " of integers you wanted to be summed is greater "
        <<"then the number " << numbers.size() << " of integers you entered.\n";
    return 2; // error termination
  }

  cout << "The sum of the first " << N << " numbers ( ";
  double sum = 0;
  for (int i=0; i<N; i++) {
    sum += numbers[i];
    cout << numbers[i] << " ";
  }

  cout << " ) is " << sum <<'.' << endl;


  if (N>1) {
    vector <double> diffrs;
    for (int i=0;i<N-1; ++i) {
      //tmp = numbers[i+1] - numbers[i];
      //diffrs.push_back(tmp);
      diffrs.push_back(numbers[i+1] - numbers[i]);
    }
    cout << "The differencies between adjacent elements are:\n";
    for (double tmp:diffrs)
      cout << tmp << ' ';
    cout << endl;
  }
  return 0;
}


