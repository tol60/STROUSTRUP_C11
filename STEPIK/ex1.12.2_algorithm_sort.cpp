// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



int main()
{
    int n; // number of words in a dictionary
    cin >> n;
    vector <int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort (a.begin(),a.end());

    for (auto now : a) {
        cout << now << " ";
    }

    return 0;
}
