// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;


int main()
{
    map <string, vector <string>> s;
    s["Vasya"] = {"112233A", "11bbbbbb"};
    s["Petya"] = {"22000000A", "22010101B", "22020202c"};

    for (auto now : s) {
        cout << now.first << ": ";
        for (auto val: now.second) {
            cout << val << ' ';
        }
        cout << endl;
    }

    return 0;
}
