// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <map>
#include <string>
using namespace std;

/*
Вам дан словарь, состоящий из пар слов. Каждое слово является синонимом к парному ему слову. Все слова в словаре различны. Для одного данного слова определите его синоним.

Входные данные
Программа получает на вход количество пар синонимов N. Далее следует N строк, каждая строка содержит ровно два слова-синонима. После этого следует одно слово.
Выходные данные
Программа должна вывести синоним к данному слову.
Sample Input:
3
Hello Hi
Bye Goodbye
List Array
Goodbye
Sample Output:
Bye
*/
int main()
{
    int n;
    cin >> n;
    map <string, string> m;

    for (int i = 0; i < n; i++) {
        string a, b;
        cin >> a >> b;
        m[a] = b;
        m[b] = a;
    }

    string str;
    cin >> str;

    cout << m[str];

    return 0;
}
