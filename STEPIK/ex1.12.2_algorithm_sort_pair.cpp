// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility> // pair
using namespace std;



int main()
{
    int n; // number of words in a dictionary
    cin >> n;
    vector <pair <int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        a[i] = {tmp, i}; // creating a pair value, number
    }
    sort (a.begin(),a.end());

    for (auto now : a) {
        cout << now.second << " ";
    }

    return 0;
}
