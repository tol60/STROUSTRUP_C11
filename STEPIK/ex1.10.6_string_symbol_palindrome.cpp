// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <string>

using namespace std;


int main()
{
/*
По данной строке определите, является ли она палиндромом (то есть, читается одинаково как слева-направо, так и справа-налево).
Входные данные
На вход подается 1 строка без пробелов.
Выходные данные
Необходимо вывести yes, если строка является палиндромом, и no в противном случае.
Sample Input:
kayak
Sample Output:
yes
*/

    string s;
    cin >> s;

    bool palindrome = true;
    int l = s.size();
    for (int i = 0; i < l / 2; i++) {
        if (s[i] != s[l - 1 - i]) {
            palindrome = false;
            break;
        }
    }

    if (palindrome) {
        cout << "yes";
    } else {
        cout << "no";
    }
    return 0;
}
