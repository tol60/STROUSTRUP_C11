// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <string>
#include <map>
using namespace std;


int main()
{
    map <int, string> s;
    s[112] = "sos";
    if (s.find(112) != s.end()) {
        cout << "YES";
    } else {
        cout << "NO";
    }


    return 0;
}
