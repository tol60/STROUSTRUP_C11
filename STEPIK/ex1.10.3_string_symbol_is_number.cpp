// g++ -std=gnu++11 Hello.cpp -o Hello.exe

#include <iostream>
#include <string>

using namespace std;


int main()
{
/*
По введенному символу определите, является ли он цифрой.
Входные данные
Вводится единственый символ.
Выходные данные
Выведите "yes", если символ является цифрой и "no" в противном случае. Обратите внимание, что слова нужно выводить маленькими буквами.
*/


    char c;
    cin >> c;

    if (c >= '0' && c <= '9' ) {
        cout << "yes";
    } else {
        cout << "no";
    }

    return 0;
}
