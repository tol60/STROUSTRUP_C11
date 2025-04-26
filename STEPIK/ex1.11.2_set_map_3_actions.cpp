// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <string>
#include <set>
using namespace std;


int main()
{
    set <int> s;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int type; // 1 - add, 2 - check, 3 - remove
        int x;
        cin >> type >> x;
        if (type == 1) { // 1 - add
            s.insert(x);
        } else if (type == 2) { // 2 - check
            if (s.find(x) == s.end()) {
                cout << "NO\n";
            } else {
                cout << "YES\n";
            }
        } else {  // 3 - remove
            s.erase(x);
        }
    }

    return 0;
}
