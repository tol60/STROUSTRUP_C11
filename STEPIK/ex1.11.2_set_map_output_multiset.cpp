// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <string>
#include <set>
using namespace std;


int main()
{
    multiset <int> s;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        s.insert(x);
    }

    //for (auto now = s.begin(); now != s.end(); now++) {
    for (std::set<int>::iterator now = s.begin(); now != s.end(); now++) {
        cout << *now << " ";
    }
    cout << endl;

    for (auto now : s) {
        cout << now << ' ';
    }


    return 0;
}
