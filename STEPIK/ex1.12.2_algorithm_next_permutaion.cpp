// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// function to print a vector
void print( vector <int> a) {
    for (auto now : a) {
        cout << now << " ";
    }
    cout << endl;
}

int fact(int n) {
    int fact = 1;
    for (int i = 2; i <=n; i++) {
        fact *= i;
    }
    return fact;
}

int main()
{
    int n; // number of words in a dictionary
    cin >> n;
    vector <int> a(n);
    for (int i = 1; i <= n; i++) {
        a[i - 1] = i;
    }

    int cnt = 0;
    while (next_permutation(a.begin(), a.end())) {
        print(a);
        cnt ++;
    }
    cout << "count = " << cnt << ", n! = " << fact(n) << endl;

    return 0;
}
