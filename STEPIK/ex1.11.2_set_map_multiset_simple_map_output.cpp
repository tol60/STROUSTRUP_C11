// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <string>
#include <map>
using namespace std;


int main()
{
    map <int, string> s;
    s[112] = "sos";
    s[102] = "emergency";
    if (s.find(112) != s.end()) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    cout << endl;

    for (auto now : s) {
        cout << now.first << ' ' << now.second << endl;
    }

    return 0;
}
