// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <string>

using namespace std;


int main()
{
/*
 В сети интернет каждому компьютеру присваивается четырехбайтовый код, который принято записывать в виде четырех чисел, каждое из которых может принимать значения от 0 до 255, разделенных точками. Вот примеры правильных IP-адресов:
127.0.0.0
192.168.0.1
255.0.255.255
Напишите программу, которая определяет, является ли заданная строка правильным IP-адресом.

Входные данные
Программа получает на вход строку из произвольных символов.
Выходные данные
Если эта строка является корректной записью IP-адреса, выведите YES, иначе выведите NO.
Примечание
Для перевода из строки в число удобно пользоваться функцией stoi, которая принимает на вход строку, а возвращает число.
*/

    string s;
    getline (cin, s);

    s += '.'; // we will add a space to simplify the code

    int cnt = 0;
    int start = 0;
    int end_p1 = 0;

    while ( (end_p1 = s.find('.',start)) != -1) { // find next space
        cnt ++;
        if (cnt > 4) { // can not have more then 4 numbers
            cout << "NO";
            return 0;
        }

        int len = end_p1 - start;
        string numb = s.substr(start,len);
        if (numb.find_first_not_of("0123456789") != string::npos) { // found letters
            cout << "NO";
            return 0;
        }

        int val = stoi (numb);
        if (val < 0 || val > 255) {
            cout << "NO";
            return 0;
        }

        start = end_p1 + 1; // prepare for next search
    }

    // as we added extra space to the end of the string, do not need extra check for the last word here.

    if (cnt != 4) {
        cout << "NO";
    } else {
        cout << "YES";
    }
    return 0;
}
